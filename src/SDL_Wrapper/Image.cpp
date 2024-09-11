
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Surface.hpp"
#include "Image.hpp"
#include <fmt/format.h>
#include <iostream>


Uint32 SDL::MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(format, r, g, b);
}

SDL::Surface* SDL::Load_BMP(const char* bitmap_path)
{
	SDL::Surface* bitmap{SDL_LoadBMP(bitmap_path)};

	if(bitmap == nullptr)
	{
		throw fmt::format("Could not load '{:s}' bitmap: {:s}", bitmap_path, SDL_GetError());
	}
	else
	{
		std::cout << fmt::format("Loaded '{:s}' bitmap as Surface", bitmap_path);
	}
	
	return bitmap;
}

void SDL::BlitSurface(SDL::Surface* src, const SDL::Rect* srcrect, SDL::Surface* dst, SDL::Rect* dstrect)
{
	if(SDL_BlitSurface(src, srcrect, dst, dstrect) == 0)
	{
		std::cout << "Blitted 'src' Surface onto 'dst' Surface";
	}
	else
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}
}

#endif
