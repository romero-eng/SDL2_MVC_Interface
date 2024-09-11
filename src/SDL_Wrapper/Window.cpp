
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Window.hpp"
#include <fmt/format.h>
#include <iostream>


SDL_Window* SDL::CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	SDL::Window* window {SDL_CreateWindow(title, x, y, w, h, flags)};

	if (window == nullptr)
	{
		throw fmt::format("\nWindow could not be created! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}
	else
	{
		std::cout << fmt::format("\nCreated '{:s}' Window\n", title);
	}

	return window;
}

void SDL::DestroyWindow(SDL::Window* window)
{
	SDL_DestroyWindow(window);
}

const char* SDL::GetWindowTitle(SDL::Window* window)
{
	return SDL_GetWindowTitle(window);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
