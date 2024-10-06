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

		std::array<uint8_t, 4> white {0xFF, 0xFF, 0xFF, 0xFF};
		std::array<uint8_t, 4>   red {0xFF, 0x0,  0x0,  0xFF};
		std::array<uint8_t, 4> green {0x0,  0xFF, 0x0,  0xFF};
		std::array<uint8_t, 4>  blue {0x0,  0x0,  0xFF, 0xFF};

		std::array<std::array<float, 2>, 2> red_line {{{100.0, 100.0},
													   {200.0, 200.0}}};
		std::vector<std::array<float, 2>> blue_line_points {{300.0, 300.0},
														    {300.0, 350.0},
														    {350.0, 400.0},
														    {400.0, 350.0}};

		SDML::Video::Window windowTest {"Test", 
										std::array<int, 2> {640, 480},
										SDML::Video::WindowInitFlag::RESIZABLE};

		SDML::Video::Renderer rendererTest {windowTest,
											SDML::Video::RendererInitFlag::ACCELERATED};

		rendererTest.SetDrawingColor(white);
		rendererTest.DrawEntireTarget();

		rendererTest.SetDrawingColor(red);
		rendererTest.DrawLine(red_line);

		rendererTest.SetDrawingColor(blue);
		rendererTest.DrawConnectedLines(blue_line_points);

		rendererTest.Update();

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
