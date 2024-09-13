
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Texture.hpp"

#include <iostream>

SDL::Texture* SDL::CreateTextureFromSurface(SDL::Renderer* renderer, SDL::Surface* surfaceToConvert)
{
    std::cout << "Created Texture\n";
    return SDL_CreateTextureFromSurface(renderer, surfaceToConvert);
}

void SDL::DestroyTexture(SDL::Texture* texture)
{
    std::cout << "Destroyed Texture\n";
    SDL_DestroyTexture(texture);
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
