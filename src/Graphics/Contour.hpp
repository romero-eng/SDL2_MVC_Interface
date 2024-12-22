#ifndef CONTOUR_H
#define CONTOUR_H

// C++ Standard Libraries
#include <stdexcept>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>


namespace Graphics
{
    namespace Contour
    {
        std::vector<std::array<int, 2>> line(const std::array<std::array<int, 2>, 2>& line);

        std::vector<std::array<int, 2>> circle(int radius,
                                               const std::array<int, 2>& center);

        std::vector<std::array<int, 2>> ellipse(int x_axis_radius,
		    	    						 	int y_axis_radius,
			    	    						std::array<int, 2> center);

        std::vector<std::array<int, 2>> rotated_ellipse(int x_axis_radius,
                                                        int y_axis_radius,
                                                        double theta_deg,
                                                        std::array<int, 2> center);

        std::tuple<std::vector<std::array<int, 2>>,
                   std::vector<std::array<int, 2>>> polygon(const std::vector<std::array<int, 2>>& vertices);
    }
}


#endif
