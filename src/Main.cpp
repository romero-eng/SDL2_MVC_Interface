#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Surface.hpp"
#include "SDML/Video/Renderer.hpp"
#include "SDML/Video/Texture.hpp"
#include "Misc/PrettyPrint.hpp"
#include "SDML/Event.hpp"

// C++ Standard Libraries
#include <filesystem>
#include <iostream>
#include <chrono>


int main( int argc, char* args[] )
{

	std::chrono::time_point<std::chrono::system_clock> init_time_point {SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS)};
	SDML::Image::Initialize(0);

	try
	{
		SDML::Video::Window windowTest {"Test", 
										std::array<int, 2> {640, 480},
										SDML::Video::WindowInitFlag::RESIZABLE};

		SDL_Event event;
		bool quit = false;
		while(!quit) {
			while(SDL_PollEvent(&event)){

				switch(event.type) {
					case SDL_QUIT:
						std::cout << SDML::Event::QuitEvent(event, init_time_point) << std::endl;
						break;
					default:
						std::cout << SDML::Event::GenericEvent{event, init_time_point} << std::endl;
						break;
				}

				if(event.type == SDL_QUIT) {
					quit = true;
				}
			}
		}

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
