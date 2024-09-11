#ifndef EVENT_WRAPPER_h
#define EVENT_WRAPPER_h

#include <SDL2/SDL.h>

namespace SDL
{

using Event = SDL_Event;

int PollEvent(SDL_Event* event);

}

#endif
