#ifndef WINDOWS_WRAPPER_h
#define WINDOWS_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace Canvassing { using Canvas = SDL_Window; } }
#include "CPU/Image.hpp"

namespace SDL
{
    namespace Canvassing
    {
        Canvas* Create(const char* title, int x, int y, int w, int h, Uint32 flags);

        void Destroy(Canvas* window);

        const char* GetTitle(Canvas* window);

        CPU::Images::Image* GetSurface(Canvas* window);

        int UpdateSurface(Canvas* window);
    }
}

#endif
