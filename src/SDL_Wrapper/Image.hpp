#ifndef IMAGE_WRAPPER_h
#define IMAGE_WRAPPER_h

#include <filesystem>
#include "Surface.hpp"
#include "Rectangle.hpp"
#include <SDL2/SDL.h>
namespace fs = std::filesystem;

namespace SDL
{

using PixelFormat = SDL_PixelFormat;

Uint32 MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b);

SDL::Surface* Load_BMP(fs::path&& bitmap_path);

Surface* Load_BMP(fs::path& bitmap_path);

void BlitSurfaceOntoWindow(Window* window, Surface* src, const Rect* srcrect, Rect* dstrect);

void BlitSurface(Surface* src, const Rect* srcrect, Surface* dst, Rect* dstrect);

}

#endif
