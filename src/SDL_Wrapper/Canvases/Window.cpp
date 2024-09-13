
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Window.hpp"
#include <fmt/format.h>
#include <iostream>


SDL::Windowing::Window* SDL::Windowing::Create(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	SDL::Windowing::Window* window {SDL_CreateWindow(title, x, y, w, h, flags)};

	if (window == nullptr)
	{
		throw fmt::format("\nWindow could not be created! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}
	else
	{
		std::cout << fmt::format("Created '{:s}' Window", title);
	}

	return window;
}

void SDL::Windowing::Destroy(SDL::Windowing::Window* window)
{
	SDL_DestroyWindow(window);
}

const char* SDL::Windowing::GetTitle(SDL::Windowing::Window* window)
{
	return SDL_GetWindowTitle(window);
}

SDL::Surfaces::Surface* SDL::Windowing::GetSurface(SDL::Windowing::Window* window)
{
	SDL::Surfaces::Surface* surface = SDL_GetWindowSurface(window);

	if (surface == nullptr)
	{
		throw fmt::format("\nSurface could not be obtained from '{:s}' Window! SDL_Error:\n\n{:s}\n\n", GetTitle(window), SDL_GetError() );
	}
	else
	{
		std::cout << fmt::format("\nGot Surface from '{:s}' Window\n", GetTitle(window));
	}

	return surface;
}

int SDL::Windowing::UpdateSurface(SDL::Windowing::Window* window)
{
	std::cout << fmt::format("Updating surface for '{:s} Window'\n", GetTitle(window));
	return SDL_UpdateWindowSurface(window);
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
