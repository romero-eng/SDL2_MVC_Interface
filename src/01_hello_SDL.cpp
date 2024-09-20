
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDL_Wrapper/Subsystems.hpp"
#include "SDL_Wrapper/Hints.hpp"
#include "SDL_Wrapper/Event.hpp"

#include "SDL_Wrapper/Painting/Canvas.hpp"
#include "SDL_Wrapper/Painting/RegularPicture.hpp"
#include "SDL_Wrapper/Painting/AcceleratedPicture.hpp"
#include "SDL_Wrapper/Painting/AcceleratedPaintbrush.hpp"
#include "SDL_Wrapper/Painting/Rectangle.hpp"


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
		SDL::Init(SDL::SubsystemInitFlags::VIDEO);

		SDL::SetHint(SDL::Hints::RENDER_SCALE_QUALITY, "linear", "Warning: Linear texture filtering not enabled!");

		SDL::Painting::Canvas canvas {"SDL Tutorial",
	  							      SDL::Painting::CanvasPositionFlags::UNDEFINED,
								      SCREEN_WIDTH,
								      SCREEN_HEIGHT,
								      SDL::Painting::CanvasInitFlags::SHOWN};

		SDL::Painting::AcceleratedPaintbrush paintbrush {canvas,
                                						 -1,
                                 						 SDL::Painting::AcceleratedPaintbrushFlags::ACCELERATED,
                                 						 0xFF, 0xFF, 0xFF, 0xFF};

		paintbrush.Fill();
		paintbrush.SetDrawColor(0xFF, 0x0, 0x0, 0xFF);
		paintbrush.DrawRect(SDL::Painting::Rect { .x{SCREEN_WIDTH/4}, .y{SCREEN_HEIGHT/4}, .w{SCREEN_WIDTH/2}, .h{SCREEN_HEIGHT/2} });
		paintbrush.SetDrawColor(0x0, 0xFF, 0x0, 0xFF);
		paintbrush.DrawRectBoundary(SDL::Painting::Rect { .x{SCREEN_WIDTH/6}, .y{SCREEN_HEIGHT/6}, .w{SCREEN_WIDTH*2/3}, .h{SCREEN_HEIGHT*2/3} });
		paintbrush.SetDrawColor(0x0, 0x0, 0xFF, 0xFF);
		paintbrush.DrawLine(0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);
		paintbrush.SetDrawColor(0xFF, 0xFF, 0x0, 0xFF);
		for (int i = 0; i < SCREEN_HEIGHT; i += 4)
		{
			paintbrush.DrawPoint(SCREEN_WIDTH/2, i);
		}
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
