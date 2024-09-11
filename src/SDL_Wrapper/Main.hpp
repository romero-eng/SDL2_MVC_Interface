#ifndef MAIN_WRAPPER_h
#define MAIN_WRAPPER_h

#include "Surface.hpp"
#include <SDL2/SDL.h>

namespace SDL
{

const Uint32 INIT_VIDEO{SDL_INIT_VIDEO};
const Uint32 WINDOWPOS_UNDEFINED{SDL_WINDOWPOS_UNDEFINED};

const int WINDOW_SHOWN{SDL_WINDOW_SHOWN};

void Init(Uint32 flags);

void Quit(void);

}

#endif
