#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_Wrapper/Canvases/CPU_Image.hpp"
#include "SDL_Wrapper/Image.hpp"
#include "SDL_Wrapper/Canvases/Renderer.hpp"

namespace Media
{

struct Resources
{
    SDL::CPU_Images::CPU_Image* helloWorld;
    SDL::GPU_Images::GPU_Image* renderingPNG;
};

Resources LoadResources(SDL::Rendering::Renderer* renderer);

void FreeResources(Resources surface_resources);

}

#endif
