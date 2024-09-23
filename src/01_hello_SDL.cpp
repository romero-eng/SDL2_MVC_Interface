
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


void runSurfaceLoadingTest()
{
	SDL::Painting::Equipment::Canvas canvas {"ViewPort Test",
		  								     SDL::Painting::Equipment::CanvasPositionFlags::UNDEFINED,
										     SCREEN_WIDTH,
									         SCREEN_HEIGHT,
									         SDL::Painting::Equipment::CanvasInitFlags::SHOWN};

	SDL::Painting::Image::RegularImage helloWorldBMP {fs::current_path().parent_path().parent_path()/"res"/"hello_world.bmp"};

	canvas.PostPicture(helloWorldBMP);

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


void runTextureRenderingTest()
{
	SDL::Painting::Equipment::Canvas canvas {"ViewPort Test",
		  								     SDL::Painting::Equipment::CanvasPositionFlags::UNDEFINED,
										     SCREEN_WIDTH,
									         SCREEN_HEIGHT,
									         SDL::Painting::Equipment::CanvasInitFlags::SHOWN};

	SDL::Painting::Equipment::AcceleratedPaintbrush paintbrush {canvas,
                                							    -1,
                                 							    SDL::Painting::Equipment::AcceleratedPaintbrushFlags::ACCELERATED,
                                 							    0xFF, 0xFF, 0xFF, 0xFF};

	SDL::Painting::Image::AcceleratedImage renderingPNG {paintbrush,
														 fs::current_path().parent_path().parent_path()/"res"/"texture.png"};

	paintbrush.Clear();
	paintbrush.PostPicture(renderingPNG);
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


void runGeometryRenderingTest()
{

	SDL::Painting::Equipment::Canvas canvas {"Geometry Rendering Test",
		  								     SDL::Painting::Equipment::CanvasPositionFlags::UNDEFINED,
										     SCREEN_WIDTH,
									         SCREEN_HEIGHT,
									         SDL::Painting::Equipment::CanvasInitFlags::SHOWN};

	SDL::Painting::Equipment::AcceleratedPaintbrush paintbrush {canvas,
                                							    -1,
                                 							    SDL::Painting::Equipment::AcceleratedPaintbrushFlags::ACCELERATED,
                                 							    0xFF, 0xFF, 0xFF, 0xFF};
	paintbrush.Fill();

	paintbrush.SetDrawColor(0xFF, 0x0, 0x0, 0xFF);
	paintbrush.DrawRectangle(SDL::Painting::Equipment::Rect {.x{SCREEN_WIDTH/4},
															 .y{SCREEN_HEIGHT/4},
															 .w{SCREEN_WIDTH/2},
															 .h{SCREEN_HEIGHT/2}});
	
	paintbrush.SetDrawColor(0x0, 0xFF, 0x0, 0xFF);
	paintbrush.DrawEmptyRectangle(SDL::Painting::Equipment::Rect {.x{SCREEN_WIDTH/6},
																  .y{SCREEN_HEIGHT/6},
																  .w{2*SCREEN_WIDTH/3},
																  .h{2*SCREEN_HEIGHT/3}});
	
	paintbrush.SetDrawColor(0x0, 0x0, 0xFF, 0xFF);
	paintbrush.DrawLine(0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

	paintbrush.SetDrawColor(0xFF, 0xFF, 0x0, 0xFF);
	for(int i = 0; i < SCREEN_HEIGHT; i += 4)
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


void runViewPortTest()
{
	SDL::Painting::Equipment::Canvas canvas {"ViewPort Test",
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

	paintbrush.ReserveDrawingArea(SDL::Painting::Equipment::Rect {.x{0},
																  .y{0},
																  .w{SCREEN_WIDTH/2},
																  .h{SCREEN_HEIGHT/2}});
	paintbrush.PostPicture(viewPortTest);
	paintbrush.ReserveDrawingArea(SDL::Painting::Equipment::Rect {.x{SCREEN_WIDTH/2},
																  .y{0},
																  .w{SCREEN_WIDTH/2},
																  .h{SCREEN_HEIGHT/2}});
	paintbrush.PostPicture(viewPortTest);
	paintbrush.ReserveDrawingArea(SDL::Painting::Equipment::Rect {.x{0},
																  .y{SCREEN_HEIGHT/2},
																  .w{SCREEN_WIDTH},
																  .h{SCREEN_HEIGHT/2}});
	paintbrush.PostPicture(viewPortTest);
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


int main( int argc, char* args[] )
{

	try
	{
		SDL::Init(SDL::SubsystemInitFlags::VIDEO,
				  SDL::Painting::Image::FileTypes::PNG);

		SDL::SetHint(SDL::Hints::RENDER_SCALE_QUALITY, "linear", "Warning: Linear texture filtering not enabled!");

		//runSurfaceLoadingTest();
		runTextureRenderingTest();
		runGeometryRenderingTest();
		runViewPortTest();

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
