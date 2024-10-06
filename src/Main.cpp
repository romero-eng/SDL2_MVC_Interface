#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Renderer.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

// C++ Standard Libraries
#include <iostream>


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);

	try
	{
		SDML::Video::Window windowTest {"Test", 
										std::array<int, 2> {640, 480},
										SDML::Video::WindowInitFlag::RESIZABLE};

		SDML::Video::Renderer testRenderer {windowTest,
											SDML::Video::RendererInitFlag::ACCELERATED};

		std::array<uint8_t, 4> white {0xFF, 0xFF, 0xFF, 0xFF};
		std::array<uint8_t, 4>   red {0xFF, 0x0,  0x0,  0xFF};
		std::array<uint8_t, 4> green {0x0,  0xFF, 0x0,  0xFF};
		std::array<uint8_t, 4>  blue {0x0,  0x0,  0xFF, 0xFF};

		std::vector<std::array<int, 2>>  red_points {};
		std::vector<std::array<float, 2>> blue_points {};
		for(int x = 0; x < windowTest.GetArea()[0]; x+=20) {
			 red_points.push_back(std::array<int, 2> {x, 240});
			blue_points.push_back(std::array<float, 2> {static_cast<float>(x), 360.0});
		}

		testRenderer.SetDrawingColor(white);
		testRenderer.DrawEntireTarget();

		testRenderer.SetDrawingColor(red);
		for(const std::array<int, 2>& point : red_points) {
			testRenderer.DrawPoint(point);
		}
		
		testRenderer.SetDrawingColor(blue);
		testRenderer.DrawPoints(blue_points);

		testRenderer.Update();

		SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

	}
	catch(const std::exception& error_message)
	{
		std::cerr << error_message.what() << std::endl;
	}

	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
