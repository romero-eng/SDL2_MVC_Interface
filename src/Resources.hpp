#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_Wrapper/Surface.hpp"

namespace Resources
{

struct Surfaces
{
    SDL::Surface* helloWorld;
};

Surfaces LoadResources(void);

void FreeResources(Surfaces surface_resources);

}

#endif
