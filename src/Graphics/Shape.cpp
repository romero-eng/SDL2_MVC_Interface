#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Shape.hpp"


std::vector<std::array<int, 2>> calculate_line_points(const std::array<std::array<int, 2>, 2>& line)
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


std::vector<std::array<int, 2>> calculate_circle_boundary_points(int radius, const std::array<int, 2>& center)
{
    int next_x;
    bool decrement_by_one;
    bool keep_going {true};

	std::vector<int> x;
	x.push_back(radius);

    while(keep_going) {

        decrement_by_one = ((radius*radius - static_cast<int>(x.size()*x.size()) - x[x.size() - 1]*x[x.size() - 1] + x[x.size() - 1]) << 2) < 1;
        next_x = x[x.size() - 1] - (decrement_by_one ? 1 : 0);
        keep_going = next_x >= static_cast<int>(x.size());

        if(keep_going) {
            x.push_back(next_x);
        }
    }

	std::vector<std::array<int, 2>> points (8*x.size());
    for(std::size_t i = 0; i < x.size(); i++) {
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


std::tuple<std::vector<std::array<int, 2>>,
           std::vector<std::array<int, 2>>> calculate_polygon_boundary_points(const std::vector<std::array<int, 2>>& vertices)
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


std::tuple<std::vector<std::array<int, 2>>,
		   std::vector<std::array<int, 2>>> Graphics::Shape::calculate_polygon_points(std::vector<std::array<int, 2>> vertices)
{
    const auto& [boundary_points, extra_vertices] = calculate_polygon_boundary_points(vertices);

	for(std::array<int, 2> extra_vertex : extra_vertices) {
		vertices.push_back(extra_vertex);
	}

	std::vector<std::array<int, 2>> within_boundary_points {PointInShape::even_odd_ray_casting(boundary_points)};

	for(std::array<int, 2> intersection : PointInShape::find_vertex_intersections(vertices)) {
		if(PointInShape::winding_number(vertices, intersection) != 0) {
			within_boundary_points.push_back(intersection);
		}
	}

	return {boundary_points,
			within_boundary_points};
}


std::tuple<std::vector<std::array<int, 2>>,
           std::vector<std::array<int, 2>>> Graphics::Shape::calculate_circle_points(int radius,
                                                                                     const std::array<int, 2>& center)
{
    std::vector<std::array<int, 2>> boundary_points {calculate_circle_boundary_points(radius, center)};
    std::vector<std::array<int, 2>> within_boundary_points {PointInShape::even_odd_ray_casting(boundary_points)};

    return {boundary_points, within_boundary_points};
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
