#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Misc.hpp"


std::vector<double> Math::Misc::wrap_angles(std::vector<double>& angles)
{
    std::vector<double> wrapped_angles (angles.size());

    int wraps {0};
    double current_angle;
    double previous_angle;
    double direct_angle_diff;
    double complementary_angle_diff;
    double shortest_angle_diff;

    for(std::size_t angle_index = 0; angle_index < angles.size(); angle_index++) {

        if(angle_index > 0) {

            current_angle  = angles[angle_index];
            previous_angle = angles[angle_index - 1];
            current_angle  +=  current_angle < 0 ? 360 : 0;
            previous_angle += previous_angle < 0 ? 360 : 0;

            direct_angle_diff = current_angle - previous_angle;
            complementary_angle_diff = (direct_angle_diff >= 0 ? -1 : 1)*(360 - std::abs(direct_angle_diff));
            shortest_angle_diff = std::abs(direct_angle_diff) < std::abs(complementary_angle_diff) ? direct_angle_diff : complementary_angle_diff;

            if(shortest_angle_diff > 0 ? current_angle < previous_angle : false) {
                wraps++;
            } else if (shortest_angle_diff <= 0 ? current_angle > previous_angle : false) {
                wraps--;
            }
        }

        wrapped_angles[angle_index] = angles[angle_index] + (angles[angle_index] < 0 ? 360 : 0);
        wrapped_angles[angle_index] += (wrapped_angles[angle_index] !=0 ? 360*wraps : 0);
    }

    return wrapped_angles;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
