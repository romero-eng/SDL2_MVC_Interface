
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Surface.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <iostream> // Needed for printing info to stdout


void SDL::FreeSurface(Surface* surface)
{
	std::cout << "Freeing Surface\n";
	SDL_FreeSurface(surface);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
