#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "Logging/Logfile.hpp"
#include "SDML/Subsystem.hpp"
#include "SDML/Image.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Surface.hpp"
#include "SDML/Video/Renderer.hpp"
#include "SDML/Video/Texture.hpp"
#include "SDML/Events/Event.hpp"
#include "SDML/Events/EventMisc.hpp"
#include "Math/LinearAlgebra.hpp"
#include "Graphics/Shape.hpp"

// C++ Standard Libraries
#include <filesystem>
#include <iostream>
#include <memory>
#include <deque>
#include <numeric>


constexpr std::string LOGFILE_NAME {"Test"};
constexpr std::string WINDOW_TITLE {"Test"};
constexpr std::array<int, 2> WINDOW_AREA {640, 480};
constexpr std::array<uint8_t, 3> WHITE {0xFF, 0xFF, 0xFF};
constexpr std::array<uint8_t, 3> BLACK {0x00, 0x00, 0x00};
constexpr std::array<uint8_t, 3> RED {0xFF, 0x00, 0x00};


std::vector<std::array<int, 2>> calculate_arrow_vertex_points(double W_r,
															  double W_t,
															  double H_r,
															  double H_t,
															  const Math::LinearAlgebra::Vector2D& center,
															  double angle_degrees)
{
	if(W_r <= W_t) {
		throw std::runtime_error("W_r must be greater than W_t");
	}

	std::vector<Math::LinearAlgebra::Vector2D> arrow_vertices {{ 0           , H_r      },
															   {(W_r - W_t)/2, H_r      },
															   {(W_r - W_t)/2, 0        },
															   {(W_r + W_t)/2, 0        },
															   {(W_r + W_t)/2, H_r      },
															   {(W_r      )  , H_r      },
															   {(W_r      )/2, H_r + H_t}};

	double angle_radians {(M_PI/180)*angle_degrees};

	Math::LinearAlgebra::Matrix2D rotation_matrix {{ std::cos((M_PI/180)*angle_degrees), std::sin((M_PI/180)*angle_degrees)},
												   {-std::sin((M_PI/180)*angle_degrees), std::cos((M_PI/180)*angle_degrees)}};

	std::vector<std::array<int, 2>> arrow_vertex_points (arrow_vertices.size());
	std::transform(arrow_vertices.cbegin(),
				   arrow_vertices.cend(),
				   arrow_vertex_points.begin(),
				   [&rotation_matrix, &center](Math::LinearAlgebra::Vector2D vertex){ return (rotation_matrix*vertex + center).round(); });
	
	return arrow_vertex_points;
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
    double y_norm {std::sqrt(y_norm_sq)};
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
         &right](double y, double sign){return -A_y*y + sign*B_y*std::sqrt(y_norm_sq - y*y) + (y <= sign*lower*B ? 1 : -1)*lower*right*std::sqrt(C_y - D_y*y*y + sign*2*E_y*y*std::sqrt(y_norm_sq - y*y));};

    double y_slope;
    int y_slope_sign;
    bool y_increment;
    bool x_increment;
    bool keep_going {true};
    double y_stop {y(x_norm)};

    std::vector<std::array<int, 2>> upper_arc_points;

    if(std::isnan(y_stop)) {
        double epsilon = 0.00001;
        y_stop = y(x_norm - epsilon);
        upper_arc_points.push_back({static_cast<int>(-std::floor(x_norm - epsilon)), static_cast<int>(round(y(-(x_norm - epsilon))))});
    } else {
        upper_arc_points.push_back({static_cast<int>(-std::floor(x_norm)), static_cast<int>(round(y(-x_norm)))});
    }

    while(keep_going) {

        y_slope = dy_dx(upper_arc_points[upper_arc_points.size() - 1][0]);
        y_slope_sign = y_slope > 0 ? 1 : -1;

        if (std::abs(y_slope) < 1) {

            if(y_slope_sign > 0 && upper_arc_points[upper_arc_points.size() - 1][1] + 1 >= y_norm) {
                y_increment = false;
            } else {
                y_increment = y_slope_sign*(y(upper_arc_points[upper_arc_points.size() - 1][0] + 1) - upper_arc_points[upper_arc_points.size() - 1][1]) > 0.5;
            }

            x_increment = true;

        } else {

            y_increment = true;

            if (upper_arc_points[upper_arc_points.size() - 1][0] + 1 >= x_norm) {
                x_increment = false;
            } else {
                x_increment = x(upper_arc_points[upper_arc_points.size() - 1][1] + y_slope_sign, -y_slope_sign) - upper_arc_points[upper_arc_points.size() - 1][0] > 0.5;
            }

            if(y_slope_sign < 0) {
                keep_going = upper_arc_points[upper_arc_points.size() - 1][1] > y_stop && upper_arc_points[upper_arc_points.size() - 1][0] < x_norm;
            }

        }

        if (keep_going) {
            upper_arc_points.push_back({upper_arc_points[upper_arc_points.size() - 1][0] + (x_increment ? 1 : 0),
                                        upper_arc_points[upper_arc_points.size() - 1][1] + y_slope_sign*(y_increment ? 1 : 0)});
        }
    }

    std::vector<std::array<int, 2>> points (2*upper_arc_points.size());
    for(std::size_t n = 0; n < upper_arc_points.size(); n++) {
        points[2*n    ] = { upper_arc_points[n][0] + x_c,  upper_arc_points[n][1] + y_c};
        points[2*n + 1] = {-upper_arc_points[n][0] + x_c, -upper_arc_points[n][1] + y_c};
    }

    return points;
}


int main( int argc, char* args[] )
{

	constexpr double W_r {50};
	constexpr double W_t {20};
	constexpr double H_r {40};
	constexpr double H_t {20};
	constexpr Math::LinearAlgebra::Vector2D arrow_center {50, 100};
	constexpr double angle_degrees {-30};

	constexpr int radius {45};
	constexpr Math::LinearAlgebra::Vector2D circle_center {200, 300};

	constexpr int x_axis_radius {20};
	constexpr int y_axis_radius {50};
	constexpr Math::LinearAlgebra::Vector2D ellipse_center {250, 300};

	SDML::Subsystem::Initialize(LOGFILE_NAME, SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS);

	try {

		SDML::Video::Window canvas {WINDOW_TITLE, WINDOW_AREA};
		SDML::Video::Renderer paintbrush {canvas};
		paintbrush.SetDrawingColor(WHITE);
		paintbrush.DrawEntireTarget();

		/*const auto& [arrow_boundary_points, arrow_within_boundary_points] = Graphics::Shape::polygon(calculate_arrow_vertex_points(W_r, W_t, H_r, H_t, arrow_center, angle_degrees));
		paintbrush.SetDrawingColor(RED);
		paintbrush.DrawPoints(arrow_within_boundary_points);
		paintbrush.SetDrawingColor(BLACK);
		paintbrush.DrawPoints(arrow_boundary_points);

		const auto& [circle_boundary_points, circle_within_boundary_points] = Graphics::Shape::circle(radius, circle_center.round());
		paintbrush.SetDrawingColor(RED);
		paintbrush.DrawPoints(circle_within_boundary_points);
		paintbrush.SetDrawingColor(BLACK);
		paintbrush.DrawPoints(circle_boundary_points);*/

		const auto& [ellipse_boundary_points, ellipse_within_boundary_points] = Graphics::Shape::ellipse(x_axis_radius, y_axis_radius, ellipse_center.round());
		paintbrush.SetDrawingColor(RED);
		paintbrush.DrawPoints(ellipse_within_boundary_points);
		paintbrush.SetDrawingColor(BLACK);
		paintbrush.DrawPoints(ellipse_boundary_points);

		paintbrush.DrawPoints(rotated_ellipse(20, 50, 45, 150, 300));
        // paintbrush.DrawLine(std::array<std::array<int, 2>, 2> {{{180, 322}, {270, 322}}});

		paintbrush.Update();
		
		std::optional<std::unique_ptr<SDML::Events::Event>> current_event;
		bool quit = false;

		while(!quit) {
			current_event = SDML::Events::PollEvent();
			while(current_event.has_value()){
				quit = quit ? quit : current_event.value()->Quit();
				current_event = SDML::Events::PollEvent();
			}
		}

	}
	catch(const std::exception& error_message)
	{
		std::cerr << error_message.what() << std::endl;
		Logging::MainLogFile.Write(error_message.what());
	}

	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
