
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "GPU_Paintbrush.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <utility> // Needed for retrieving underlying type of scoped enumerations


SDL::GPU_Painting::GPU_Paintbrush* SDL::GPU_Painting::Create(SDL::Canvassing::Canvas* window,
                                                 int index,
                                                 SDL::GPU_Painting::Flags flag,
                                                 Uint8 r,
                                                 Uint8 g,
                                                 Uint8 b,
                                                 Uint8 a)
{
    return SDL::GPU_Painting::Create(window, index, static_cast<Uint32>(flag), r, g, b, a);
}

SDL::GPU_Painting::GPU_Paintbrush* SDL::GPU_Painting::Create(SDL::Canvassing::Canvas* window,
                                                 int index,
                                                 Uint32 flags,
                                                 Uint8 r,
                                                 Uint8 g,
                                                 Uint8 b,
                                                 Uint8 a)
{
    SDL::GPU_Painting::GPU_Paintbrush* renderer {SDL_CreateRenderer(window, index, flags)};
    
    if (renderer == nullptr)
    {
        throw fmt::format("Renderer could not be created for the '{:s}' Window:\n\n{:s}\n", SDL::Canvassing::GetTitle(window), SDL_GetError());
    }
    else
    {
        SDL::GPU_Painting::SetDrawColor(renderer, r, g, b, a);
    }

    return renderer;
}

void SDL::GPU_Painting::Destroy(SDL::GPU_Painting::GPU_Paintbrush* renderer)
{
    SDL_DestroyRenderer(renderer);
}

bool SDL::GPU_Painting::SetDrawColor(SDL::GPU_Painting::GPU_Paintbrush* renderer,
                                  Uint8 r,
                                  Uint8 g,
                                  Uint8 b,
                                  Uint8 a)
{
    return SDL_SetRenderDrawColor(renderer, r, g, b, a) >= 0;
}

void SDL::GPU_Painting::Clear(SDL::GPU_Painting::GPU_Paintbrush* renderer)
{
    if (SDL_RenderClear(renderer) < 0)
    {
        throw fmt::format("Could not clear the Renderer: {:s}", SDL_GetError());
    }
}

void SDL::GPU_Painting::Copy(SDL::GPU_Painting::GPU_Paintbrush* renderer,
                          SDL::GPU_Images::GPU_Image* texture,
                          const SDL::Rect* srcrect,
                          const SDL::Rect* dstrect)
{
    if (SDL_RenderCopy(renderer, texture, srcrect, dstrect) < 0)
    {
        throw fmt::format("Could not copy from the texture to the renderer: {:s}", SDL_GetError());
    }
}

void SDL::GPU_Painting::Present(SDL::GPU_Painting::GPU_Paintbrush* renderer)
{
    SDL_RenderPresent(renderer);
}

Uint32 operator|(SDL::GPU_Painting::Flags first_flag,
                 SDL::GPU_Painting::Flags second_flag)
{
    return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
