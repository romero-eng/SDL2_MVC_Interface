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

    namespace Polygon {

        std::tuple<std::vector<std::array<int, 2>>,
		           std::vector<std::array<int, 2>>> calculate_points(std::vector<std::array<int, 2>> vertices);

    }

}

#endif