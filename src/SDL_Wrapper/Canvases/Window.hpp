#ifndef WINDOWS_WRAPPER_h
#define WINDOWS_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace Windowing { using Window = SDL_Window; } }
#include "Surface.hpp"

namespace SDL
{
    namespace Windowing
    {
        Window* Create(const char* title, int x, int y, int w, int h, Uint32 flags);

        void Destroy(Window* window);

        const char* GetTitle(Window* window);

        Surfaces::Surface* GetSurface(Window* window);

        int UpdateSurface(Window* window);
    }
}

#endif
