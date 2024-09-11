#ifndef IMAGE_WRAPPER_h
#define IMAGE_WRAPPER_h

#include "Surface.hpp"
#include "Rectangle.hpp"
#include <SDL2/SDL.h>

namespace SDL
{

using PixelFormat = SDL_PixelFormat;

Uint32 MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b);

Surface* Load_BMP(const char* file);

void BlitSurface(Surface* src, const Rect* srcrect, Surface* dst, Rect* dstrect);

}

#endif
