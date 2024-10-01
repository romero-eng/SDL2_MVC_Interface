#ifndef DRIVER_H
#define DRIVER_H

// Third-party Libraries
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <vector>
#include <string>


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


#endif
