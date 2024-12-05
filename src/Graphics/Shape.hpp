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

// Custom Code from this project
#include "PIS.hpp"
#include "Contour.hpp"


namespace Graphics {

    namespace Shape {

        std::tuple<std::vector<std::array<int, 2>>,
		           std::vector<std::array<int, 2>>> calculate_polygon_points(std::vector<std::array<int, 2>> vertices);

        std::tuple<std::vector<std::array<int, 2>>,
                   std::vector<std::array<int, 2>>> calculate_circle_points(int radius,
                                                                            const std::array<int, 2>& center);

    }

}

#endif
