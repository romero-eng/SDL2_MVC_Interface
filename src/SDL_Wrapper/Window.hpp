#ifndef WINDOWS_WRAPPER_h
#define WINDOWS_WRAPPER_h

#include "Canvases/Surface.hpp"

#include <SDL2/SDL.h>

namespace SDL
{

using Window = SDL_Window;

Window* CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags);

void DestroyWindow(Window* window);

const char* GetWindowTitle(Window* window);

Surfaces::Surface* GetWindowSurface(Window* window);

int UpdateWindowSurface(Window* window);

}

#endif
