
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Subsystems.hpp"
#include "SDL_Wrapper/Hints.hpp"
#include "SDL_Wrapper/Event.hpp"

#include "SDL_Wrapper/Painting/Equipment/Canvas.hpp"
#include "SDL_Wrapper/Painting/Image/RegularImage.hpp"
#include "SDL_Wrapper/Painting/Image/AcceleratedImage.hpp"
#include "SDL_Wrapper/Painting/Equipment/AcceleratedPaintbrush.hpp"
#include "SDL_Wrapper/Painting/Equipment/Rectangle.hpp"


#include <string>
#include <iostream>
#include <utility>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{

	try
	{
		SDL::Init(SDL::SubsystemInitFlags::VIDEO,
				  SDL::Painting::Image::FileTypes::PNG);

		SDL::SetHint(SDL::Hints::RENDER_SCALE_QUALITY, "linear", "Warning: Linear texture filtering not enabled!");

		SDL::Painting::Equipment::Canvas canvas {"SDL Tutorial",
		  								         SDL::Painting::Equipment::CanvasPositionFlags::UNDEFINED,
										         SCREEN_WIDTH,
										         SCREEN_HEIGHT,
										         SDL::Painting::Equipment::CanvasInitFlags::SHOWN};

		SDL::Painting::Equipment::AcceleratedPaintbrush paintbrush {canvas,
                                								    -1,
                                 								    SDL::Painting::Equipment::AcceleratedPaintbrushFlags::ACCELERATED,
                                 								    0xFF, 0xFF, 0xFF, 0xFF};

		SDL::Painting::Image::AcceleratedImage viewPortTest {paintbrush,
															   fs::current_path().parent_path().parent_path()/"res"/"viewport.png"};

		paintbrush.ReserveDrawingArea(SDL::Painting::Equipment::Rect {.x{0}, .y{0}, .w{SCREEN_WIDTH/2}, .h{SCREEN_HEIGHT/2}});
		paintbrush.CopyPicture(viewPortTest);
		paintbrush.ReserveDrawingArea(SDL::Painting::Equipment::Rect {.x{SCREEN_WIDTH/2}, .y{0}, .w{SCREEN_WIDTH/2}, .h{SCREEN_HEIGHT/2}});
		paintbrush.CopyPicture(viewPortTest);
		paintbrush.ReserveDrawingArea(SDL::Painting::Equipment::Rect {.x{0}, .y{SCREEN_HEIGHT/2}, .w{SCREEN_WIDTH}, .h{SCREEN_HEIGHT/2}});
		paintbrush.CopyPicture(viewPortTest);
		paintbrush.Present();

        SDL::Event current_event;
		bool quit = false;
		while(!quit)
		{
			if(SDL::PollEvent(current_event))
			{
				quit |= current_event.type == SDL::EventTypes::QUIT;
			}

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
