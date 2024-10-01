#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Driver.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>
#include <fmt/ranges.h>

// C++ Standard Libraries
#include <iostream>


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);

	try
	{
		SDML::Video::Window windowTest {"Test", 640, 480, SDML::Video::WindowFlag::RESIZABLE};
		windowTest.SetMinimumArea(  10,   10);
		windowTest.SetMaximumArea(1000, 1000);
		windowTest.Flash(SDML::Video::FlashOperation::UNTIL_FOCUSED);

		std::cout << "Number of Drivers: " << SDML::Video::Drivers::GetNumDrivers() << std::endl;
		std::cout << "Current Driver: " << SDML::Video::Drivers::GetCurrentDriverName() << std::endl;
		std::cout << "All Drivers: " << fmt::format("[{}]", fmt::join(SDML::Video::Drivers::GetDriverNames(), ", ")) << std::endl;
		std::cout << std::endl;

		std::cout << windowTest << std::endl;

		SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

		/*
		std::cout << SDML::Video::Drivers::GetNumDrivers() << std::endl;
		std::cout << SDML::Video::Drivers::GetCurrentDriverName() << std::endl;
		std::cout << SDML::Video::Drivers::GetDriverNames() << std::endl;
		std::cout << "\n" << std::endl;
		*/

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
