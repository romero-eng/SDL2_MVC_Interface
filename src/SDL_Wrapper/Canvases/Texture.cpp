
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Texture.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages


SDL::Textures::Texture* SDL::Textures::CreateFromSurface(SDL::Rendering::Renderer* renderer,
                                                         SDL::Surfaces::Surface* surfaceToConvert)
{
    SDL::Textures::Texture* texture {SDL_CreateTextureFromSurface(renderer, surfaceToConvert)};

    if (texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }

    return texture;
}

SDL::Textures::Texture* SDL::Textures::LoadFromFile(fs::path&& bitmap_path,
                                                    SDL::Rendering::Renderer* renderer)
{
	return SDL::Textures::LoadFromFile(bitmap_path, renderer);
}

SDL::Textures::Texture* SDL::Textures::LoadFromFile(fs::path& bitmap_path,
                                                    SDL::Rendering::Renderer* renderer)
{
	SDL::Surfaces::Surface* tmpSurface { SDL::Surfaces::LoadFromFile(bitmap_path) };
	SDL::Textures::Texture* loaded_texture { SDL::Textures::CreateFromSurface(renderer, tmpSurface) };
	SDL::Surfaces::FreeSurface(tmpSurface);

	if (loaded_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", bitmap_path.filename().c_str()); 
	}

	return loaded_texture;
}

void SDL::Textures::Destroy(SDL::Textures::Texture* texture)
{
    SDL_DestroyTexture(texture);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
