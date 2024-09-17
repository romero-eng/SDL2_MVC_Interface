
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Main.hpp"
#include "SDL_Wrapper/Canvases/Canvas.hpp"
#include "SDL_Wrapper/Canvases/CPU_Image.hpp"
#include "SDL_Wrapper/Canvases/GPU_Paintbrush.hpp"
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
	SDL::GPU_Painting::GPU_Paintbrush* renderer {nullptr};
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
			SDL::GPU_Painting::Create(window,
								   -1,
								   SDL::GPU_Painting::Flags::ACCELERATED,
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

			SDL::GPU_Painting::Clear(renderer);
			SDL::GPU_Painting::Copy(renderer, loaded_resources.GPU_PaintingPNG, NULL, NULL);
			SDL::GPU_Painting::Present(renderer);

		}

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	Media::FreeResources(loaded_resources);
	SDL::GPU_Painting::Destroy(renderer);
	SDL::Canvassing::Destroy(window);
	IMG::Quit();
	SDL::Quit();

	return 0;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
