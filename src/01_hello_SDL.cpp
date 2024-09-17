
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Main.hpp"
#include "SDL_Wrapper/Canvases/Canvas.hpp"
#include "SDL_Wrapper/Canvases/CPU/Image.hpp"
#include "SDL_Wrapper/Canvases/GPU/Paintbrush.hpp"
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
	SDL::Canvassing::Canvas* window {nullptr};
	SDL::GPU::Painting::Paintbrush* renderer {nullptr};
	Media::Resources loaded_resources {NULL};

	try
	{

		SDL::Init(SDL::INIT_VIDEO);
		IMG::Init(IMG::InitFlags::PNG);

		SDL::SetHint(SDL::HINT_RENDER_SCALE_QUALITY, "1",
					 "Warning: Linear texture filtering not enabled!");

		window = \
			SDL::Canvassing::Create("SDL Tutorial",
	  							   SDL::WINDOWPOS_UNDEFINED,
								   SDL::WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH,
								   SCREEN_HEIGHT,
								   SDL::WINDOW_SHOWN);

		renderer  = \
			SDL::GPU::Painting::Create(window,
								   -1,
								   SDL::GPU::Painting::Flags::ACCELERATED,
								   0xFF, 0xFF, 0xFF, 0xFF);
		
		loaded_resources = Media::LoadResources(renderer);

        SDL::Event current_event;
		bool quit = false;
		while(!quit)
		{
			if(SDL::PollEvent(current_event))
			{
				quit |= current_event.type == SDL::EventTypes::QUIT;
			}

			/*
			SDL::BlitSurfaceOntoWindow(window,
						 			   loaded_resources.helloWorld,
									   nullptr,
									   nullptr);

			SDL::Canvassing::UpdateSurface(window);
			*/
			///*
			SDL::GPU::Painting::Clear(renderer);
			SDL::GPU::Painting::Copy(renderer, loaded_resources.renderingPNG, NULL, NULL);
			SDL::GPU::Painting::Present(renderer);
			//*/

		}

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	Media::FreeResources(loaded_resources);
	SDL::GPU::Painting::Destroy(renderer);
	SDL::Canvassing::Destroy(window);
	IMG::Quit();
	SDL::Quit();

	return 0;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
