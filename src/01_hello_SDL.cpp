
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Subsystems.hpp"
#include "SDL_Wrapper/Hints.hpp"
#include "SDL_Wrapper/Event.hpp"

#include "SDL_Wrapper/Painting/Canvas.hpp"
#include "SDL_Wrapper/Painting/RegularPicture.hpp"
#include "SDL_Wrapper/Painting/AcceleratedPicture.hpp"
#include "SDL_Wrapper/Painting/AcceleratedPaintbrush.hpp"


#include <string>
#include <iostream>
#include <utility>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const fs::path RESOURCE_DIRECTORY { fs::current_path().parent_path().parent_path()/"res" };

int main( int argc, char* args[] )
{

	try
	{
		SDL::Init(SDL::SubsystemInitFlags::VIDEO,
				  SDL::Painting::ImageFileTypes::PNG);

		SDL::SetHint(SDL::Hints::RENDER_SCALE_QUALITY, "linear", "Warning: Linear texture filtering not enabled!");

		SDL::Painting::Canvas canvas {"SDL Tutorial",
	  							      SDL::Painting::CanvasPositionFlags::UNDEFINED,
								      SCREEN_WIDTH,
								      SCREEN_HEIGHT,
								      SDL::Painting::CanvasInitFlags::SHOWN};
		
		//SDL::Painting::RegularPicture helloWorldPicture {RESOURCE_DIRECTORY/"hello_world.bmp"}; /*
		SDL::Painting::AcceleratedPaintbrush paintbrush {canvas,
                                						 -1,
                                 						 SDL::Painting::AcceleratedPaintbrushFlags::ACCELERATED,
                                 						 0xFF, 0xFF, 0xFF, 0xFF};
		SDL::Painting::AcceleratedPicture renderingPNG {paintbrush, RESOURCE_DIRECTORY/"texture.png"};
		//*/

        SDL::Event current_event;
		bool quit = false;
		while(!quit)
		{
			if(SDL::PollEvent(current_event))
			{
				quit |= current_event.type == SDL::EventTypes::QUIT;
			}

			//canvas.PostPicture(helloWorldPicture);
			paintbrush.Clear(); renderingPNG.Copy(); paintbrush.Present();

		}

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	SDL::Quit();

	return 0;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
