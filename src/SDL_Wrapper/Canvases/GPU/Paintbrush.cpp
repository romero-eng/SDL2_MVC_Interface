
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Paintbrush.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <utility> // Needed for retrieving underlying type of scoped enumerations


SDL::GPU::Painting::Paintbrush* SDL::GPU::Painting::Create(SDL::Canvassing::Canvas* window,
                                                 int index,
                                                 SDL::GPU::Painting::Flags flag,
                                                 Uint8 r,
                                                 Uint8 g,
                                                 Uint8 b,
                                                 Uint8 a)
{
    return SDL::GPU::Painting::Create(window, index, static_cast<Uint32>(flag), r, g, b, a);
}

SDL::GPU::Painting::Paintbrush* SDL::GPU::Painting::Create(SDL::Canvassing::Canvas* window,
                                                 int index,
                                                 Uint32 flags,
                                                 Uint8 r,
                                                 Uint8 g,
                                                 Uint8 b,
                                                 Uint8 a)
{
    SDL::GPU::Painting::Paintbrush* renderer {SDL_CreateRenderer(window, index, flags)};
    
    if (renderer == nullptr)
    {
        throw fmt::format("Renderer could not be created for the '{:s}' Window:\n\n{:s}\n", SDL::Canvassing::GetTitle(window), SDL_GetError());
    }
    else
    {
        SDL::GPU::Painting::SetDrawColor(renderer, r, g, b, a);
    }

    return renderer;
}

void SDL::GPU::Painting::Destroy(SDL::GPU::Painting::Paintbrush* renderer)
{
    SDL_DestroyRenderer(renderer);
}

bool SDL::GPU::Painting::SetDrawColor(SDL::GPU::Painting::Paintbrush* renderer,
                                  Uint8 r,
                                  Uint8 g,
                                  Uint8 b,
                                  Uint8 a)
{
    return SDL_SetRenderDrawColor(renderer, r, g, b, a) >= 0;
}

void SDL::GPU::Painting::Clear(SDL::GPU::Painting::Paintbrush* renderer)
{
    if (SDL_RenderClear(renderer) < 0)
    {
        throw fmt::format("Could not clear the Renderer: {:s}", SDL_GetError());
    }
}

void SDL::GPU::Painting::Copy(SDL::GPU::Painting::Paintbrush* renderer,
                          SDL::GPU::Images::Image* texture,
                          const SDL::Rect* srcrect,
                          const SDL::Rect* dstrect)
{
    if (SDL_RenderCopy(renderer, texture, srcrect, dstrect) < 0)
    {
        throw fmt::format("Could not copy from the texture to the renderer: {:s}", SDL_GetError());
    }
}

void SDL::GPU::Painting::Present(SDL::GPU::Painting::Paintbrush* renderer)
{
    SDL_RenderPresent(renderer);
}

Uint32 operator|(SDL::GPU::Painting::Flags first_flag,
                 SDL::GPU::Painting::Flags second_flag)
{
    return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
