#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Driver.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <string>
#include <string_view>
#include <iostream>


namespace SDML
{
	namespace Video
	{
		int GetNumDisplays()
		{
			int num_displays {SDL_GetNumVideoDisplays()};

			if(num_displays < 1) { throw std::string{"No Video Displays were detected"}; }

			return num_displays;
		}

		std::string_view GetDisplayName(int displayIndex)
		{
			const char* display_name {SDL_GetDisplayName(displayIndex)};

			if(display_name == nullptr)
			{
				throw fmt::format("Could not get name for Display #{:d}: {:s}",
								  displayIndex,
								  SDL_GetError());
				}

			return std::string_view {display_name};
		}

		int GetDisplayWidth(int DisplayIndex)
		{
			SDL_Rect FullscreenBounds {};
			SDL_Rect UsableBounds {};

			if(SDL_GetDisplayBounds(DisplayIndex, &FullscreenBounds) < 0)
			{
				throw fmt::format("Could not retrive fullscreen boundaries for '{:s}' Display: {:s}",
								  GetDisplayName(DisplayIndex),
								  SDL_GetError());
			}

			if(SDL_GetDisplayUsableBounds(DisplayIndex, &UsableBounds) < 0)
			{
				throw fmt::format("Could not retrive usable boundaries for '{:s}' Display: {:s}",
								  GetDisplayName(DisplayIndex),
								  SDL_GetError());
			}

			if(FullscreenBounds.w != UsableBounds.w)
			{
				std::cerr << fmt::format("Warning: difference detected between Fullscreen width and Usable Width:\nFullscreen Width: {:d}\nUsable Width: {:d}",
										 FullscreenBounds.w,
										 UsableBounds.w);
			}

			return FullscreenBounds.w;
		}

		int GetDisplayHeight(int DisplayIndex)
		{
			SDL_Rect FullscreenBounds {};
			SDL_Rect UsableBounds {};

			if(SDL_GetDisplayBounds(DisplayIndex, &FullscreenBounds) < 0)
			{
				throw fmt::format("Could not retrive fullscreen boundaries for '{:s}' Display: {:s}",
								  GetDisplayName(DisplayIndex),
								  SDL_GetError());
			}

			if(SDL_GetDisplayUsableBounds(DisplayIndex, &UsableBounds) < 0)
			{
				throw fmt::format("Could not retrive usable boundaries for '{:s}' Display: {:s}",
								  GetDisplayName(DisplayIndex),
								  SDL_GetError());
			}

			if(FullscreenBounds.h != UsableBounds.h)
			{
				std::cerr << fmt::format("Warning: difference detected between Fullscreen Height and Usable Height:\nFullscreen Height: {:d}\nUsable Height: {:d}",
										 FullscreenBounds.h,
										 UsableBounds.h);
			}

			return FullscreenBounds.h;
		}
	}
}


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);

	try
	{
		/*
		SDML::Video::Window windowTest {"Test", 640, 480, SDML::Video::WindowFlag::RESIZABLE};
		windowTest.SetMinimumArea(  10,   10);
		windowTest.SetMaximumArea(1000, 1000);
		windowTest.Flash(SDML::Video::FlashOperation::UNTIL_FOCUSED);

		std::cout << windowTest.GetTitle() << std::endl;
		std::cout << windowTest.GetID() << std::endl;
		std::cout << windowTest.GetX() << std::endl;
		std::cout << windowTest.GetY() << std::endl;
		std::cout << windowTest.GetWidth() << std::endl;
		std::cout << windowTest.GetMinimumWidth() << std::endl;
		std::cout << windowTest.GetMaximumWidth() << std::endl;
		std::cout << windowTest.GetHeight() << std::endl;
		std::cout << windowTest.GetMinimumHeight() << std::endl;
		std::cout << windowTest.GetMaximumHeight() << std::endl;
		std::cout << windowTest.CheckWindowFlags(SDML::Video::WindowFlag::SHOWN) << std::endl;
		std::cout << windowTest.CheckWindowFlags(SDML::Video::WindowFlag::SHOWN | SDML::Video::WindowFlag::RESIZABLE) << std::endl;
		std::cout << windowTest.CheckWindowFlags(SDML::Video::WindowFlag::RESIZABLE) << std::endl;

		SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
		*/

		std::cout << SDML::Video::GetNumVideoDrivers() << std::endl;
		std::cout << SDML::Video::GetCurrentVideoDriver() << std::endl;
		std::cout << SDML::Video::GetVideoDrivers() << std::endl;
		std::cout << "\n" << std::endl;

		std::cout << SDML::Video::GetNumDisplays() << std::endl;
		std::cout << SDML::Video::GetDisplayName(0) << std::endl;
		std::cout << SDML::Video::GetDisplayWidth(0) << std::endl;
		std::cout << SDML::Video::GetDisplayHeight(0) << std::endl;

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
