#ifndef IMAGE_WRAPPER_h
#define IMAGE_WRAPPER_h

#include <SDL2/SDL.h>

namespace SDL
{

using PixelFormat = SDL_PixelFormat;

Uint32 MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b);

}

#endif
