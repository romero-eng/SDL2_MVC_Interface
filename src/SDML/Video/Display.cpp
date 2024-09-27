#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Display.hpp"


int SDML::Video::Displays::GetNumDisplays()
{
	int num_displays {SDL_GetNumVideoDisplays()};

	if(num_displays < 1) { throw std::string{"No Video Displays were detected"}; }

	return num_displays;
}


std::string_view SDML::Video::Displays::GetName(int displayIndex)
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


int SDML::Video::Displays::GetWidth(int DisplayIndex)
{
	SDL_Rect FullscreenBounds {};
	SDL_Rect UsableBounds {};

	if(SDL_GetDisplayBounds(DisplayIndex, &FullscreenBounds) < 0)
	{
		throw fmt::format("Could not retrive fullscreen boundaries for '{:s}' Display: {:s}",
						  GetName(DisplayIndex),
						  SDL_GetError());
	}

	if(SDL_GetDisplayUsableBounds(DisplayIndex, &UsableBounds) < 0)
	{
		throw fmt::format("Could not retrive usable boundaries for '{:s}' Display: {:s}",
						  GetName(DisplayIndex),
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


int SDML::Video::Displays::GetHeight(int DisplayIndex)
{
	SDL_Rect FullscreenBounds {};
	SDL_Rect UsableBounds {};

	if(SDL_GetDisplayBounds(DisplayIndex, &FullscreenBounds) < 0)
	{
		throw fmt::format("Could not retrive fullscreen boundaries for '{:s}' Display: {:s}",
						  GetName(DisplayIndex),
						  SDL_GetError());
	}

	if(SDL_GetDisplayUsableBounds(DisplayIndex, &UsableBounds) < 0)
	{
		throw fmt::format("Could not retrive usable boundaries for '{:s}' Display: {:s}",
						  GetName(DisplayIndex),
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


SDML::Video::Displays::Orientation SDML::Video::Displays::GetOrientation(int DisplayIndex)
{
    Orientation display_orientation;

    switch(SDL_GetDisplayOrientation(DisplayIndex))
    {
        case SDL_ORIENTATION_UNKNOWN:
            display_orientation = Orientation::UNKNOWN;
            break;
        case SDL_ORIENTATION_LANDSCAPE:
            display_orientation = Orientation::LANDSCAPE;
            break;
        case SDL_ORIENTATION_LANDSCAPE_FLIPPED:
            display_orientation = Orientation::LANDSCAPE_FLIPPED;
            break;
        case SDL_ORIENTATION_PORTRAIT:
            display_orientation = Orientation::PORTRAIT;
            break;
        case SDL_ORIENTATION_PORTRAIT_FLIPPED:
            display_orientation = Orientation::PORTRAIT_FLIPPED;
            break;
    }

    return display_orientation;
}


std::ostream& operator<<(std::ostream& output,
                         SDML::Video::Displays::Orientation orientation)
{
    switch(orientation)
    {
        case SDML::Video::Displays::Orientation::UNKNOWN:
            output << "Unknown";
            break;
        case SDML::Video::Displays::Orientation::LANDSCAPE:
            output << "Landscape";
            break;
        case SDML::Video::Displays::Orientation::LANDSCAPE_FLIPPED:
            output << "Landscape Flipped";
            break;
        case SDML::Video::Displays::Orientation::PORTRAIT:
            output << "Portrait";
            break;
        case SDML::Video::Displays::Orientation::PORTRAIT_FLIPPED:
            output << "Portrait Flipped";
            break;
    }

    return output;
}


#endif
