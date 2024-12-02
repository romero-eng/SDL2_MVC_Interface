#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Polygon.hpp"


std::vector<std::array<int, 2>> calculate_line_points(const std::array<std::array<int, 2>, 2>& line)
{
	/*
	Problem Definition:
	-------------------

		Draw a discretized version of the line (y = mx + b) defined by the points {(x1, y1), (x1, y1)}

	Algorithm:
	----------

		Basically, for a non-steep monotonically increasing line, step along the x-axis, and
		for each step, increment the y-value in case the actual line goes above the midpoint.
		The equations below are a generalized formalization of this procedure for all non-steep
		lines (for steep lines, switch the x and y axes).

		1)  define: Δx = x2 - x1

		2)  define: Δy = y2 - y1

		3)  define: x[n] = the array of points along the x-axis selected by this algorithm
						   where the beginning and end points are defined by the user-selected
						   points (i.e., x[0] = x_1 and x[N + 1] = x_2)

		4)  define: y[n] = the array of points along the y-axis selected by this algorithm
						   where the beginning and end points are defined by the user-selected
						   points (i.e., y[0] = y_1 and y[N + 1] = y_2)

						   WARNING: y[n] != y(x[n])

								=> y(x[n]) = mx[n] + b (i.e., y(x[n]) refers to the y-coordinates of the
														calculated points along the continuous line, not
														to the points selected by the algorithm which
														approximate this continuous line)
					 		__
						   |
	 					   |	 1,  x >= 0
		5) define sgn(x) = |
						   |	-1,  x < 0
						   |__

		6)  for n=1 to n=N: (with N being the number of steps to take along the x-axis)
		    ---------------

			    x[n + 1] = x[n] + sgn(Δx)

						    __
					       |
					       |  y[n] + sgn(Δy) ,  |y(x[n + 1]) - y[n]| >= 0.5
			    y[n + 1] = |
					       |	  y[n]		 , 	|y(x[n + 1]) - y[n]| < 0.5
					       |__

	Computational Optimization:
	---------------------------

		The calculation of the decision on whether or not to increment along the y-axis
		is computationally optimized as below:

				|y(x[n + 1]) - y[n]| >= 0.5  --------->  2|(n + 1)Δy - (N + 1)*(y[n] - y[0])| >= (N + 1)

		How this transformation is both equivalent and more computationally efficient is an
		exercise left up to the reader.

	*/

	const auto& [point_1, point_2] = line;
    const auto& [x1, y1] = point_1;
    const auto& [x2, y2] = point_2;

	if (point_1 == point_2) {
		throw std::runtime_error("Cannot calculate a drawn line between the same two points");
	}

    int delta_y {y2 - y1};
    int delta_x {x2 - x1};

	int sgn_delta_y {y2 >= y1 ? 1 : -1};
	int sgn_delta_x {x2 >= x1 ? 1 : -1};
    bool steep_slope {std::abs(delta_y) > std::abs(delta_x)};
    std::size_t N {static_cast<std::size_t>(steep_slope ? std::abs(delta_y) : std::abs(delta_x)) - 1};

	std::vector<std::array<int, 2>> points (N + 2);
    points[0] = point_1;
	points[N + 1] = point_2;

	if(delta_y == 0) {
		for (std::size_t n = 0; n < N; n++) {
			points[n + 1] = points[n];
			points[n + 1][0] += sgn_delta_x;
		}
	} else if (delta_x == 0) {
		for (std::size_t n = 0; n < N; n++) {
			points[n + 1] = points[n];
			points[n + 1][1] += sgn_delta_y;
		}
	} else {

	    int tmp_n_plus_one;
    	int tmp_N_plus_one {static_cast<int>(N) + 1};
 
	    for(std::size_t n = 0; n < N; n++) {

	        points[n + 1] = points[n];
    	    tmp_n_plus_one = static_cast<int>(n) + 1;

	        if(steep_slope) {
        	    if ((std::abs(tmp_n_plus_one*delta_x - tmp_N_plus_one*(points[n][0] - points[0][0])) << 1) >= tmp_N_plus_one) {
        	        points[n + 1][0] += sgn_delta_x;
            	}
            	points[n + 1][1] += sgn_delta_y;
    	    } else {
	            if ((std::abs(tmp_n_plus_one*delta_y - tmp_N_plus_one*(points[n][1] - points[0][1])) << 1) >= tmp_N_plus_one) {
            	    points[n + 1][1] += sgn_delta_y;
    	        }
        	    points[n + 1][0] += sgn_delta_x;
        	}
    	}
	}

    return points;
}


std::tuple<std::vector<std::array<int, 2>>,
           std::vector<std::array<int, 2>>> calculate_boundary_points(const std::vector<std::array<int, 2>>& vertices)
{
	if(vertices.size() < 3) {
		throw std::runtime_error("A polygon can only be defined with a minimum of three vertices");
	}

	std::vector<std::array<std::array<int, 2>, 2>> lines;

	for(std::size_t i = 0; i < vertices.size() - 1; i++) {
		lines.push_back({vertices[i], vertices[i + 1]});
	}
	lines.push_back({vertices[vertices.size() - 1], vertices[0]});

	std::vector<std::array<int, 2>> boundary_points;
	std::array<int, 2> tmp_point;
	std::vector<std::array<int, 2>> tmp_boundary_points;
    std::vector<std::array<int, 2>> extra_vertices;

	for(std::array<std::array<int, 2>, 2> line : lines) {

		tmp_boundary_points = calculate_line_points(line);
		tmp_boundary_points = std::vector<std::array<int, 2>> (tmp_boundary_points.begin(), tmp_boundary_points.end() - 1);

		for(std::array<int, 2> potential_vertex : tmp_boundary_points) {
			for(int x : {-1, 0, 1}){
				for(int y : {-1, 0, 1}) {
					if(!(x == 0 && y == 0)) {

						tmp_point = {potential_vertex[0] + x, potential_vertex[1] + y};

						if(std::find(boundary_points.begin(), boundary_points.end(), tmp_point) != boundary_points.end()) {
							if(std::find(vertices.begin(), vertices.end(), tmp_point) == vertices.end()) {
								extra_vertices.push_back(potential_vertex);
							}

						}
					}
				}
			}
		}

		for(std::array<int, 2> boundary_point : tmp_boundary_points) {
			boundary_points.push_back(boundary_point);
		}

	}

	return {boundary_points, extra_vertices};
}


std::map<int, std::vector<int>> map_2D_coordinates_to_scanlines(std::vector<std::array<int, 2>> coordinates,
                                                                bool orthogonal_axis_first)
{
    std::size_t orthogonal_axis {static_cast<std::size_t>(orthogonal_axis_first ?  0 : 1)};

    std::map<int, std::vector<int>> scanline_per_orthogonal_axis_point;
    std::size_t scanning_axis = static_cast<std::size_t>(std::abs(static_cast<int>(orthogonal_axis) - 1));

    for(std::array<int, 2> coordinate : coordinates) {
        if(scanline_per_orthogonal_axis_point.contains(coordinate[orthogonal_axis])) {
            scanline_per_orthogonal_axis_point[coordinate[orthogonal_axis]].push_back(coordinate[scanning_axis]);
        } else {
            scanline_per_orthogonal_axis_point.emplace(coordinate[orthogonal_axis], std::vector<int> {coordinate[scanning_axis]});
        }
    }

    return scanline_per_orthogonal_axis_point;
}


std::map<int, std::vector<std::deque<int>>> collate_points_along_scanlines(std::map<int, std::vector<int>> scanlines_per_orthogonal_axis_point)
{
    bool not_found;
    bool boundary_crossed_from_back;
    bool boundary_crossed_from_front;
    std::map<int, std::vector<std::deque<int>>> boundaries_per_orthogonal_axis_point;

    for(auto& [orthogonal_axis_point, scanline] : scanlines_per_orthogonal_axis_point) {

		// Make sure the integers within the scanline are sorted in ascending order with no repeats/duplicates

        std::sort(scanline.begin(),
                  scanline.end());

        scanline.erase(std::unique(scanline.begin(),
                                   scanline.end()),
                       scanline.end());

        for (int boundary : scanline) {
            if(boundaries_per_orthogonal_axis_point[orthogonal_axis_point].size() > 0) {

                not_found = true;
                std::size_t index = 0;
                while(index < boundaries_per_orthogonal_axis_point[orthogonal_axis_point].size() && not_found) {
                
                    boundary_crossed_from_back  = boundary == boundaries_per_orthogonal_axis_point[orthogonal_axis_point][index].back()  - 1;
                    boundary_crossed_from_front = boundary == boundaries_per_orthogonal_axis_point[orthogonal_axis_point][index].front() + 1;

                    if(boundary_crossed_from_back || boundary_crossed_from_front) {

                    not_found = false;

                        if(boundary_crossed_from_back) {
                            boundaries_per_orthogonal_axis_point[orthogonal_axis_point][index].push_back(boundary);
                        } else {
                            boundaries_per_orthogonal_axis_point[orthogonal_axis_point][index].push_front(boundary);
                        }
                    }

                index++;
                }
                if(not_found) {
                    boundaries_per_orthogonal_axis_point[orthogonal_axis_point].push_back(std::deque<int> {boundary});
                }

            } else {
                boundaries_per_orthogonal_axis_point[orthogonal_axis_point].push_back(std::deque<int> {boundary});
            }
        }

    }

    return boundaries_per_orthogonal_axis_point;
}


std::vector<std::array<int, 2>> even_odd_ray_casting(const std::vector<std::array<int, 2>>& boundary_coordinates)
{
    std::vector<std::array<int, 2>> within_shape_points;

    int num_right_sided_boundary_crossings;
    int num_left_sided_boundary_crossings;
    int num_up_sided_boundary_crossings;
    int num_down_sided_boundary_crossings;

    std::size_t min_x_axis_boundary_point;
    std::size_t max_x_axis_boundary_point;

    std::map<int, std::vector<int>> vertical_scanline_per_y_axis_point {map_2D_coordinates_to_scanlines(boundary_coordinates, false)};
    std::map<int, std::vector<std::deque<int>>> horizontal_boundaries_per_x_axis_point {collate_points_along_scanlines(map_2D_coordinates_to_scanlines(boundary_coordinates, true))};

    for(auto& [y_axis_point, vertical_boundaries] : collate_points_along_scanlines(vertical_scanline_per_y_axis_point)) {

		min_x_axis_boundary_point = \
			static_cast<std::size_t>(*std::min_element(vertical_scanline_per_y_axis_point[y_axis_point].begin(),
													   vertical_scanline_per_y_axis_point[y_axis_point].end()));

		max_x_axis_boundary_point = \
			static_cast<std::size_t>(*std::max_element(vertical_scanline_per_y_axis_point[y_axis_point].begin(),
							 						   vertical_scanline_per_y_axis_point[y_axis_point].end()));

        for(std::size_t x_axis_point = min_x_axis_boundary_point; x_axis_point < max_x_axis_boundary_point; x_axis_point++) {

            num_right_sided_boundary_crossings = 0;
            num_left_sided_boundary_crossings = 0;
            num_up_sided_boundary_crossings = 0;
            num_down_sided_boundary_crossings = 0;

            for(std::deque<int> vertical_boundary : vertical_boundaries) {
                if(x_axis_point > static_cast<std::size_t>(vertical_boundary.front())) {
                    num_right_sided_boundary_crossings++;
                }
                if(x_axis_point < static_cast<std::size_t>(vertical_boundary.back())) {
                    num_left_sided_boundary_crossings++;
                }
            }

            for(std::deque<int> horizontal_boundary : horizontal_boundaries_per_x_axis_point[static_cast<int>(x_axis_point)]) {
                if(y_axis_point > horizontal_boundary.front()) {
                    num_up_sided_boundary_crossings++;
                }
                if(y_axis_point < horizontal_boundary.back()) {
                    num_down_sided_boundary_crossings++;
                }
            }

            if((num_right_sided_boundary_crossings % 2 && num_left_sided_boundary_crossings % 2) || (num_up_sided_boundary_crossings % 2 && num_down_sided_boundary_crossings % 2)) {
                within_shape_points.push_back({static_cast<int>(x_axis_point), y_axis_point});
            }

        }
    }

    return within_shape_points;
}


std::vector<std::array<int, 2>> find_vertex_intersections(std::vector<std::array<int, 2>> vertices)
{
    std::size_t num_iterations {vertices.size() - 1};
    std::vector<std::array<int, 2>> intersections;
    std::array<int, 2>  first_tmp_vertex;
    std::array<int, 2> second_tmp_vertex;
    bool  first_tmp_vertex_not_already_a_vertex;
    bool second_tmp_vertex_not_already_a_vertex;
    bool  first_tmp_vertex_not_already_an_intersection;
    bool second_tmp_vertex_not_already_an_intersection;

    for(std::size_t iteration = 0; iteration < num_iterations; iteration++) {
        std::array<int, 2> current_vertex = vertices.back();
        for(std::array<int, 2> vertex : vertices) {

            first_tmp_vertex  = {current_vertex[0],         vertex[1]};
            second_tmp_vertex = {        vertex[0], current_vertex[1]};
            first_tmp_vertex_not_already_a_vertex  = std::find(vertices.begin(), vertices.end(),  first_tmp_vertex) == vertices.end();
            second_tmp_vertex_not_already_a_vertex = std::find(vertices.begin(), vertices.end(), second_tmp_vertex) == vertices.end();
            first_tmp_vertex_not_already_an_intersection  = std::find(intersections.begin(), intersections.end(),  first_tmp_vertex) == intersections.end();
            second_tmp_vertex_not_already_an_intersection = std::find(intersections.begin(), intersections.end(), second_tmp_vertex) == intersections.end();

            if(first_tmp_vertex_not_already_a_vertex && first_tmp_vertex_not_already_an_intersection) {
                intersections.push_back( first_tmp_vertex);
            }
            if(second_tmp_vertex_not_already_a_vertex && second_tmp_vertex_not_already_an_intersection) {
                intersections.push_back(second_tmp_vertex);
            }
        }
        vertices.pop_back();
    }

    return intersections;
}


std::vector<double> wrap_angles(std::vector<double>& angles)
{
    std::vector<double> wrapped_angles (angles.size());

    int wraps {0};
    double current_angle;
    double previous_angle;
    double direct_angle_diff;
    double complementary_angle_diff;
    double shortest_angle_diff;

    for(std::size_t angle_index = 0; angle_index < angles.size(); angle_index++) {

        if(angle_index > 0) {

            current_angle  = angles[angle_index];
            previous_angle = angles[angle_index - 1];
            current_angle  +=  current_angle < 0 ? 360 : 0;
            previous_angle += previous_angle < 0 ? 360 : 0;

            direct_angle_diff = current_angle - previous_angle;
            complementary_angle_diff = (direct_angle_diff >= 0 ? -1 : 1)*(360 - std::abs(direct_angle_diff));
            shortest_angle_diff = std::abs(direct_angle_diff) < std::abs(complementary_angle_diff) ? direct_angle_diff : complementary_angle_diff;

            if(shortest_angle_diff > 0 ? current_angle < previous_angle : false) {
                wraps++;
            } else if (shortest_angle_diff <= 0 ? current_angle > previous_angle : false) {
                wraps--;
            }
        }

        wrapped_angles[angle_index] = angles[angle_index] + (angles[angle_index] < 0 ? 360 : 0);
        wrapped_angles[angle_index] += (wrapped_angles[angle_index] !=0 ? 360*wraps : 0);
    }

    return wrapped_angles;
}


int winding_number(const std::vector<std::array<int, 2>>& vertices,
                   const std::array<int, 2>& point)
{
    std::vector<double> angles (vertices.size());

    std::transform(vertices.begin(),
                   vertices.end(),
                   angles.begin(),
                   [&point](std::array<int, 2> vertex){ return (180/M_PI)*std::atan2(vertex[1] - point[1],
                                                                                     vertex[0] - point[0]); });

    angles.push_back(angles[0]);

    std::vector<double> wrapped_angles {wrap_angles(angles)};

    double winding_number = (std::reduce(wrapped_angles.begin() + 1, wrapped_angles.end()) - std::reduce(wrapped_angles.begin(), wrapped_angles.end() - 1))/360;

    return static_cast<int>(winding_number);
}


std::tuple<std::vector<std::array<int, 2>>,
		   std::vector<std::array<int, 2>>> Custom::Polygon::calculate_points(std::vector<std::array<int, 2>> vertices)
{

	std::vector<std::array<int, 2>> boundary_points;
	std::vector<std::array<int, 2>> extra_vertices;
	std::tie(boundary_points, extra_vertices) = calculate_boundary_points(vertices);
	for(std::array<int, 2> extra_vertex : extra_vertices) {
		vertices.push_back(extra_vertex);
	}

	std::vector<std::array<int, 2>> within_boundary_points {even_odd_ray_casting(boundary_points)};

	for(std::array<int, 2> intersection : find_vertex_intersections(vertices)) {
		if(winding_number(vertices, intersection) != 0) {
			within_boundary_points.push_back(intersection);
		}
	}

	return {boundary_points,
			within_boundary_points};
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
