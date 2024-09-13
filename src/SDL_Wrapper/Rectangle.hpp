#ifndef RECTANGLE_WRAPPER_h
#define RECTANGLE_WRAPPER_h

#include "Canvases/Surface.hpp"
#include <SDL2/SDL.h>

namespace SDL
{

using Rect = SDL_Rect;

int FillRect(Surfaces::Surface* dst, const Rect* rect, Uint32 color);

}

#endif
