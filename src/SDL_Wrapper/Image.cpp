
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Image.hpp"
#include <fmt/format.h>
#include <utility>


Uint32 SDL::MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(format, r, g, b);
}

void SDL::BlitSurfaceOntoWindow(SDL::Canvassing::Canvas* window, SDL::CPU_Images::CPU_Image* src, const SDL::Rect* srcrect, SDL::Rect* dstrect)
{
	SDL::BlitSurface(src,
					 srcrect,
					 SDL::Canvassing::GetSurface(window),
					 dstrect);
}

void SDL::BlitSurface(SDL::CPU_Images::CPU_Image* src, const SDL::Rect* srcrect, SDL::CPU_Images::CPU_Image* dst, SDL::Rect* dstrect)
{
	if(SDL_BlitSurface(src, srcrect, dst, dstrect) != 0)
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}
}

void IMG::Init(InitFlags flag)
{
	IMG::Init(std::to_underlying(flag));
}

void IMG::Init(Uint32 flags)
{
	if(!( static_cast<Uint32>(IMG_Init(static_cast<int>(flags))) & flags ))
	{
		throw fmt::format("SDL Images could not be initialized: {:s}\n", IMG_GetError());
	}
}

void IMG::Quit(void)
{
	IMG_Quit();
}

Uint32 operator|(IMG::InitFlags first_flag, IMG::InitFlags second_flag)
{
	return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}

Uint32 operator|(Uint32 first_flag, IMG::InitFlags second_flag)
{
	return first_flag | std::to_underlying(second_flag);
}

Uint32 operator|(IMG::InitFlags first_flag, Uint32 second_flag)
{
	return std::to_underlying(first_flag) | second_flag;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
