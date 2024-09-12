#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL_Wrapper/Surface.hpp"

namespace Media
{

struct Resources
{
    SDL::Surface* helloWorld;
};

Resources LoadResources(void);

void FreeResources(Resources surface_resources);

}

#endif
