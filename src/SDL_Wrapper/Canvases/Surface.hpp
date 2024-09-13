#ifndef SURFACE_WRAPPER_h
#define SURFACE_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL{ namespace Surfaces { using Surface = SDL_Surface; } }

namespace SDL
{
    namespace Surfaces
    {
        void FreeSurface(Surface* surface);
    }
}


#endif
