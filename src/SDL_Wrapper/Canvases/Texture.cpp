
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Texture.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <iostream> // Needed for printing info to stdout


SDL::Textures::Texture* SDL::Textures::CreateFromSurface(SDL::Rendering::Renderer* renderer,
                                                         SDL::Surfaces::Surface* surfaceToConvert)
{
    SDL::Textures::Texture* texture {SDL_CreateTextureFromSurface(renderer, surfaceToConvert)};

    if (texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }
    else
    {
        std::cout << "Created Texture\n";
    }

    return texture;
}

void SDL::Textures::Destroy(SDL::Textures::Texture* texture)
{
    std::cout << "Destroyed Texture\n";
    SDL_DestroyTexture(texture);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
