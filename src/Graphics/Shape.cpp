#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Shape.hpp"


std::tuple<std::vector<std::array<int, 2>>,
		   std::vector<std::array<int, 2>>> Graphics::Shape::polygon(std::vector<std::array<int, 2>> vertices)
{
    const auto& [boundary_points, extra_vertices] = Contour::polygon(vertices);

	for(std::array<int, 2> extra_vertex : extra_vertices) {
		vertices.push_back(extra_vertex);
	}

	std::vector<std::array<int, 2>> within_boundary_points {PointInContour::even_odd_ray_casting(boundary_points)};

	for(std::array<int, 2> intersection : PointInContour::find_vertex_intersections(vertices)) {
		if(PointInContour::winding_number(vertices, intersection) != 0) {
			within_boundary_points.push_back(intersection);
		}
	}

	return {boundary_points,
			within_boundary_points};
}


std::tuple<std::vector<std::array<int, 2>>,
           std::vector<std::array<int, 2>>> Graphics::Shape::circle(int radius, const std::array<int, 2>& center)
{
    std::vector<std::array<int, 2>> boundary_points {Contour::circle(radius, center)};
    std::vector<std::array<int, 2>> within_boundary_points {PointInContour::even_odd_ray_casting(boundary_points)};

    return {boundary_points, within_boundary_points};
}


std::tuple<std::vector<std::array<int, 2>>,
           std::vector<std::array<int, 2>>> Graphics::Shape::ellipse(int x_axis_radius,
															 	     int y_axis_radius,
																     std::array<int, 2> center)
{
    std::vector<std::array<int, 2>> boundary_points {Contour::ellipse(x_axis_radius, y_axis_radius, center)};
    std::vector<std::array<int, 2>> within_boundary_points {PointInContour::even_odd_ray_casting(boundary_points)};

    return {boundary_points, within_boundary_points};
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
