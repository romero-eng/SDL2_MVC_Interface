
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Surface.hpp"
#include <fmt/format.h>
#include <iostream>


SDL::Surface* SDL::GetWindowSurface(SDL::Window* window)
{
	SDL::Surface* surface = SDL_GetWindowSurface(window);

	if (surface == nullptr)
	{
		throw fmt::format("\nSurface could not be obtained from '{:s}' Window! SDL_Error:\n\n{:s}\n\n", GetWindowTitle(window), SDL_GetError() );
	}
	else
	{
		std::cout << fmt::format("\nGot Surface from '{:s}' Window\n", GetWindowTitle(window));
	}

	return surface;
}

int SDL::UpdateWindowSurface(SDL::Window* window)
{
	return SDL_UpdateWindowSurface(window);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
