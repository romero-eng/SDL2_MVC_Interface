#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL { using Texture = SDL_Texture; }
#include "Renderer.hpp"
#include "../Surface.hpp"


namespace SDL
{
    Texture* CreateTextureFromSurface(Rendering::Renderer* renderer,
                                      Surface* surfaceToConvert);

    void DestroyTexture(Texture* texture);
}

#endif
