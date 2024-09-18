
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Rectangle.hpp"


int SDL::FillRect(SDL::CPU::Pictures::Picture* dst, const Rect* rect, Uint32 color)
{
	return SDL_FillRect(dst, rect, color);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
