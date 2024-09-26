#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDML/Subsystem.hpp"
#include "SDML/Window.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <vector>
#include <string_view>
#include <iostream>


namespace SDML
{
	namespace Video
	{
		std::size_t GetNumVideoDrivers()
		{
			std::size_t num_video_drivers {static_cast<std::size_t>(SDL_GetNumVideoDrivers())};

			if(num_video_drivers < 1) { throw std::string("Could not detect any Video Drivers: {:s}", SDL_GetError()); }

			return num_video_drivers;
		}

		std::string GetCurrentVideoDriver() { return std::string {SDL_GetCurrentVideoDriver()}; }
		

		std::vector<std::string> GetVideoDrivers()
		{
			std::size_t num_video_drivers {GetNumVideoDrivers()};

			std::vector<std::string> video_drivers(num_video_drivers);

			for (std::size_t video_driver_index = 0; video_driver_index < num_video_drivers; video_driver_index++)
			{
				video_drivers[video_driver_index] = std::string {SDL_GetVideoDriver(static_cast<int>(video_driver_index))};
			}

			return video_drivers;
		}
	}
}


std::ostream& operator<<(std::ostream& output_stream, std::vector<std::string> strings_to_concatenate)
{
	if(strings_to_concatenate.size() > 1)
	{
		output_stream << "[";
		for (std::size_t string_index = 0; string_index < strings_to_concatenate.size(); string_index++)
		{
			output_stream << strings_to_concatenate[string_index];
			if(string_index < strings_to_concatenate.size() - 1)
			{
				output_stream << ", ";
			}
		}
		output_stream << "]";
	}
	else
	{
		output_stream << "[" + strings_to_concatenate[0] + "]";
	}

	return output_stream;
}


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);

	try
	{
		SDML::Video::Window windowTest {"Test", 640, 480, SDML::Video::WindowFlag::RESIZABLE};
		windowTest.SetMinimumArea(  10,   10);
		windowTest.SetMaximumArea(1000, 1000);
		windowTest.Flash(SDML::Video::FlashOperation::UNTIL_FOCUSED);

		std::cout << SDML::Video::GetNumVideoDrivers() << std::endl;
		std::cout << SDML::Video::GetCurrentVideoDriver() << std::endl;
		std::cout << SDML::Video::GetVideoDrivers() << std::endl;
		std::cout << "\n" << std::endl;

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
