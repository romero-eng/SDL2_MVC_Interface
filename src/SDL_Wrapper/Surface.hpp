#ifndef SURFACE_WRAPPER_h
#define SURFACE_WRAPPER_h

#include "Window.hpp"
#include <SDL2/SDL.h>

namespace SDL
{

using Surface = SDL_Surface;

Surface* GetWindowSurface(Window* window);

int UpdateWindowSurface(Window* window);

}


#endif
