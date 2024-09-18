#ifndef RECTANGLE_WRAPPER_h
#define RECTANGLE_WRAPPER_h

#include "Canvases/CPU/Picture.hpp"
#include <SDL2/SDL.h>

namespace SDL
{

using Rect = SDL_Rect;

int FillRect(CPU::Pictures::Picture* dst, const Rect* rect, Uint32 color);

}

#endif
