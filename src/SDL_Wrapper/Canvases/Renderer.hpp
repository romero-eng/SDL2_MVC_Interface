#ifndef RENDER_WRAPPER_H
#define RENDER_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace Rendering { using Renderer = SDL_Renderer; } }
#include "Texture.hpp"
#include "Window.hpp"
#include "../Rectangle.hpp"

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations

namespace SDL
{
    namespace Rendering
    {
        enum class Flags : std::uint32_t
        {
            SOFTWARE      = SDL_RENDERER_SOFTWARE,      /**< The renderer is a software fallback           */
            ACCELERATED   = SDL_RENDERER_ACCELERATED,   /**< The renderer uses hardware acceleration       */
            PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,  /**< Present is synchronized with the refresh rate */
            TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE  /**< The renderer supports rendering to texture    */                    
        };

            Renderer* Create(Windowing::Window* window,
                             int index,
                             Flags flag,
                             Uint8 r,
                             Uint8 g,
                             Uint8 b,
                             Uint8 a);

            Renderer* Create(Windowing::Window* window,
                             int index,
                             Uint32 flags,
                             Uint8 r,
                             Uint8 g,
                             Uint8 b,
                             Uint8 a);

            void Destroy(Renderer* renderer);

            bool SetDrawColor(Renderer* renderer,
                              Uint8 r,
                              Uint8 g,
                              Uint8 b,
                              Uint8 a);

            void Clear(Renderer* renderer);

            void Copy(Renderer* renderer,
                      Textures::Texture* texture,
                      const Rect* srcrect,
                      const Rect* dstrect);

            void Present(Renderer* renderer);
    }
}

Uint32 operator|(SDL::Rendering::Flags first_flag,
                 SDL::Rendering::Flags second_flag);

#endif
