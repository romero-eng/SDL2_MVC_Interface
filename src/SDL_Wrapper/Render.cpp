
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Render.hpp"
#include <fmt/format.h>
#include <iostream>
#include <utility>

Uint32 operator|(SDL::RendererFlags first_flag, SDL::RendererFlags second_flag)
{
    return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}

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

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
