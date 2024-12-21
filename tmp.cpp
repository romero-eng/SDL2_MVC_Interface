#include <fmt/format.h>

#include <array>
#include <vector>
#include <algorithm>
#include <iostream>


std::ostream& operator<<(std::ostream& output, std::vector<std::array<int, 2>> points)
{
    std::vector<std::string> point_strings (points.size());

    std::transform(points.begin(),
                   points.end(),
                   point_strings.begin(),
                   [](std::array<int, 2> point){return fmt::format("({:d}, {:d})", point[0], point[1]);});

    output << fmt::format("{:s}", fmt::join(point_strings, "\n"));

    return output;
}


std::vector<std::array<int, 2>> rotated_ellipse(int x_axis_radius,
                                                int y_axis_radius,
                                                double theta_deg,
                                                int x_c,
                                                int y_c)
{
    double theta_rad {(M_PI/180)*(std::fmod(theta_deg, 360) + (theta_deg > 0 ? 0 : 360))};

    double a {static_cast<double>(x_axis_radius)};
    double b {static_cast<double>(y_axis_radius)};
    double a_sq {a*a};
    double b_sq {b*b};
    double A {a*std::cos(theta_rad)};
    double B {b*std::cos(theta_rad)};
    double term_1 {static_cast<double>(a_sq/(a_sq + b_sq))};
    double term_2 {static_cast<double>(b_sq/(a_sq + b_sq))};
    double sin_2_theta {std::sin(2*theta_rad)};
    double cos_2_theta {std::cos(2*theta_rad)};

    double x_norm_sq {(static_cast<double>(a_sq - b_sq)/2)*(1 + cos_2_theta) + b_sq};
    double x_norm {std::sqrt(x_norm_sq)};
    double A_x {a_sq*sin_2_theta/(2*x_norm_sq)};
    double B_x {a*b*(1 - cos_2_theta)/(2*x_norm_sq)};
    double C_x {a_sq*b_sq*std::pow(1 + cos_2_theta, 2)/(4*x_norm_sq)};
    double D_x {(b_sq)*(a_sq + b_sq)*(std::pow(term_1 + cos_2_theta, 2) - std::pow(term_2, 2))/std::pow(2*x_norm_sq, 2)};\
    double E_x {a*b*b_sq*sin_2_theta*(1 + cos_2_theta)/std::pow(2*x_norm_sq, 2)};

    double y_norm_sq {(static_cast<double>(b_sq - a_sq)/2)*(1 + cos_2_theta) + a_sq};
    double A_y {b_sq*sin_2_theta/(2*y_norm_sq)};
    double B_y {a*b*(1 - cos_2_theta)/(2*y_norm_sq)};
    double C_y {a_sq*b_sq*std::pow(1 + cos_2_theta, 2)/(4*y_norm_sq)};
    double D_y {(a_sq)*(a_sq + b_sq)*(std::pow(term_2 + cos_2_theta, 2) - std::pow(term_1, 2))/std::pow(2*y_norm_sq, 2)};\
    double E_y {a*a_sq*b*sin_2_theta*(1 + cos_2_theta)/std::pow(2*y_norm_sq, 2)};

    int upper {theta_rad < M_PI ? 1 : -1};
    int lower {theta_rad > M_PI ? 1 : -1};
    int right {theta_rad <= M_PI/2 || theta_rad >= 3*M_PI/2 ? 1 : -1};

    auto y = \
        [&A,
         &A_x,
         &B_x,
         &C_x,
         &D_x,
         &E_x,
         &x_norm_sq,
         &upper,
         &right](double x){return A_x*x + B_x*std::sqrt(x_norm_sq - x*x) + (x <= upper*A ? 1 : -1)*upper*right*std::sqrt(C_x - D_x*x*x - 2*E_x*x*std::sqrt(x_norm_sq - x*x));};

    auto dy_dx = \
        [&A,
         &A_x,
         &B_x,
         &C_x,
         &D_x,
         &E_x,
         &x_norm_sq,
         &upper,
         &right](double x){return A_x - B_x*(x/std::sqrt(x_norm_sq - x*x)) - (x <= upper*A ? 1 : -1)*upper*right*((D_x*x - E_x*(2*x*x - x_norm_sq)/std::sqrt(x_norm_sq - x*x))/std::sqrt(C_x - D_x*x*x - 2*E_x*x*std::sqrt(x_norm_sq - x*x)));};

    auto x = \
        [&B,
         &A_y,
         &B_y,
         &C_y,
         &D_y,
         &E_y,
         &y_norm_sq,
         &lower,
         &right](double y, double sign){return -A_y*y + sign*B_y*std::sqrt(y_norm_sq - y*y) + sign*(y <= lower*B ? 1 : -1)*lower*right*std::sqrt(C_y - D_y*y*y + sign*2*E_y*y*std::sqrt(y_norm_sq - y*y));};

    auto dx_dy = \
        [&B,
         &A_y,
         &B_y,
         &C_y,
         &D_y,
         &E_y,
         &y_norm_sq,
         &lower,
         &right](double y, double sign){return -A_y - sign*B_y*y/std::sqrt(y_norm_sq - y*y) + sign*(y <= lower*B ? 1 : -1)*lower*right*((-D_y*y + sign*E_y*(y_norm_sq - 2*y*y)/std::sqrt(y_norm_sq - y*y))/std::sqrt(C_y - D_y*y*y + sign*2*E_y*y*std::sqrt(y_norm_sq - y*y)));};

    double y_slope;
    double x_slope;
    int y_slope_sign;
    int x_slope_sign;
    bool peaked;
    bool keep_going {true};
    double y_stop {y(x_norm)};

    std::vector<std::array<int, 2>> upper_arc_points;
    upper_arc_points.push_back({static_cast<int>(-std::floor(x_norm)), static_cast<int>(round(y(-std::floor(x_norm))))});

    while(keep_going) {

        y_slope = dy_dx(static_cast<double>(upper_arc_points[upper_arc_points.size() - 1][0]));
        x_slope = dx_dy(static_cast<double>(upper_arc_points[upper_arc_points.size() - 1][1]), -static_cast<double>(y_slope_sign));
        y_slope_sign = static_cast<int>(y_slope/std::abs(y_slope));
        x_slope_sign = static_cast<int>(x_slope/std::abs(x_slope));

        if (std::abs(y_slope) < std::abs(x_slope)) {
            upper_arc_points.push_back({upper_arc_points[upper_arc_points.size() - 1][0] + 1,
                              upper_arc_points[upper_arc_points.size() - 1][1] + y_slope_sign*(y_slope_sign*(y(static_cast<double>(upper_arc_points[upper_arc_points.size() - 1][0] + 1)) - static_cast<double>(upper_arc_points[upper_arc_points.size() - 1][1])) > 0.5 ? 1 : 0)});
        } else {
            upper_arc_points.push_back({upper_arc_points[upper_arc_points.size() - 1][0] + (x(static_cast<double>(upper_arc_points[upper_arc_points.size() - 1][1] + 1), -static_cast<double>(y_slope_sign)) - static_cast<double>(upper_arc_points[upper_arc_points.size() - 1][0]) > 0.5 ? 1 : 0),
                              upper_arc_points[upper_arc_points.size() - 1][1] + y_slope_sign});
        }

        if(!peaked){
            peaked = upper_arc_points[upper_arc_points.size() - 1][1] < upper_arc_points[upper_arc_points.size() - 2][1];
        } else {
            keep_going = upper_arc_points[upper_arc_points.size() - 1][1] > y_stop;
        }
    }

    std::cout << upper_arc_points << std::endl;

    std::vector<std::array<int, 2>> points (2*upper_arc_points.size());
    for(std::size_t n = 0; n < upper_arc_points.size(); n++) {
        points[2*n    ] = { upper_arc_points[n][0] + x_c,  upper_arc_points[n][1] + y_c};
        points[2*n + 1] = {-upper_arc_points[n][0] + x_c, -upper_arc_points[n][1] + y_c};
    }

    return points;
}


int main()
{
    std::cout << ellipse(20, 50, 10, 0, 0) << std::endl;

    return 1;
}
