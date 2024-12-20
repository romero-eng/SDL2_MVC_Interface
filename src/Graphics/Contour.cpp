#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Contour.hpp"


std::vector<std::array<int, 2>> Graphics::Contour::line(const std::array<std::array<int, 2>, 2>& line)
{
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


std::vector<std::array<int, 2>> Graphics::Contour::circle(int radius,
                                                          const std::array<int, 2>& center)
{
	const int threshold {1 - (radius*radius << 2)};
	const std::size_t N {static_cast<std::size_t>(radius/std::sqrt(2)) + 1};

	std::vector<int> x (N + 1);
	x[0] = radius;

    for(std::size_t n = 0; n < N; n++) {
        x[n + 1] = x[n] - (((x[n] - static_cast<int>((n + 1)*(n + 1)) - x[n]*x[n]) << 2) < threshold ? 1 : 0);
    }

	std::vector<std::array<int, 2>> points (8*(N + 1));
    for(std::size_t i = 0; i < N + 1; i++) {
        points[8*i    ] = { 			   x[i] + center[0],  static_cast<int>(i) + center[1]}; //   first octant
        points[8*i + 1] = { static_cast<int>(i) + center[0],  			     x[i] + center[1]}; //  second octant
        points[8*i + 2] = {-static_cast<int>(i) + center[0],  			     x[i] + center[1]}; //   third octant
        points[8*i + 3] = {				  -x[i] + center[0],  static_cast<int>(i) + center[1]}; //  fourth octant
        points[8*i + 4] = {				  -x[i] + center[0], -static_cast<int>(i) + center[1]}; //   fifth octant
        points[8*i + 5] = {-static_cast<int>(i) + center[0], 				-x[i] + center[1]}; //   sixth octant
        points[8*i + 6] = { static_cast<int>(i) + center[0], 				-x[i] + center[1]}; // seventh octant
        points[8*i + 7] = { 			   x[i] + center[0], -static_cast<int>(i) + center[1]}; //  eighth octant
    }

    return points;
}


std::vector<std::array<int, 2>> Graphics::Contour::ellipse(int x_axis_radius,
													 	   int y_axis_radius,
														   std::array<int, 2> center)
{
	const int x_axis_radius_squared {x_axis_radius*x_axis_radius};
	const int y_axis_radius_squared {y_axis_radius*y_axis_radius};
	const int composite_radius_squared {x_axis_radius_squared*y_axis_radius_squared};
	const int first_octant_threshold {y_axis_radius_squared - (composite_radius_squared << 2)};
	const int second_octant_threshold {x_axis_radius_squared - (composite_radius_squared << 2)};
	const double composite_radius_norm {std::sqrt(x_axis_radius_squared + y_axis_radius_squared)};
	const std::size_t N {static_cast<std::size_t>(y_axis_radius_squared/composite_radius_norm) + 1};
	const std::size_t M {static_cast<std::size_t>(x_axis_radius_squared/composite_radius_norm) + 1};
	const std::size_t offset {N + 1};
	const std::size_t I {offset + M + 1};

	std::vector<std::array<int, 2>> points (4*I);
	std::vector<std::array<int, 2>> first_quadrant_points (I);
	first_quadrant_points[0] = {x_axis_radius, 0};
	first_quadrant_points[N + 1] = {0, y_axis_radius};

	// First Octant
	for(std::size_t n = 0; n < N; n++) {
		first_quadrant_points[n + 1] = \
			{first_quadrant_points[n][0] - (((y_axis_radius_squared*first_quadrant_points[n][0] - x_axis_radius_squared*static_cast<int>((n + 1)*(n + 1)) - y_axis_radius_squared*first_quadrant_points[n][0]*first_quadrant_points[n][0]) << 2) < first_octant_threshold ? 1 : 0),
			 static_cast<int>(n + 1)};
	}

	// Second Octant
	for(std::size_t m = 0; m < M; m++) {
		first_quadrant_points[m + 1 + offset] = \
			{static_cast<int>(m + 1),
			 first_quadrant_points[m + offset][1] - (((x_axis_radius_squared*first_quadrant_points[m + offset][1] - y_axis_radius_squared*static_cast<int>((m + 1)*(m + 1)) - x_axis_radius_squared*first_quadrant_points[m + offset][1]*first_quadrant_points[m + offset][1]) << 2) < second_octant_threshold ? 1 : 0)};
	}

	// All Quadrants
	for(std::size_t i = 0; i < I; i++) {
		points[4*i    ] = { first_quadrant_points[i][0] + center[0],  first_quadrant_points[i][1] + center[1]};
		points[4*i + 1] = {-first_quadrant_points[i][0] + center[0],  first_quadrant_points[i][1] + center[1]};
		points[4*i + 2] = {-first_quadrant_points[i][0] + center[0], -first_quadrant_points[i][1] + center[1]};
		points[4*i + 3] = { first_quadrant_points[i][0] + center[0], -first_quadrant_points[i][1] + center[1]};
	}

	return points;
}


std::tuple<std::vector<std::array<int, 2>>,
           std::vector<std::array<int, 2>>> Graphics::Contour::polygon(const std::vector<std::array<int, 2>>& vertices)
{
	if(vertices.size() < 3) {
		throw std::runtime_error("A polygon can only be defined with a minimum of three vertices");
	}

	std::vector<std::array<std::array<int, 2>, 2>> lines;

	for(std::size_t i = 0; i < vertices.size() - 1; i++) {
		lines.push_back({vertices[i], vertices[i + 1]});
	}
	lines.push_back({vertices[vertices.size() - 1], vertices[0]});

	std::vector<std::array<int, 2>> all_boundary_points;
	std::array<int, 2> current_boundary_point;
	std::vector<std::array<int, 2>> current_boundary_points;
    std::vector<std::array<int, 2>> extra_vertices;

	for(std::array<std::array<int, 2>, 2> current_line : lines) {

		current_boundary_points = line(current_line);
		current_boundary_points = std::vector<std::array<int, 2>> (current_boundary_points.begin(), current_boundary_points.end() - 1);

		for(std::array<int, 2> potential_vertex : current_boundary_points) {
			for(int x : {-1, 0, 1}){
				for(int y : {-1, 0, 1}) {
					if(!(x == 0 && y == 0)) {

						current_boundary_point = {potential_vertex[0] + x, potential_vertex[1] + y};

						if(std::find(all_boundary_points.begin(), all_boundary_points.end(), current_boundary_point) != all_boundary_points.end()) {
							if(std::find(vertices.begin(), vertices.end(), current_boundary_point) == vertices.end()) {
								extra_vertices.push_back(potential_vertex);
							}

						}
					}
				}
			}
		}

		for(std::array<int, 2> boundary_point : current_boundary_points) {
			all_boundary_points.push_back(boundary_point);
		}

	}

	return {all_boundary_points, extra_vertices};
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
