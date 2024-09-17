
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "GPU_Image.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages


SDL::GPU_Images::GPU_Image* SDL::GPU_Images::CreateFromSurface(SDL::GPU_Painting::GPU_Paintbrush* renderer,
                                                         SDL::CPU::Images::Image* surfaceToConvert)
{
    SDL::GPU_Images::GPU_Image* texture {SDL_CreateTextureFromSurface(renderer, surfaceToConvert)};

    if (texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }

    return texture;
}

SDL::GPU_Images::GPU_Image* SDL::GPU_Images::LoadFromFile(fs::path&& bitmap_path,
                                                    SDL::GPU_Painting::GPU_Paintbrush* renderer)
{
	return SDL::GPU_Images::LoadFromFile(bitmap_path, renderer);
}

SDL::GPU_Images::GPU_Image* SDL::GPU_Images::LoadFromFile(fs::path& bitmap_path,
                                                    SDL::GPU_Painting::GPU_Paintbrush* renderer)
{
	SDL::CPU::Images::Image* tmpSurface { SDL::CPU::Images::LoadFromFile(bitmap_path) };
	SDL::GPU_Images::GPU_Image* loaded_texture { SDL::GPU_Images::CreateFromSurface(renderer, tmpSurface) };
	SDL::CPU::Images::FreeSurface(tmpSurface);

	if (loaded_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", bitmap_path.filename().c_str()); 
	}

	return loaded_texture;
}

void SDL::GPU_Images::Destroy(SDL::GPU_Images::GPU_Image* texture)
{
    SDL_DestroyTexture(texture);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
