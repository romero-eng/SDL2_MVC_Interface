#ifndef POINT_IN_SHAPE_H
#define POINT_IN_SHAPE_H

// C++ Standard Libraries
#include <array>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <numeric>
#include <cmath>


namespace Graphics
{
    namespace PointInShape
    {
        std::vector<std::array<int, 2>> even_odd_ray_casting(const std::vector<std::array<int, 2>>& boundary_points);

        std::vector<std::array<int, 2>> find_vertex_intersections(std::vector<std::array<int, 2>> vertices);

        int winding_number(const std::vector<std::array<int, 2>>& vertices,
                           const std::array<int, 2>& point);
    }
}

#endif
