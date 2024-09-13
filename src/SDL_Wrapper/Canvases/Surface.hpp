#ifndef SURFACE_WRAPPER_h
#define SURFACE_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
#include "../Window.hpp"

namespace SDL
{

    using Surface = SDL_Surface;

    Surface* GetWindowSurface(Window* window);

    int UpdateWindowSurface(Window* window);

    void FreeSurface(Surface* surface);

}


#endif
