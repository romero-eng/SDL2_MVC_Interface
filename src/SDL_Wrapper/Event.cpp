
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Event.hpp"


int SDL::PollEvent(SDL::Event* event)
{
	return SDL_PollEvent(event);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
