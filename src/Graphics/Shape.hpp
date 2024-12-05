#ifndef POLYGON_H
#define POLYGON_H

// C++ Standard Libraries
#include <vector>
#include <array>

// Custom Code from this project
#include "PIC.hpp"
#include "Contour.hpp"


namespace Graphics {

    namespace Shape {

        std::tuple<std::vector<std::array<int, 2>>,
		           std::vector<std::array<int, 2>>> polygon(std::vector<std::array<int, 2>> vertices);

        std::tuple<std::vector<std::array<int, 2>>,
                   std::vector<std::array<int, 2>>> circle(int radius, const std::array<int, 2>& center);

    }

}

#endif
