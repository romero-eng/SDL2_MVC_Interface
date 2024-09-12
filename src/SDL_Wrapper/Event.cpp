
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Event.hpp"
#include <utility>


bool SDL::PollEvent(SDL::Event& event)
{
	return SDL_PollEvent(&event) == 1;
}


bool operator==(Uint32 type, SDL::EventTypes event_type)
{
    return type == std::to_underlying(event_type);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
