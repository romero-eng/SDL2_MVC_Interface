
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Image.hpp"
#include <fmt/format.h>
#include <iostream>


Uint32 SDL::MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(format, r, g, b);
}

SDL::Surface* SDL::Load_BMP(fs::path&& bitmap_path)
{	
	return SDL::Load_BMP(bitmap_path);
}

SDL::Surface* SDL::Load_BMP(fs::path& bitmap_path)
{
	SDL::Surface* bitmap{SDL_LoadBMP(bitmap_path.string().c_str())};

	if(bitmap == nullptr)
	{
		throw fmt::format("Could not load '{:s}' bitmap: {:s}", bitmap_path.stem().string(), SDL_GetError());
	}
	else
	{
		std::cout << fmt::format("Loaded '{:s}' bitmap as Surface\n", bitmap_path.stem().string());
	}
	
	return bitmap;
}

void SDL::BlitSurface(SDL::Surface* src, const SDL::Rect* srcrect, SDL::Surface* dst, SDL::Rect* dstrect)
{
	if(SDL_BlitSurface(src, srcrect, dst, dstrect) == 0)
	{
		std::cout << "Blitted 'src' Surface onto 'dst' Surface\n";
	}
	else
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}
}

#endif
