#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Surface.hpp"
#include "SDML/Video/Renderer.hpp"
#include "SDML/Video/Texture.hpp"


// C++ Standard Libraries
#include <filesystem>
#include <iostream>


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);
	SDML::Image::Initialize(0);

	try
	{
		constexpr std::array<uint8_t, 3> red {0xFF, 0x00, 0x00};
		constexpr std::array<int, 2> generic_area {100, 100};
		constexpr std::array<int, 2> first_position {50, 50};
		constexpr std::array<int, 2> second_position {250, 250};
		constexpr std::array<int, 2> third_position {450, 250};

		std::vector<std::pair<std::array<int, 2>, std::array<int, 2>>> rectangles {{ first_position, generic_area},
																				   {second_position, generic_area},
																				   { third_position, generic_area}};

		SDML::Video::Window windowTest {"Test", 
										std::array<int, 2> {640, 480},
										SDML::Video::WindowInitFlag::RESIZABLE};

		windowTest.DrawRects(rectangles, red);
		windowTest.UpdateRects(rectangles);

		SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

	}
	catch(const std::exception& error_message)
	{
		std::cerr << error_message.what() << std::endl;
	}

	SDML::Image::Quit();
	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
