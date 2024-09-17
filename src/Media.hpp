#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_Wrapper/Canvases/CPU_Image.hpp"
#include "SDL_Wrapper/Image.hpp"
#include "SDL_Wrapper/Canvases/GPU_Paintbrush.hpp"

namespace Media
{

struct Resources
{
    SDL::CPU_Images::CPU_Image* helloWorld;
    SDL::GPU_Images::GPU_Image* GPU_PaintingPNG;
};

Resources LoadResources(SDL::GPU_Painting::GPU_Paintbrush* renderer);

void FreeResources(Resources surface_resources);

}

#endif
