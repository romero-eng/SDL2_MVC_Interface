#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDML/Subsystem.hpp"
#include "SDML/Window.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <iostream>


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);

	try
	{
		SDML::Video::Window windowTest {"Test", 640, 480};
		windowTest.Flash(SDML::Video::FlashOperation::UNTIL_FOCUSED);

		std::cout << windowTest.GetWidth() << std::endl;
		std::cout << windowTest.GetHeight() << std::endl;

		SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

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
