#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Display.hpp"

int SDML::Video::Displays::GetNumDisplays()
{
	int num_displays {SDL_GetNumVideoDisplays()};

	if(num_displays < 1) { throw std::string{"No Video Displays were detected"}; }

	return num_displays;
}


std::string_view SDML::Video::Displays::GetDisplayName(int displayIndex)
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


int SDML::Video::Displays::GetDisplayWidth(int DisplayIndex)
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


int SDML::Video::Displays::GetDisplayHeight(int DisplayIndex)
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

#endif
