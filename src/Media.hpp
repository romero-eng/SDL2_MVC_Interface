#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_Wrapper/Canvases/CPU/Picture.hpp"
#include "SDL_Wrapper/Image.hpp"
#include "SDL_Wrapper/Canvases/GPU/Paintbrush.hpp"

namespace Media
{

struct Resources
{
    SDL::CPU::Pictures::Picture* helloWorld;
    SDL::GPU::Pictures::Picture* renderingPNG;
};

Resources LoadResources(SDL::GPU::Painting::Paintbrush* renderer);

void FreeResources(Resources surface_resources);

}

#endif
