#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace GPU_Images { using GPU_Image = SDL_Texture; } }
#include "GPU_Paintbrush.hpp"
#include "CPU_Image.hpp"


namespace SDL
{
    namespace GPU_Images
    {
        GPU_Image* CreateFromSurface(GPU_Painting::GPU_Paintbrush* renderer,
                                   CPU_Images::CPU_Image* surfaceToConvert);

        GPU_Image* LoadFromFile(fs::path&& bitmap_path,
                             SDL::GPU_Painting::GPU_Paintbrush* render);

        GPU_Image* LoadFromFile(fs::path& bitmap_path,
                             SDL::GPU_Painting::GPU_Paintbrush* render);

        void Destroy(GPU_Image* texture);
    }
}

#endif
