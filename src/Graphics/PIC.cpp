#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "PIC.hpp"


std::map<int, std::vector<int>> map_2D_coordinates_to_scanlines(std::vector<std::array<int, 2>> points,
                                                                bool orthogonal_axis_first)
{
    std::size_t orthogonal_axis {static_cast<std::size_t>(orthogonal_axis_first ?  0 : 1)};

    std::map<int, std::vector<int>> scanline_per_orthogonal_axis_point;
    std::size_t scanning_axis = static_cast<std::size_t>(std::abs(static_cast<int>(orthogonal_axis) - 1));

    for(std::array<int, 2> point : points) {
        if(scanline_per_orthogonal_axis_point.contains(point[orthogonal_axis])) {
            scanline_per_orthogonal_axis_point[point[orthogonal_axis]].push_back(point[scanning_axis]);
        } else {
            scanline_per_orthogonal_axis_point.emplace(point[orthogonal_axis], std::vector<int> {point[scanning_axis]});
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


std::vector<std::array<int, 2>> Graphics::PointInContour::even_odd_ray_casting(const std::vector<std::array<int, 2>>& boundary_points)
{
    std::vector<std::array<int, 2>> within_shape_points;

    int num_right_sided_boundary_crossings;
    int num_left_sided_boundary_crossings;
    int num_up_sided_boundary_crossings;
    int num_down_sided_boundary_crossings;

    std::size_t min_x_axis_boundary_point;
    std::size_t max_x_axis_boundary_point;

    std::map<int, std::vector<int>> vertical_scanline_per_y_axis_point {map_2D_coordinates_to_scanlines(boundary_points, false)};
    std::map<int, std::vector<std::deque<int>>> horizontal_boundaries_per_x_axis_point {collate_points_along_scanlines(map_2D_coordinates_to_scanlines(boundary_points, true))};

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


std::vector<std::array<int, 2>> Graphics::PointInContour::find_vertex_intersections(std::vector<std::array<int, 2>> vertices)
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


int Graphics::PointInContour::winding_number(const std::vector<std::array<int, 2>>& vertices,
                                             const std::array<int, 2>& point)
{
    std::vector<double> angles (vertices.size());

    std::transform(vertices.begin(),
                   vertices.end(),
                   angles.begin(),
                   [&point](std::array<int, 2> vertex){ return (180/M_PI)*std::atan2(vertex[1] - point[1],
                                                                                     vertex[0] - point[0]); });

    angles.push_back(angles[0]);

    std::vector<double> wrapped_angles {Math::Misc::wrap_angles(angles)};

    double winding_number = (std::reduce(wrapped_angles.begin() + 1, wrapped_angles.end()) - std::reduce(wrapped_angles.begin(), wrapped_angles.end() - 1))/360;

    return static_cast<int>(winding_number);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
