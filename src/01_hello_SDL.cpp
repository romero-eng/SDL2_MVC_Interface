
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Main.hpp"
#include "SDL_Wrapper/Window.hpp"
#include "SDL_Wrapper/Surface.hpp"
#include "SDL_Wrapper/Event.hpp"
#include "SDL_Wrapper/Rectangle.hpp"

#include <string>
#include <iostream>


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	SDL::Window* window {nullptr};
	SDL::Surface* screenSurface {nullptr};

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

		SDL::FillRect(screenSurface,
					  NULL,
					  SDL::MapRGB(screenSurface->format,
					 			  0xAF, 0xAF, 0x2b));
			
		SDL::UpdateWindowSurface(window);
            
        //Hack to get window to stay up
        SDL::Event current_event;
		bool quit = false;
		while(quit == false)
		{
			while(SDL::PollEvent( &current_event ))
			{
				if(current_event.type == SDL_QUIT)
				{
					quit = true;
				}
			}
		}

	}
	catch(std::string error_message)
	{
		std::cout << error_message;
	}

	SDL::DestroyWindow(window);
	SDL::Quit();

	return 0;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
