
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Image.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages


SDL::GPU::Images::Image* SDL::GPU::Images::CreateFromSurface(SDL::GPU::Painting::Paintbrush* renderer,
                                                         SDL::CPU::Images::Image* surfaceToConvert)
{
    SDL::GPU::Images::Image* texture {SDL_CreateTextureFromSurface(renderer, surfaceToConvert)};

    if (texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }

    return texture;
}

SDL::GPU::Images::Image* SDL::GPU::Images::LoadFromFile(fs::path&& bitmap_path,
                                                    SDL::GPU::Painting::Paintbrush* renderer)
{
	return SDL::GPU::Images::LoadFromFile(bitmap_path, renderer);
}

SDL::GPU::Images::Image* SDL::GPU::Images::LoadFromFile(fs::path& bitmap_path,
                                                    SDL::GPU::Painting::Paintbrush* renderer)
{
	SDL::CPU::Images::Image* tmpSurface { SDL::CPU::Images::LoadFromFile(bitmap_path) };
	SDL::GPU::Images::Image* loaded_texture { SDL::GPU::Images::CreateFromSurface(renderer, tmpSurface) };
	SDL::CPU::Images::FreeSurface(tmpSurface);

	if (loaded_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", bitmap_path.filename().c_str()); 
	}

	return loaded_texture;
}

void SDL::GPU::Images::Destroy(SDL::GPU::Images::Image* texture)
{
    SDL_DestroyTexture(texture);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
