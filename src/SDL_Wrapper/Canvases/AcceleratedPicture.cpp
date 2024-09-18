
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "AcceleratedPicture.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages


SDL_Texture* SDL::AcceleratedPicture::CreateTextureFromSurface(SDL::GPU::Painting::Paintbrush* renderer,
                                                               SDL_Surface* surfaceToConvert)
{
   SDL_Texture* texture {SDL_CreateTextureFromSurface(renderer, surfaceToConvert)};

    if (texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }

    return texture;
}


SDL_Surface* SDL::AcceleratedPicture::LoadSurfaceFromFile(fs::path& image_path)
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


SDL_Texture* SDL::AcceleratedPicture::LoadTextureFromFile(fs::path& image_file,
                                                          SDL::GPU::Painting::Paintbrush* renderer)
{
	SDL_Surface* tmpSurface { this->LoadSurfaceFromFile(image_file) };
	SDL_Texture* loaded_texture { this->CreateTextureFromSurface(renderer, tmpSurface) };
	SDL_FreeSurface(tmpSurface);

	if (loaded_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", image_file.filename().c_str()); 
	}

	return loaded_texture;
}


SDL::AcceleratedPicture::AcceleratedPicture(SDL::GPU::Painting::Paintbrush* render,
                                            SDL_Surface* surfaceToConvert): picture_texture{CreateTextureFromSurface(render, surfaceToConvert)} {}


SDL::AcceleratedPicture::~AcceleratedPicture()
{
    SDL_DestroyTexture(this->picture_texture);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
