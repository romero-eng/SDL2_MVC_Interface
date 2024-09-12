
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Main.hpp"
#include "SDL_Wrapper/Window.hpp"
#include "SDL_Wrapper/Surface.hpp"
#include "SDL_Wrapper/Event.hpp"
#include "SDL_Wrapper/Image.hpp"
#include "SDL_Wrapper/Rectangle.hpp"

#include "Resources.hpp"

#include <string>
#include <iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main( int argc, char* args[] )
{
	SDL::Window* window {nullptr};
	SDL::Surface* screenSurface {nullptr};
	SDL::Surface* bitmapSurface {nullptr};

	try
	{

		SDL::Init(SDL::INIT_VIDEO);

		window = \
			SDL::CreateWindow("SDL Tutorial",
  							  SDL::WINDOWPOS_UNDEFINED,
							  SDL::WINDOWPOS_UNDEFINED,
							  SCREEN_WIDTH,
							  SCREEN_HEIGHT,
							  SDL::WINDOW_SHOWN);

		screenSurface = SDL::GetWindowSurface(window);

        SDL::Event current_event;
		bool quit = false;
		while(!quit)
		{
			if(SDL::PollEvent(current_event))
			{
				quit |= current_event.type == SDL::EventTypes::QUIT;
			}

			
			SDL::BlitSurface(Resources::HelloWorldSurface, nullptr, screenSurface, nullptr);
			SDL::UpdateWindowSurface(window);
		}

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	SDL::FreeSurface(bitmapSurface);
	SDL::DestroyWindow(window);
	SDL::Quit();

	return 0;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
