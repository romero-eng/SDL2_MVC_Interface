#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "Logging/Logfile.hpp"
#include "SDML/Subsystem.hpp"
#include "SDML/Image.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Surface.hpp"
#include "SDML/Video/Renderer.hpp"
#include "SDML/Video/Texture.hpp"
#include "SDML/Events/Event.hpp"
#include "SDML/Events/EventMisc.hpp"

// C++ Standard Libraries
#include <filesystem>
#include <iostream>
#include <memory>
#include <deque>
#include <numeric>


constexpr std::string LOGFILE_NAME {"Test"};
constexpr std::string WINDOW_TITLE {"Test"};
constexpr std::array<int, 2> WINDOW_AREA {640, 480};
constexpr std::array<uint8_t, 3> WHITE {0xFF, 0xFF, 0xFF};
constexpr std::array<uint8_t, 3> BLACK {0x00, 0x00, 0x00};
constexpr std::array<uint8_t, 3> RED {0xFF, 0x00, 0x00};


std::array<double, 2> operator+(const std::array<double, 2>& first_vector,
								const std::array<double, 2>& second_vector) {
	return {first_vector[0] + second_vector[0],
			first_vector[1] + second_vector[1]};
}


double operator*(const std::array<double, 2>& first_vector,
								const std::array<double, 2>& second_vector) {
	return {first_vector[0]*second_vector[0] + first_vector[1]*second_vector[1]};
}


std::array<double, 2> operator*(const std::array<std::array<double, 2>, 2>& matrix,
								const std::array<double, 2>& vector) {
	return {matrix[0]*vector, matrix[1]*vector};
}


std::vector<std::array<int, 2>> custom_calculate_line_points(const std::array<std::array<int, 2>, 2>& line)
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


std::vector<std::array<int, 2>> custom_calculate_polygon_boundary_points(const std::vector<std::array<int, 2>> vertices)
{
	if(vertices.size() < 3) {
		throw std::runtime_error("A polygon can only be defined with a minimum of three vertices");
	}

	std::vector<std::array<std::array<int, 2>, 2>> lines;

	for(std::size_t i = 0; i < vertices.size() - 1; i++) {
		lines.push_back({vertices[i], vertices[i + 1]});
	}
	lines.push_back({vertices[vertices.size() - 1], vertices[0]});

	std::vector<std::array<int, 2>> points;
	std::vector<std::array<int, 2>> tmp_points;
	for(std::array<std::array<int, 2>, 2> line : lines) {
		tmp_points = custom_calculate_line_points(line);
		for(std::array<int, 2> point : std::vector<std::array<int, 2>> (tmp_points.begin(), tmp_points.end() - 1)) {
			points.push_back(point);
		}
	}

	return points;
}


std::vector<std::array<int, 2>> custom_double_sided_even_odd_ray_casting(bool orthogonal_axis_first,
                                                                         const std::vector<std::array<int, 2>>& boundary_points,
																	     const std::optional<std::vector<std::array<int, 2>>>& orthogonal_axis_points = std::nullopt)
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
                	if(point > boundary.front()) {
                    	num_boundary_crossings++;
                	}
                	if(point < boundary.back()) {
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


std::vector<double> custom_wrap_angles(std::vector<double>& angles) {

    std::vector<double> wrapped_angles (angles.size());

    int wraps {0};
    double current_angle;
    double previous_angle;
    double direct_angle_diff;
    double complementary_angle_diff;
    double shortest_angle_diff;
    bool counter_clockwise_wrap;
    bool clockwise_wrap;

    for(std::size_t angle_index = 0; angle_index < angles.size(); angle_index++) {

        if(angle_index > 0) {

            /*
            ============================================================================================================================
            ============================================================================================================================
            */

            current_angle  = angles[angle_index];
            previous_angle = angles[angle_index - 1];
            current_angle  +=  current_angle < 0 ? 360 : 0;
            previous_angle += previous_angle < 0 ? 360 : 0;

            direct_angle_diff = current_angle - previous_angle;
            complementary_angle_diff = (direct_angle_diff >= 0 ? -1 : 1)*(360 - std::abs(direct_angle_diff));
            shortest_angle_diff = std::abs(direct_angle_diff) < std::abs(complementary_angle_diff) ? direct_angle_diff : complementary_angle_diff;

            counter_clockwise_wrap = shortest_angle_diff > 0 ? current_angle < previous_angle : false;
            clockwise_wrap = shortest_angle_diff <= 0 ? current_angle > previous_angle : false;

            if(counter_clockwise_wrap) {
                wraps++;
            } else if (clockwise_wrap) {
                wraps--;
            }
        }

        wrapped_angles[angle_index] = angles[angle_index] + (angles[angle_index] < 0 ? 360 : 0);
        wrapped_angles[angle_index] += (wrapped_angles[angle_index] !=0 ? 360*wraps : 0);
    }

    return wrapped_angles;
}


int custom_calculate_winding_number(const std::vector<std::array<int, 2>>& vertices,
                                const std::array<int, 2>& point)
{
    std::vector<double> angles (vertices.size());

    std::transform(vertices.begin(),
                   vertices.end(),
                   angles.begin(),
                   [&point](std::array<int, 2> vertex){ return (180/M_PI)*std::atan2(vertex[1] - point[1],
                                                                                     vertex[0] - point[0]); });

    angles.push_back(angles[0]);

    std::vector<double> wrapped_angles {custom_wrap_angles(angles)};

    double winding_number = (std::reduce(wrapped_angles.begin() + 1, wrapped_angles.end()) - std::reduce(wrapped_angles.begin(), wrapped_angles.end() - 1))/360;

    return static_cast<int>(winding_number);
}


std::vector<std::array<int, 2>> custom_calculate_intersections(std::vector<std::array<int, 2>> vertices)
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


std::vector<std::array<int, 2>> custom_round_double_vectors_to_int_vectors(const std::vector<std::array<double, 2>> double_vertices)
{
	std::vector<std::array<int, 2>> int_vertices (double_vertices.size());

	for(std::size_t n = 0; n < double_vertices.size(); n++){
		int_vertices[n] = {static_cast<int>(std::round(double_vertices[n][0])),
						   static_cast<int>(std::round(double_vertices[n][1]))};
	}

	return int_vertices;
}


std::array<std::array<double, 2>, 2> custom_rotation_matrix(double angle_degrees)
{
	double angle_radians {(M_PI/180)*angle_degrees};

	return {{{ std::cos(angle_radians), std::sin(angle_radians)},
			 {-std::sin(angle_radians), std::cos(angle_radians)}}};
}


std::vector<std::array<double, 2>> custom_translate_and_rotate_vectors(std::vector<std::array<double, 2>> vectors,
																	   double angle_degrees,
																	   std::array<double, 2> center)
{
	std::vector<std::array<double, 2>> new_vectors (vectors.size());
	std::array<std::array<double, 2>, 2> rotation_matrix {custom_rotation_matrix(angle_degrees)};

	for(std::size_t n = 0; n < vectors.size(); n++) {
		new_vectors[n] = rotation_matrix*vectors[n] + center;
	}

	return new_vectors;
}


std::tuple<std::vector<std::array<int, 2>>,
		   std::vector<std::array<int, 2>>> custom_calculate_arrow_boundary_points(double W_r,
																				   double W_t,
																				   double H_r,
																				   double H_t,
																				   std::array<double, 2> center,
																				   double angle_degrees)
{
	if(W_r <= W_t) {
		throw std::runtime_error("W_r must be greater than W_t");
	}

	std::vector<std::array<int, 2>> vertices {custom_round_double_vectors_to_int_vectors(custom_translate_and_rotate_vectors({{		      0, 	    H_r},
																															  {(W_r - W_t)/2, 	    H_r},
													 																		  {(W_r - W_t)/2,         0},
													 																		  {(W_r + W_t)/2,   	  0},
													 																		  {(W_r + W_t)/2, 	    H_r},
													 																		  {	   	     W_r, 	    H_r},
													 																		  {	 	   W_r/2, H_r + H_t}},
																															 angle_degrees,
																															 center))};

	std::vector<std::array<int, 2>> boundary_points {custom_calculate_polygon_boundary_points(vertices)};

	std::vector<std::array<int, 2>> within_boundary_points {custom_double_sided_even_odd_ray_casting(false, boundary_points)};
	within_boundary_points = custom_double_sided_even_odd_ray_casting(true, boundary_points, within_boundary_points);

	for(std::array<int, 2> intersection : custom_calculate_intersections(vertices)) {
		if(custom_calculate_winding_number(vertices, intersection) != 0) {
			within_boundary_points.push_back(intersection);
		}
	}

	return {boundary_points,
			within_boundary_points};
}


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(LOGFILE_NAME, SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS);

	try {

		const auto& [arrow_boundary_points, arrow_within_boundary_points] = custom_calculate_arrow_boundary_points(50, 20, 40, 20, {50, 100}, 30);

		SDML::Video::Window canvas {WINDOW_TITLE, WINDOW_AREA};
		SDML::Video::Renderer paintbrush {canvas};
		paintbrush.SetDrawingColor(WHITE);
		paintbrush.DrawEntireTarget();
		paintbrush.SetDrawingColor(BLACK);
		paintbrush.DrawPoints(arrow_boundary_points);
		paintbrush.DrawPoints(arrow_within_boundary_points);
		paintbrush.SetDrawingColor(RED);
		//paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{0, 110}, {WINDOW_AREA[0], 110}}});
		//paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{0, 111}, {WINDOW_AREA[0], 111}}});
		//paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{0, 117}, {WINDOW_AREA[0], 117}}});
		//paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{0, 135}, {WINDOW_AREA[0], 135}}});
		//paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{0, 93}, {WINDOW_AREA[0], 93}}});
		//paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{83, 0}, {83, WINDOW_AREA[1]}}});

		//paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{96, 0}, {96, WINDOW_AREA[1]}}});
		//paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{113, 0}, {113, WINDOW_AREA[1]}}});
		paintbrush.Update();
		
		std::optional<std::unique_ptr<SDML::Events::Event>> current_event;
		bool quit = false;

		while(!quit) {
			current_event = SDML::Events::PollEvent();
			while(current_event.has_value()){
				quit = quit ? quit : current_event.value()->Quit();
				current_event = SDML::Events::PollEvent();
			}
		}

	}
	catch(const std::exception& error_message)
	{
		std::cerr << error_message.what() << std::endl;
		Logging::MainLogFile.Write(error_message.what());
	}

	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
