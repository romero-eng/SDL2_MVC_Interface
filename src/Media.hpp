#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_Wrapper/Canvases/CPU/Image.hpp"
#include "SDL_Wrapper/Image.hpp"
#include "SDL_Wrapper/Canvases/GPU/Paintbrush.hpp"

namespace Media
{

struct Resources
{
    SDL::CPU::Images::Image* helloWorld;
    SDL::GPU::Images::Image* renderingPNG;
};

Resources LoadResources(SDL::GPU::Painting::Paintbrush* renderer);

void FreeResources(Resources surface_resources);

}

#endif
