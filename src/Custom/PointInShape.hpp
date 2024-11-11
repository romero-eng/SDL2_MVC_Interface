#ifndef POINT_IN_SHAPE_H
#define POINT_IN_SHAPE_H

// C++ Standard Libraries
#include <stdexcept>
#include <vector>
#include <array>
#include <map>
#include <deque>
#include <cmath>
#include <algorithm>
#include <numeric>

std::vector<std::array<int, 2>> custom_calculate_line_points(const std::array<std::array<int, 2>, 2>& line);

namespace Custom {

    namespace PointInShape {    

        std::vector<std::array<int, 2>> calculate_polygon_boundary_points(std::vector<std::array<int, 2>>& vertices);

        std::vector<std::array<int, 2>> double_sided_even_odd_ray_casting(bool orthogonal_axis_first,
                                                                          const std::vector<std::array<int, 2>>& boundary_points,
		    															  const std::optional<std::vector<std::array<int, 2>>>& orthogonal_axis_points = std::nullopt);

        std::vector<double> wrap_angles(std::vector<double>& angles);

        int calculate_winding_number(const std::vector<std::array<int, 2>>& vertices,
                                     const std::array<int, 2>& point);

        std::vector<std::array<int, 2>> calculate_intersections(std::vector<std::array<int, 2>> vertices);

    }

}

#endif
