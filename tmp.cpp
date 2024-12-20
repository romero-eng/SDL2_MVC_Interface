#include <array>
#include <iostream>
#include <fmt/format.h>


void ellipse(int x_axis_radius,
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
    double y_norm {std::sqrt(y_norm)};
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
         &right](double y){return -A_y*y + B_y*std::sqrt(y_norm_sq - y*y) + (y <= lower*B ? 1 : -1)*lower*right*std::sqrt(C_y - D_y*y*y + 2*E_y*y*std::sqrt(y_norm_sq - y*y));};

    //std::cout << y(0) << std::endl;
    //std::cout << y(-2) << std::endl;
    //std::cout << y(2) << std::endl;
    //std::cout << x(0) << std::endl;
    //std::cout << x(1) << std::endl;
    //std::cout << x(-1) << std::endl;
    std::cout << dy_dx(-2.6) << std::endl;
    std::cout << dy_dx(2) << std::endl;

}


int main()
{
    ellipse(2, 5, 30, 0, 0);

    return 1;
}
