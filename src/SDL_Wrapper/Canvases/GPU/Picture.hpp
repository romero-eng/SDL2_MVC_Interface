#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace GPU { namespace Pictures { using Picture = SDL_Texture; } } }
#include "Paintbrush.hpp"
#include "../CPU/Picture.hpp"


namespace SDL
{
    namespace GPU
    {
        namespace Pictures
        {
            Picture* CreateFromSurface(GPU::Painting::Paintbrush* renderer,
                                       CPU::Pictures::Picture* surfaceToConvert);

            Picture* LoadFromFile(fs::path&& bitmap_path,
                                 SDL::GPU::Painting::Paintbrush* render);

            Picture* LoadFromFile(fs::path& bitmap_path,
                                 SDL::GPU::Painting::Paintbrush* render);

            void Destroy(Picture* texture);
        }
    }
}

#endif
