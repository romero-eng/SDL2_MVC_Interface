
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Picture.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages


SDL::GPU::Pictures::Picture* SDL::GPU::Pictures::CreateFromSurface(SDL::GPU::Painting::Paintbrush* renderer,
                                                         SDL::CPU::Pictures::Picture* surfaceToConvert)
{
    SDL::GPU::Pictures::Picture* texture {SDL_CreateTextureFromSurface(renderer, surfaceToConvert)};

    if (texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }

    return texture;
}

SDL::GPU::Pictures::Picture* SDL::GPU::Pictures::LoadFromFile(fs::path&& bitmap_path,
                                                    SDL::GPU::Painting::Paintbrush* renderer)
{
	return SDL::GPU::Pictures::LoadFromFile(bitmap_path, renderer);
}

SDL::GPU::Pictures::Picture* SDL::GPU::Pictures::LoadFromFile(fs::path& bitmap_path,
                                                    SDL::GPU::Painting::Paintbrush* renderer)
{
	SDL::CPU::Pictures::Picture* tmpSurface { SDL::CPU::Pictures::LoadFromFile(bitmap_path) };
	SDL::GPU::Pictures::Picture* loaded_texture { SDL::GPU::Pictures::CreateFromSurface(renderer, tmpSurface) };
	SDL::CPU::Pictures::FreeSurface(tmpSurface);

	if (loaded_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", bitmap_path.filename().c_str()); 
	}

	return loaded_texture;
}

void SDL::GPU::Pictures::Destroy(SDL::GPU::Pictures::Picture* texture)
{
    SDL_DestroyTexture(texture);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
