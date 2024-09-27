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
            enum class Orientation
            {
                UNKNOWN,
                LANDSCAPE,
                LANDSCAPE_FLIPPED,
                PORTRAIT,
                PORTRAIT_FLIPPED
            };

			int GetNumDisplays();

			std::string_view GetName(int displayIndex);

			int GetWidth(int DisplayIndex);

			int GetHeight(int DisplayIndex);

            Orientation GetOrientation(int DisplayIndex);
		}
	}
}


std::ostream& operator<<(std::ostream& output,
                         SDML::Video::Displays::Orientation orientation);


#endif
