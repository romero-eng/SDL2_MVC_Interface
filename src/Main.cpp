#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Driver.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <iostream>


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);

	try
	{
		SDML::Video::Window windowTest {"Test", 640, 480, SDML::Video::WindowFlag::RESIZABLE};
		windowTest.SetMinimumArea(  10,   10);
		windowTest.SetMaximumArea(1000, 1000);
		windowTest.Flash(SDML::Video::FlashOperation::UNTIL_FOCUSED);

		std::string_view display_orientation_string;
		switch(windowTest.GetDisplayOrientation())
		{
			case SDML::Video::DisplayOrientation::UNKNOWN:
				display_orientation_string = "Unknown";
				break;
			case SDML::Video::DisplayOrientation::LANDSCAPE:
				display_orientation_string = "Landscape";
				break;
			case SDML::Video::DisplayOrientation::LANDSCAPE_FLIPPED:
				display_orientation_string = "Flipped Landscape";
				break;
			case SDML::Video::DisplayOrientation::PORTRAIT:
				display_orientation_string = "Portrait";
				break;
			case SDML::Video::DisplayOrientation::PORTRAIT_FLIPPED:
				display_orientation_string = "Flipped Portrait";
				break;
		}
		
		int max_key_len {34};
		std::cout << fmt::format("{:>{}s}: {:s}", "Window Name", max_key_len, windowTest.GetTitle()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window ID", max_key_len, windowTest.GetID()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window X-Coordinate", max_key_len, windowTest.GetX()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window Y-Coordinate", max_key_len, windowTest.GetY()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window Width", max_key_len, windowTest.GetWidth()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window Minimum Width", max_key_len, windowTest.GetMinimumWidth()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window Maximum Width", max_key_len, windowTest.GetMaximumWidth()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window Height", max_key_len, windowTest.GetHeight()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window Minimum Height", max_key_len, windowTest.GetMinimumHeight()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Window Maximum Height", max_key_len, windowTest.GetMaximumHeight()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:s}", "Window Pixel Format", max_key_len, windowTest.GetPixelFormatName()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:s}", "Window is only shown", max_key_len, windowTest.CheckWindowFlags(SDML::Video::WindowFlag::SHOWN) ? "True" : "False") << std::endl;
		std::cout << fmt::format("{:>{}s}: {:s}", "Window is both shown and resizable", max_key_len, windowTest.CheckWindowFlags(SDML::Video::WindowFlag::SHOWN | SDML::Video::WindowFlag::RESIZABLE) ? "True" : "False") << std::endl;
		std::cout << fmt::format("{:>{}s}: {:s}", "Window is only resizable", max_key_len, windowTest.CheckWindowFlags(SDML::Video::WindowFlag::RESIZABLE) ? "True" : "False") << std::endl;
		std::cout << fmt::format("{:>{}s}: {:s}", "Display Name for Window", max_key_len, windowTest.GetDisplayName()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Display Width", max_key_len, windowTest.GetDisplayWidth()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Display Height", max_key_len, windowTest.GetDisplayHeight()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:s}", "Display Orientation", max_key_len, display_orientation_string) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:s}", "Display Mode Pixel Format", max_key_len, windowTest.GetDisplayModePixelFormatName()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Display Mode Width", max_key_len, windowTest.GetDisplayModeWidth()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Display Mode Height", max_key_len, windowTest.GetDisplayModeHeight()) << std::endl;
		std::cout << fmt::format("{:>{}s}: {:d}", "Display Mode Refresh Rate", max_key_len, windowTest.GetDisplayModeRefreshRate()) << std::endl;

		SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

		/*
		std::cout << SDML::Video::Drivers::GetNumDrivers() << std::endl;
		std::cout << SDML::Video::Drivers::GetCurrentDriverName() << std::endl;
		std::cout << SDML::Video::Drivers::GetDriverNames() << std::endl;
		std::cout << "\n" << std::endl;
		*/

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
