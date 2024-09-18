
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Canvas.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages


SDL::Canvassing::Canvas* SDL::Canvassing::Create(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	SDL::Canvassing::Canvas* window {SDL_CreateWindow(title, x, y, w, h, flags)};

	if (window == nullptr)
	{
		throw fmt::format("\nWindow could not be created! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}

	return window;
}

void SDL::Canvassing::Destroy(SDL::Canvassing::Canvas* window)
{
	SDL_DestroyWindow(window);
}

const char* SDL::Canvassing::GetTitle(SDL::Canvassing::Canvas* window)
{
	return SDL_GetWindowTitle(window);
}

SDL::CPU::Pictures::Picture* SDL::Canvassing::GetSurface(SDL::Canvassing::Canvas* window)
{
	SDL::CPU::Pictures::Picture* surface = SDL_GetWindowSurface(window);

	if (surface == nullptr)
	{
		throw fmt::format("\nSurface could not be obtained from '{:s}' Window! SDL_Error:\n\n{:s}\n\n", GetTitle(window), SDL_GetError() );
	}

	return surface;
}

int SDL::Canvassing::UpdateSurface(SDL::Canvassing::Canvas* window)
{
	return SDL_UpdateWindowSurface(window);
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
