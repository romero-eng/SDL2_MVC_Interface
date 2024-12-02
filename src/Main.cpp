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
#include "Custom/Polygon.hpp"

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


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(LOGFILE_NAME, SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS);

	try {

		constexpr double W_r = 50;
		constexpr double W_t = 20;
		constexpr double H_r = 40;
		constexpr double H_t = 20;
		constexpr std::array<double, 2> center = {50, 100};
		constexpr double angle_degrees = 30;

		SDML::Video::Window canvas {WINDOW_TITLE, WINDOW_AREA};
		SDML::Video::Renderer paintbrush {canvas};
		paintbrush.SetDrawingColor(WHITE);
		paintbrush.DrawEntireTarget();

		std::vector<std::array<int, 2>> arrow_boundary_points;
		std::vector<std::array<int, 2>> arrow_within_boundary_points;
		std::tie(arrow_boundary_points,
				 arrow_within_boundary_points) = \
				 Custom::Polygon::calculate_points(Custom::LinearAlgebra::round_double_vectors_to_int_vectors(Custom::LinearAlgebra::translate_and_rotate_vectors({{		      0, 	    H_r},
																																								 {(W_r - W_t)/2, 	    H_r},
																		 																						 {(W_r - W_t)/2,          0},
																	 																							 {(W_r + W_t)/2,   	      0},
																	 																							 {(W_r + W_t)/2, 	    H_r},
																	 																							 {	   	     W_r, 	    H_r},
																	 																							 {	 	   W_r/2, H_r + H_t}},
																																								angle_degrees,
																																								center)));
		paintbrush.SetDrawingColor(RED);
		paintbrush.DrawPoints(arrow_within_boundary_points);
		paintbrush.SetDrawingColor(BLACK);
		paintbrush.DrawPoints(arrow_boundary_points);

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
