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
		namespace Drivers
		{
			std::size_t GetNumDrivers();

			std::string GetCurrentDriverName();

			std::vector<std::string> GetDriverNames();
		}
	}
}

std::ostream& operator<<(std::ostream& output_stream, std::vector<std::string> strings_to_concatenate);


#endif
