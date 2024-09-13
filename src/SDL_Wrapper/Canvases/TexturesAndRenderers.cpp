
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "TexturesAndRenderers.hpp"
#include <fmt/format.h>
#include <iostream>
#include <utility>


SDL::Renderer* SDL::CreateRenderer(SDL::Window* window, int index, SDL::RendererFlags flag, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    return SDL::CreateRenderer(window, index, static_cast<Uint32>(flag), r, g, b, a);
}

SDL::Renderer* SDL::CreateRenderer(SDL::Window* window, int index, Uint32 flags, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL::Renderer* renderer {SDL_CreateRenderer(window, index, flags)};
    
    if (renderer == nullptr)
    {
        throw fmt::format("Renderer could not be created for the '{:s}' Window:\n\n{:s}\n", SDL::GetWindowTitle(window), SDL_GetError());
    }
    else
    {
        SDL::SetRenderDrawColor(renderer, r, g, b, a);
        std::cout << fmt::format("Renderer created for the '{:s}' Window\n", SDL::GetWindowTitle(window));
    }

    return renderer;
}

void SDL::DestroyRenderer(SDL::Renderer* renderer)
{
    std::cout << "Destroyed Renderer\n";
    SDL_DestroyRenderer(renderer);
}

bool SDL::SetRenderDrawColor(SDL::Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    std::cout << fmt::format("Renderer set with the following RBG Values for Drawing Operations: (Red: {:d} | Green {:d} | Blue {:d} | Alpha {:d})\n", r, g, b, a);
    return SDL_SetRenderDrawColor(renderer, r, g, b, a) >= 0;
}

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

void SDL::RenderClear(SDL::Renderer* renderer)
{
    if (SDL_RenderClear(renderer) < 0)
    {
        throw fmt::format("Could not clear the Renderer: {:s}", SDL_GetError());
    }
    else
    {
        std::cout << "Cleared the Renderer";
    }
}

void SDL::RenderCopy(SDL::Renderer* renderer,
                     SDL::Texture* texture,
                     const SDL::Rect* srcrect,
                     const SDL::Rect* dstrect)
{
    if (SDL_RenderCopy(renderer, texture, srcrect, dstrect) < 0)
    {
        throw fmt::format("Could not copy from the texture to the renderer: {:s}", SDL_GetError());
    }
    else
    {
        std::cout << "Copied from the texture to the renderer";
    }
}

void SDL::RenderPresent(SDL::Renderer* renderer)
{
    SDL_RenderPresent(renderer);
}

Uint32 operator|(SDL::RendererFlags first_flag, SDL::RendererFlags second_flag)
{
    return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
