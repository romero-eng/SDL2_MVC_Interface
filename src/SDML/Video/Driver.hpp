#ifndef DRIVER_H
#define DRIVER_H

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
		std::size_t GetNumVideoDrivers();

		std::string GetCurrentVideoDriver();

		std::vector<std::string> GetVideoDrivers();
	}
}

std::ostream& operator<<(std::ostream& output_stream, std::vector<std::string> strings_to_concatenate);


#endif
