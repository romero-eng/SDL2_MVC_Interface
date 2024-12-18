#include <iostream>
#include <fmt/format.h>


int main()
{
    double theta_deg_1 {45};
    double theta_deg_2 {-125};
    std::cout << fmt::format("{:f}", (M_PI/180)*(std::fmod(theta_deg_1, 360) + (theta_deg_1 > 0 ? 0 : 360))) << std::endl;
    std::cout << fmt::format("{:f}", (M_PI/180)*(std::fmod(theta_deg_2, 360) + (theta_deg_2 > 0 ? 0 : 360))) << std::endl;
    return 1;
}
