
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Image.hpp"
#include <fmt/format.h>
#include <iostream>
#include <utility>


Uint32 SDL::MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(format, r, g, b);
}

SDL::Surfaces::Surface* SDL::Load_BMP(fs::path&& bitmap_path)
{	
	return SDL::Load_BMP(bitmap_path);
}

SDL::Surfaces::Surface* SDL::Load_BMP(fs::path& bitmap_path)
{
	SDL::Surfaces::Surface* bitmap{SDL_LoadBMP(bitmap_path.string().c_str())};

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

void SDL::BlitSurfaceOntoWindow(SDL::Windowing::Window* window, SDL::Surfaces::Surface* src, const SDL::Rect* srcrect, SDL::Rect* dstrect)
{
	SDL::BlitSurface(src,
					 srcrect,
					 SDL::Windowing::GetSurface(window),
					 dstrect);
}

void SDL::BlitSurface(SDL::Surfaces::Surface* src, const SDL::Rect* srcrect, SDL::Surfaces::Surface* dst, SDL::Rect* dstrect)
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
	else
	{
		std::cout << "Initialized SDL Images\n";
	}
}

SDL::Surfaces::Surface* IMG::LoadSurface(fs::path&& bitmap_path)
{
	return IMG::LoadSurface(bitmap_path);
}

SDL::Surfaces::Surface* IMG::LoadSurface(fs::path& bitmap_path)
{
	SDL::Surfaces::Surface* tmpSurface { IMG_Load(bitmap_path.string().c_str()) };

	if (tmpSurface == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", bitmap_path.filename().c_str());
	}

	return tmpSurface;
}

SDL::Textures::Texture* IMG::LoadTexture(fs::path&& bitmap_path, SDL::Rendering::Renderer* renderer)
{
	return IMG::LoadTexture(bitmap_path, renderer);
}

SDL::Textures::Texture* IMG::LoadTexture(fs::path& bitmap_path, SDL::Rendering::Renderer* renderer)
{
	SDL::Surfaces::Surface* tmpSurface { IMG::LoadSurface(bitmap_path) };
	SDL::Textures::Texture* loaded_texture { SDL::Textures::CreateFromSurface(renderer, tmpSurface) };
	SDL::Surfaces::FreeSurface(tmpSurface);

	if (loaded_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", bitmap_path.filename().c_str()); 
	}

	return loaded_texture;
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
