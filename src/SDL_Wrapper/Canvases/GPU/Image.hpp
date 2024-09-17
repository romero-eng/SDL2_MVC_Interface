#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace GPU { namespace Images { using Image = SDL_Texture; } } }
#include "Paintbrush.hpp"
#include "../CPU/Image.hpp"


namespace SDL
{
    namespace GPU
    {
        namespace Images
        {
            Image* CreateFromSurface(GPU::Painting::Paintbrush* renderer,
                                       CPU::Images::Image* surfaceToConvert);

            Image* LoadFromFile(fs::path&& bitmap_path,
                                 SDL::GPU::Painting::Paintbrush* render);

            Image* LoadFromFile(fs::path& bitmap_path,
                                 SDL::GPU::Painting::Paintbrush* render);

            void Destroy(Image* texture);
        }
    }
}

#endif
