#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

#include "Renderer.hpp"
#include "../Surface.hpp"

#include <SDL2/SDL.h> // Call original SDL2 API

namespace SDL
{
    using Texture = SDL_Texture;

    Texture* CreateTextureFromSurface(Renderer* renderer, Surface* surfaceToConvert);

    void DestroyTexture(Texture* texture);
}

#endif
