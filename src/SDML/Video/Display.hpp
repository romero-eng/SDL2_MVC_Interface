#ifndef DISPLAY_H
#define DISPLAY_H

// Third-party Libraries
#include <SDL2/SDL.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <string>
#include <string_view>
#include <iostream>


namespace SDML
{
	namespace Video
	{
		namespace Displays
		{
			int GetNumDisplays();

			std::string_view GetDisplayName(int displayIndex);

			int GetDisplayWidth(int DisplayIndex);

			int GetDisplayHeight(int DisplayIndex);
		}
	}
}

#endif
