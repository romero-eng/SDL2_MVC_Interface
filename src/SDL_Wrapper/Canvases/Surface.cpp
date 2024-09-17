
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Surface.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <iostream> // Needed for printing info to stdout


SDL::Surfaces::Surface* SDL::Surfaces::Load_BMP(fs::path&& bitmap_path)
{	
	return SDL::Surfaces::Load_BMP(bitmap_path);
}

SDL::Surfaces::Surface* SDL::Surfaces::Load_BMP(fs::path& bitmap_path)
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

SDL::Surfaces::Surface* SDL::Surfaces::LoadSurface(fs::path&& bitmap_path)
{
	return SDL::Surfaces::LoadSurface(bitmap_path);
}

SDL::Surfaces::Surface* SDL::Surfaces::LoadSurface(fs::path& bitmap_path)
{
	SDL::Surfaces::Surface* tmpSurface { IMG_Load(bitmap_path.string().c_str()) };

	if (tmpSurface == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", bitmap_path.filename().c_str());
	}

	return tmpSurface;
}

void SDL::Surfaces::FreeSurface(SDL::Surfaces::Surface* surface)
{
	std::cout << "Freeing Surface\n";
	SDL_FreeSurface(surface);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
