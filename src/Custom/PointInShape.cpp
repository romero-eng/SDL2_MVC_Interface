#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "PointInShape.hpp"


std::vector<std::array<int, 2>> Custom::PointInShape::calculate_polygon_boundary_points(std::vector<std::array<int, 2>>& vertices)
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

	for(std::array<std::array<int, 2>, 2> line : lines) {

		tmp_boundary_points = custom_calculate_line_points(line);
		tmp_boundary_points = std::vector<std::array<int, 2>> (tmp_boundary_points.begin(), tmp_boundary_points.end() - 1);

		for(std::array<int, 2> potential_vertex : tmp_boundary_points) {
			for(int x : {-1, 0, 1}){
				for(int y : {-1, 0, 1}) {
					if(!(x == 0 && y == 0)) {

						tmp_point = {potential_vertex[0] + x, potential_vertex[1] + y};

						if(std::find(boundary_points.begin(), boundary_points.end(), tmp_point) != boundary_points.end()) {
							if(std::find(vertices.begin(), vertices.end(), tmp_point) == vertices.end()) {
								vertices.push_back(potential_vertex);
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

	return boundary_points;
}


std::vector<std::array<int, 2>> Custom::PointInShape::double_sided_even_odd_ray_casting(bool orthogonal_axis_first,
                                                                                        const std::vector<std::array<int, 2>>& boundary_points,
															    	    	            const std::optional<std::vector<std::array<int, 2>>>& orthogonal_axis_points)
{

	// Initialization of numerous variables needed for up-coming for loops

    bool not_found;
    bool boundary_crossed_from_back;
    bool boundary_crossed_from_front;

    std::vector<std::array<int, 2>> within_shape_points;
    int num_boundary_crossings;
    int num_boundary_crossings_reversed;

    std::size_t orthogonal_axis {static_cast<std::size_t>(orthogonal_axis_first ?  0 : 1)};
    std::size_t scanning_axis {static_cast<std::size_t>(orthogonal_axis_first ? 1 : 0)};

	std::size_t min_boundary_point;
	std::size_t max_boundary_point;
	bool keep_going;

	// Reorganize the boundary points from coordinates into scan line boundary points
	// mapped to corresponding orthogonal axis points.
    std::map<int, std::vector<int>> reorganized_boundary_points;
    for(std::array<int, 2> point : boundary_points) {
        if(reorganized_boundary_points.contains(point[orthogonal_axis])) {
            reorganized_boundary_points[point[orthogonal_axis]].push_back(point[scanning_axis]);
        } else {
            reorganized_boundary_points.emplace(point[orthogonal_axis], std::vector<int> {point[scanning_axis]});
        }
    }

	// If currently existing filled-in shape points were given, reorganize them from
	// points from coordinates into scan line boundary points mapped to corresponding
	// orthogonal axis points
	std::map<int, std::vector<int>> reorganized_orthogonal_axis_points;
	if(orthogonal_axis_points.has_value()) {
		for(std::array<int, 2> point : orthogonal_axis_points.value()){
			if(reorganized_orthogonal_axis_points.contains(point[orthogonal_axis])) {
				reorganized_orthogonal_axis_points[point[orthogonal_axis]].push_back(point[scanning_axis]);
			} else {
				reorganized_orthogonal_axis_points.emplace(point[orthogonal_axis], std::vector<int> {point[scanning_axis]});
			}
		}
		within_shape_points = orthogonal_axis_points.value();
	}

	// For each orthogonal axis point and it's corresponding scan line boundary points,...
    for(auto& [orthogonal_axis_constant, scanning_axis_boundary_points] : reorganized_boundary_points) {

        std::vector<std::deque<int>> boundaries;

		// Make sure the scan line boundary points are not repeated/duplicated

        std::sort(scanning_axis_boundary_points.begin(),
                  scanning_axis_boundary_points.end());

        scanning_axis_boundary_points.erase(std::unique(scanning_axis_boundary_points.begin(),
                                                        scanning_axis_boundary_points.end()),
                                            scanning_axis_boundary_points.end());

		// Collate each boundary point along the axis into boundaries, where each boundary is
		// implemented as a deque of integers sorted in ascending order from back to front
        for(int boundary_point : scanning_axis_boundary_points) {
            if(boundaries.size() > 0) {

                not_found = true;
                std::size_t index = 0;
                while(index < boundaries.size() && not_found) {
                
                    boundary_crossed_from_back  = boundary_point == boundaries[index].back()  - 1;
                    boundary_crossed_from_front = boundary_point == boundaries[index].front() + 1;

                    if(boundary_crossed_from_back || boundary_crossed_from_front) {

                    not_found = false;

                        if(boundary_crossed_from_back) {
                            boundaries[index].push_back(boundary_point);
                        } else {
                            boundaries[index].push_front(boundary_point);
                        }
                    }

                index++;
                }
                if(not_found) {
                    boundaries.push_back(std::deque<int> {boundary_point});
                }

            } else {
                boundaries.push_back(std::deque<int> {boundary_point});
            }
        }

		min_boundary_point = \
			static_cast<std::size_t>(*std::min_element(scanning_axis_boundary_points.begin(),
													   scanning_axis_boundary_points.end()));

		max_boundary_point = \
			static_cast<std::size_t>(*std::max_element(scanning_axis_boundary_points.begin(),
							 						   scanning_axis_boundary_points.end()));

		// This for-loop is the most important loop, and is the main workhorse of this function.
		// For each point from the minimum to the maximum boundary point along the scan line,
		// determine if each individual point lies between a pair of boundaries.
        for(std::size_t point = min_boundary_point; point < max_boundary_point; point++) {

			// If no extra set of already-filled-in coordinates were given, keep going.
			// If already-filled-in coordinates were actually given, check to make sure that the
			// current point is not already within those filled-in-coordinates.
			keep_going = true;
			if(reorganized_orthogonal_axis_points.size() > 0){
				keep_going = std::find(reorganized_orthogonal_axis_points[orthogonal_axis_constant].begin(),
									   reorganized_orthogonal_axis_points[orthogonal_axis_constant].end(),
						  			   point) == reorganized_orthogonal_axis_points[orthogonal_axis_constant].end();
			}

			if(keep_going) {

            	num_boundary_crossings = 0;
            	num_boundary_crossings_reversed = 0;

            	for(std::deque<int> boundary : boundaries) {
                	if(point > static_cast<std::size_t>(boundary.front())) {
                    	num_boundary_crossings++;
                	}
                	if(point < static_cast<std::size_t>(boundary.back())) {
                    	num_boundary_crossings_reversed++;
                	}
            	}

            	if(num_boundary_crossings % 2 && num_boundary_crossings_reversed % 2) {
                	if(orthogonal_axis_first) {
                    	within_shape_points.push_back({orthogonal_axis_constant, static_cast<int>(point)});
                	} else {
                    	within_shape_points.push_back({static_cast<int>(point), orthogonal_axis_constant});
                	}
            	}
			}
        }
    }

    return within_shape_points;
}


std::vector<double> Custom::PointInShape::wrap_angles(std::vector<double>& angles)
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


int Custom::PointInShape::calculate_winding_number(const std::vector<std::array<int, 2>>& vertices,
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


std::vector<std::array<int, 2>> Custom::PointInShape::calculate_intersections(std::vector<std::array<int, 2>> vertices)
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


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
