
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Image.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages


SDL::CPU::Images::Image* SDL::CPU::Images::LoadFromFile(fs::path&& image_path)
{
	return SDL::CPU::Images::LoadFromFile(image_path);
}

SDL::CPU::Images::Image* SDL::CPU::Images::LoadFromFile(fs::path& image_path)
{
	if(!fs::exists(image_path))
	{
		throw fmt::format("The '{:s}' Image file does not exist", image_path.string().c_str());
	}

	if(!fs::is_regular_file(image_path))
	{
		throw fmt::format("The '{:s}' Image file does not seem to be a regular file", image_path.string().c_str());
	}

	SDL::CPU::Images::Image* tmpSurface;

	if(image_path.extension() == ".bmp")
	{
		SDL_RWops* ops {SDL_RWFromFile(image_path.string().c_str(), "rb")};
		if(ops == nullptr)
		{
			throw fmt::format("Unexpected error in reading '{:s}': {:s}", image_path.string().c_str(), SDL_GetError());
		}

		tmpSurface = SDL_LoadBMP_RW(ops, 1);
	}
	else
	{
		tmpSurface = IMG_Load(image_path.string().c_str());
	}

	if (tmpSurface == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image File: {:s}", image_path.string().c_str(), SDL_GetError());
	}

	return tmpSurface;
}

void SDL::CPU::Images::FreeSurface(SDL::CPU::Images::Image* surface)
{
	SDL_FreeSurface(surface);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
