#ifndef RENDER_WRAPPER_H
#define RENDER_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Custom wrapper code for SDL2 API
#include "Canvas.hpp"
#include "../Image/AcceleratedImage.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations
#include <utility> // Needed for retrieving underlying type of scoped enumerations


namespace SDL
{
    namespace Painting
    {
        namespace Image
        {
            class AcceleratedImage; // Forward Declaration of AcceleratedImage Class to resolve circular include
        }

        namespace Equipment
        {
            enum class AcceleratedPaintbrushFlags : std::uint32_t
            {
               SOFTWARE      = SDL_RENDERER_SOFTWARE,
                ACCELERATED   = SDL_RENDERER_ACCELERATED,
                PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,
                TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE                
            };

            class AcceleratedPaintbrush
            {
            private:

                SDL_Renderer* paintbrush_renderer;

                void PostPicture(Image::AcceleratedImage& picture,
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

                void PostPicture(Image::AcceleratedImage& picture);

                void PostPicture(Image::AcceleratedImage& picture,
                                 const Rect& srcrect,
                                 const Rect& dstrect);

                void Fill();

                void DrawRectangle(const Rect& area);

                void DrawEmptyRectangle(const Rect& area);

                void DrawLine(int x1, int y1, int x2, int y2);

                void DrawPoint(int x1, int y1);

                void ReserveDrawingArea(const Rect& area);

                void Present();

                SDL_Renderer* Access_SDL_Implementation();

                ~AcceleratedPaintbrush();
            };
        }
    }
}

Uint32 operator|(SDL::Painting::Equipment::AcceleratedPaintbrushFlags first_flag,
                 SDL::Painting::Equipment::AcceleratedPaintbrushFlags second_flag);

#endif
