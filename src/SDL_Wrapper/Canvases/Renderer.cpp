
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom wrapper code for SDL2 API
#include "Renderer.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <iostream> // Needed for printing info to stdout
#include <utility> // Needed for retrieving underlying type of scoped enumerations


SDL::Rendering::Renderer* SDL::Rendering::Create(SDL::Window* window,
                                                 int index,
                                                 SDL::Rendering::Flags flag,
                                                 Uint8 r,
                                                 Uint8 g,
                                                 Uint8 b,
                                                 Uint8 a)
{
    return SDL::Rendering::Create(window, index, static_cast<Uint32>(flag), r, g, b, a);
}

SDL::Rendering::Renderer* SDL::Rendering::Create(SDL::Window* window,
                                                 int index,
                                                 Uint32 flags,
                                                 Uint8 r,
                                                 Uint8 g,
                                                 Uint8 b,
                                                 Uint8 a)
{
    SDL::Rendering::Renderer* renderer {SDL_CreateRenderer(window, index, flags)};
    
    if (renderer == nullptr)
    {
        throw fmt::format("Renderer could not be created for the '{:s}' Window:\n\n{:s}\n", SDL::GetWindowTitle(window), SDL_GetError());
    }
    else
    {
        SDL::Rendering::SetDrawColor(renderer, r, g, b, a);
        std::cout << fmt::format("Renderer created for the '{:s}' Window\n", SDL::GetWindowTitle(window));
    }

    return renderer;
}

void SDL::Rendering::Destroy(SDL::Rendering::Renderer* renderer)
{
    std::cout << "Destroyed Renderer\n";
    SDL_DestroyRenderer(renderer);
}

bool SDL::Rendering::SetDrawColor(SDL::Rendering::Renderer* renderer,
                                  Uint8 r,
                                  Uint8 g,
                                  Uint8 b,
                                  Uint8 a)
{
    std::cout << fmt::format("Renderer set with the following RBG Values for Drawing Operations: (Red: {:d} | Green {:d} | Blue {:d} | Alpha {:d})\n", r, g, b, a);
    return SDL_SetRenderDrawColor(renderer, r, g, b, a) >= 0;
}

void SDL::Rendering::Clear(SDL::Rendering::Renderer* renderer)
{
    if (SDL_RenderClear(renderer) < 0)
    {
        throw fmt::format("Could not clear the Renderer: {:s}", SDL_GetError());
    }
    else
    {
        std::cout << "Cleared the Renderer\n";
    }
}

void SDL::Rendering::Copy(SDL::Rendering::Renderer* renderer,
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
        std::cout << "Copied from the texture to the renderer\n";
    }
}

void SDL::Rendering::Present(SDL::Rendering::Renderer* renderer)
{
    SDL_RenderPresent(renderer);
}

Uint32 operator|(SDL::Rendering::Flags first_flag,
                 SDL::Rendering::Flags second_flag)
{
    return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
