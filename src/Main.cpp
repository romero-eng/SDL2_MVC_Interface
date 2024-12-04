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
#include "Custom/LinearAlgebra.hpp"
#include "Custom/Shape.hpp"

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
															  Custom::LinearAlgebra::Vector2D center,
															  double angle_degrees)
{
	if(W_r <= W_t) {
		throw std::runtime_error("W_r must be greater than W_t");
	}

	std::vector<Custom::LinearAlgebra::Vector2D> arrow_vertices {{ 0           , H_r      },
																 {(W_r - W_t)/2, H_r      },
																 {(W_r - W_t)/2, 0        },
																 {(W_r + W_t)/2, 0        },
																 {(W_r + W_t)/2, H_r      },
																 {(W_r      )  , H_r      },
																 {(W_r      )/2, H_r + H_t}};

	double angle_radians {(M_PI/180)*angle_degrees};

	Custom::LinearAlgebra::Matrix2D rotation_matrix {{ std::cos((M_PI/180)*angle_degrees), std::sin((M_PI/180)*angle_degrees)},
													 {-std::sin((M_PI/180)*angle_degrees), std::cos((M_PI/180)*angle_degrees)}};

	std::vector<std::array<int, 2>> arrow_vertex_points (arrow_vertices.size());
	std::transform(arrow_vertices.cbegin(),
				   arrow_vertices.cend(),
				   arrow_vertex_points.begin(),
				   [&rotation_matrix, &center](Custom::LinearAlgebra::Vector2D vertex){ return (rotation_matrix*vertex + center).round(); });
	
	return arrow_vertex_points;
}


int main( int argc, char* args[] )
{

	constexpr double W_r = 50;
	constexpr double W_t = 20;
	constexpr double H_r = 40;
	constexpr double H_t = 20;
	constexpr Custom::LinearAlgebra::Vector2D center {50, 100};
	constexpr double angle_degrees = -10;

	SDML::Subsystem::Initialize(LOGFILE_NAME, SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS);

	try {

		SDML::Video::Window canvas {WINDOW_TITLE, WINDOW_AREA};
		SDML::Video::Renderer paintbrush {canvas};
		paintbrush.SetDrawingColor(WHITE);
		paintbrush.DrawEntireTarget();

		std::vector<std::array<int, 2>> arrow_boundary_points;
		std::vector<std::array<int, 2>> arrow_within_boundary_points;
		std::tie(arrow_boundary_points, arrow_within_boundary_points) = Custom::Shape::calculate_polygon_points(calculate_arrow_vertex_points(W_r, W_t, H_r, H_t, center, angle_degrees));
		paintbrush.SetDrawingColor(RED);
		paintbrush.DrawPoints(arrow_within_boundary_points);
		paintbrush.SetDrawingColor(BLACK);
		paintbrush.DrawPoints(arrow_boundary_points);

		std::vector<std::array<int, 2>> circle_points {Custom::Shape::calculate_circle_points(45, 200, 300)};
		paintbrush.DrawPoints(circle_points);

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
