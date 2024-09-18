
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "PictureIdea.hpp"


SDL_Surface* SDL::Painting::PictureIdea::LoadSurfaceFromFile(fs::path& image_path)
{
	if(!fs::exists(image_path))
	{
		throw fmt::format("The '{:s}' Image file does not exist", image_path.string().c_str());
	}

	if(!fs::is_regular_file(image_path))
	{
		throw fmt::format("The '{:s}' Image file does not seem to be a regular file", image_path.string().c_str());
	}

	SDL_Surface* tmpSurface;

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


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
