#ifndef POLYGON_H
#define POLYGON_H

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

    namespace Shape {

        std::tuple<std::vector<std::array<int, 2>>,
		           std::vector<std::array<int, 2>>> calculate_polygon_points(std::vector<std::array<int, 2>> vertices);

        std::vector<std::array<int, 2>> calculate_circle_points(int r, int x_c, int y_c);

    }

}

#endif
