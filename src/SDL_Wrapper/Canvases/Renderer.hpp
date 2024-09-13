#ifndef RENDER_WRAPPER_H
#define RENDER_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace Rendering { using Renderer = SDL_Renderer; } }
#include "Texture.hpp"
#include "../Window.hpp"
#include "../Surface.hpp"
#include "../Rectangle.hpp"

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations

namespace SDL
{
    namespace Rendering
    {
        enum class RendererFlags : std::uint32_t
        {
            SOFTWARE      = SDL_RENDERER_SOFTWARE,      /**< The renderer is a software fallback           */
            ACCELERATED   = SDL_RENDERER_ACCELERATED,   /**< The renderer uses hardware acceleration       */
            PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,  /**< Present is synchronized with the refresh rate */
            TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE  /**< The renderer supports rendering to texture    */                    
        };

            Renderer* CreateRenderer(Window* window,
                                     int index,
                                     RendererFlags flag,
                                     Uint8 r,
                                     Uint8 g,
                                     Uint8 b,
                                     Uint8 a);

            Renderer* CreateRenderer(Window* window,
                                     int index,
                                     Uint32 flags,
                                     Uint8 r,
                                     Uint8 g,
                                     Uint8 b,
                                     Uint8 a);

            void DestroyRenderer(Renderer* renderer);

            bool SetRenderDrawColor(Renderer* renderer,
                                    Uint8 r,
                                    Uint8 g,
                                    Uint8 b,
                                    Uint8 a);

            void RenderClear(Renderer* renderer);

            void RenderCopy(Renderer* renderer,
                            Texture* texture,
                            const Rect* srcrect,
                            const Rect* dstrect);

            void RenderPresent(Renderer* renderer);
    }
}

Uint32 operator|(SDL::Rendering::RendererFlags first_flag,
                 SDL::Rendering::RendererFlags second_flag);

#endif
