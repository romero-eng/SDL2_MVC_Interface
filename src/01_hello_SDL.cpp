
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Main.hpp"
#include "SDL_Wrapper/Painting/Canvas.hpp"
#include "SDL_Wrapper/Painting/RegularPicture.hpp"
#include "SDL_Wrapper/Painting/AcceleratedPaintbrush.hpp"
#include "SDL_Wrapper/Event.hpp"
#include "SDL_Wrapper/Image.hpp"
#include "SDL_Wrapper/Rectangle.hpp"


#include <string>
#include <iostream>
#include <utility>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

fs::path RESOURCE_DIRECTORY { fs::current_path().parent_path().parent_path()/"res" };
fs::path TEXTURE_PNG {RESOURCE_DIRECTORY/"texture.png"};

int main( int argc, char* args[] )
{

	try
	{

		SDL::Init(SDL::INIT_VIDEO);
		IMG::Init(IMG::InitFlags::PNG);

		SDL::SetHint(SDL::HINT_RENDER_SCALE_QUALITY, "1",
					 "Warning: Linear texture filtering not enabled!");

		SDL::Painting::Canvas canvas {"SDL Tutorial",
	  							      SDL::WINDOWPOS_UNDEFINED,
								      SDL::WINDOWPOS_UNDEFINED,
								      SCREEN_WIDTH,
								      SCREEN_HEIGHT,
								      SDL::WINDOW_SHOWN};
		
		/*
		renderer  = \
			SDL::GPU::Painting::Create(window,
								   -1,
								   SDL::GPU::Painting::Flags::ACCELERATED,
								   0xFF, 0xFF, 0xFF, 0xFF);
		*/
		SDL::Painting::RegularPicture helloWorldPicture {RESOURCE_DIRECTORY/"hello_world.bmp"};

        SDL::Event current_event;
		bool quit = false;
		while(!quit)
		{
			if(SDL::PollEvent(current_event))
			{
				quit |= current_event.type == SDL::EventTypes::QUIT;
			}

			///*
			canvas.PostPicture(helloWorldPicture);
			//*/
			/*
			SDL::GPU::Painting::Clear(renderer);
			SDL::GPU::Painting::Copy(renderer, loaded_resources.renderingPNG, NULL, NULL);
			SDL::GPU::Painting::Present(renderer);
			*/

		}

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	IMG::Quit();
	SDL::Quit();

	return 0;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
