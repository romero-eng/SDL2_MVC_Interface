#ifndef RENDER_WRAPPER_H
#define RENDER_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace GPU_Painting { using GPU_Paintbrush = SDL_Renderer; } }
#include "GPU_Image.hpp"
#include "Canvas.hpp"
#include "../Rectangle.hpp"

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations

namespace SDL
{
    namespace GPU_Painting
    {
        enum class Flags : std::uint32_t
        {
            SOFTWARE      = SDL_RENDERER_SOFTWARE,      /**< The renderer is a software fallback           */
            ACCELERATED   = SDL_RENDERER_ACCELERATED,   /**< The renderer uses hardware acceleration       */
            PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,  /**< Present is synchronized with the refresh rate */
            TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE  /**< The renderer supports GPU_Painting to texture    */                    
        };

            GPU_Paintbrush* Create(Canvassing::Canvas* window,
                             int index,
                             Flags flag,
                             Uint8 r,
                             Uint8 g,
                             Uint8 b,
                             Uint8 a);

            GPU_Paintbrush* Create(Canvassing::Canvas* window,
                             int index,
                             Uint32 flags,
                             Uint8 r,
                             Uint8 g,
                             Uint8 b,
                             Uint8 a);

            void Destroy(GPU_Paintbrush* renderer);

            bool SetDrawColor(GPU_Paintbrush* renderer,
                              Uint8 r,
                              Uint8 g,
                              Uint8 b,
                              Uint8 a);

            void Clear(GPU_Paintbrush* renderer);

            void Copy(GPU_Paintbrush* renderer,
                      GPU_Images::GPU_Image* texture,
                      const Rect* srcrect,
                      const Rect* dstrect);

            void Present(GPU_Paintbrush* renderer);
    }
}

Uint32 operator|(SDL::GPU_Painting::Flags first_flag,
                 SDL::GPU_Painting::Flags second_flag);

#endif
