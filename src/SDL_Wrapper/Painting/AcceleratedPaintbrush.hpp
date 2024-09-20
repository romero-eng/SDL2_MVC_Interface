#ifndef RENDER_WRAPPER_H
#define RENDER_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Custom wrapper code for SDL2 API
#include "Canvas.hpp"
#include "AcceleratedPicture.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations
#include <utility> // Needed for retrieving underlying type of scoped enumerations


namespace SDL
{
    namespace Painting
    {
        enum class AcceleratedPaintbrushFlags : std::uint32_t
        {
            SOFTWARE      = SDL_RENDERER_SOFTWARE,
            ACCELERATED   = SDL_RENDERER_ACCELERATED,
            PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,
            TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE                
        };

        class AcceleratedPicture; // Forward Declaration of AcceleratedPicture Class to resolve circular include

        class AcceleratedPaintbrush
        {
        private:

            SDL_Renderer* picture_renderer;

            void Copy(AcceleratedPicture& picture,
                      const Rect* srcrect,
                      const Rect* dstrect);

        public:

            AcceleratedPaintbrush(Canvas& canvas,
                                  int index,
                                  AcceleratedPaintbrushFlags flag,
                                  Uint8 r,
                                  Uint8 g,
                                  Uint8 b,
                                  Uint8 a);

            AcceleratedPaintbrush(Canvas& canvas,
                                  int index,
                                  Uint32 flags,
                                  Uint8 r,
                                  Uint8 g,
                                  Uint8 b,
                                  Uint8 a);

            AcceleratedPaintbrush(const AcceleratedPaintbrush& paintbrush) = delete;  // Copy Constructor

            AcceleratedPaintbrush& operator=(const AcceleratedPaintbrush& paintbrush) = delete;  // Copy Assignment

            void SetDrawColor(Uint8 r,
                              Uint8 g,
                              Uint8 b,
                              Uint8 a);

            void Clear();

            void Copy(AcceleratedPicture& picture);

            void Copy(AcceleratedPicture& picture,
                      const Rect& srcrect,
                      const Rect& dstrect);

            void Present();

            SDL_Renderer* Access_SDL_Implementation();

            ~AcceleratedPaintbrush();
        };
    }
}

Uint32 operator|(SDL::Painting::AcceleratedPaintbrushFlags first_flag,
                 SDL::Painting::AcceleratedPaintbrushFlags second_flag);

#endif
