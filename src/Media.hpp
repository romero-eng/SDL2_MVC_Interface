#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_Wrapper/Surface.hpp"
#include "SDL_Wrapper/Image.hpp"
#include "SDL_Wrapper/TexturesAndRenderers.hpp"

namespace Media
{

struct Resources
{
    SDL::Surface* helloWorld;
    SDL::Texture* renderingPNG;
};

Resources LoadResources(SDL::Renderer* renderer);

void FreeResources(Resources surface_resources);

}

#endif
