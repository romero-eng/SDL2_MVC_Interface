#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { namespace Textures { using Texture = SDL_Texture; } }
#include "Renderer.hpp"
#include "CPU_Image.hpp"


namespace SDL
{
    namespace Textures
    {
        Texture* CreateFromSurface(Rendering::Renderer* renderer,
                                   CPU_Images::CPU_Image* surfaceToConvert);

        Texture* LoadFromFile(fs::path&& bitmap_path,
                             SDL::Rendering::Renderer* render);

        Texture* LoadFromFile(fs::path& bitmap_path,
                             SDL::Rendering::Renderer* render);

        void Destroy(Texture* texture);
    }
}

#endif
