#ifndef RENDER_WRAPPER_H
#define RENDER_WRAPPER_H

#include "../Window.hpp"
#include "../Surface.hpp"
#include "../Rectangle.hpp"

#include <SDL2/SDL.h> // Original SDL2 API
#include <cstdint>

namespace SDL
{

using Renderer = SDL_Renderer;
using Texture = SDL_Texture;

enum class RendererFlags : std::uint32_t
{
    SOFTWARE      = SDL_RENDERER_SOFTWARE,      /**< The renderer is a software fallback           */
    ACCELERATED   = SDL_RENDERER_ACCELERATED,   /**< The renderer uses hardware acceleration       */
    PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,  /**< Present is synchronized with the refresh rate */
    TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE  /**< The renderer supports rendering to texture    */                    
};

Renderer* CreateRenderer(Window* window, int index, RendererFlags flag, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

Renderer* CreateRenderer(Window* window, int index, Uint32 flags, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void DestroyRenderer(Renderer* renderer);

bool SetRenderDrawColor(Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void RenderClear(Renderer* renderer);

void RenderCopy(Renderer* renderer,
                Texture* texture,
                const Rect* srcrect,
                const Rect* dstrect);

void RenderPresent(Renderer* renderer);

}

Uint32 operator|(SDL::RendererFlags first_flag, SDL::RendererFlags second_flag);

#endif
