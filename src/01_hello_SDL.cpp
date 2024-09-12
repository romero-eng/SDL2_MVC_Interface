
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Main.hpp"
#include "SDL_Wrapper/Window.hpp"
#include "SDL_Wrapper/Surface.hpp"
#include "SDL_Wrapper/Render.hpp"
#include "SDL_Wrapper/Event.hpp"
#include "SDL_Wrapper/Image.hpp"
#include "SDL_Wrapper/Rectangle.hpp"

#include "Media.hpp"

#include <string>
#include <iostream>
#include <utility>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main( int argc, char* args[] )
{
	SDL::Window* window {nullptr};
	SDL::Renderer* renderer {nullptr};
	Media::Resources loaded_resources { Media::LoadResources() };

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

		renderer \
			= SDL::CreateRenderer(window,
								  -1,
								  SDL::RendererFlags::ACCELERATED | SDL::RendererFlags::PRESENTVSYNC,
								  0xFF, 0xFF, 0xFF, 0xFF);

        SDL::Event current_event;
		bool quit = false;
		while(!quit)
		{
			if(SDL::PollEvent(current_event))
			{
				quit |= current_event.type == SDL::EventTypes::QUIT;
			}

			
			SDL::BlitSurfaceOntoWindow(window,
						 			   loaded_resources.helloWorld,
									   nullptr,
									   nullptr);

			SDL::UpdateWindowSurface(window);
		}

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	Media::FreeResources(loaded_resources);
	SDL::DestroyRenderer(renderer);
	SDL::DestroyWindow(window);
	SDL::Quit();

	return 0;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
