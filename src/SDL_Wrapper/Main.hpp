#ifndef MAIN_WRAPPER_h
#define MAIN_WRAPPER_h

#include "Surface.hpp"
#include <SDL2/SDL.h>
#include <string>

namespace SDL
{

const Uint32 INIT_VIDEO{SDL_INIT_VIDEO};
const Uint32 WINDOWPOS_UNDEFINED{SDL_WINDOWPOS_UNDEFINED};

const int WINDOW_SHOWN{SDL_WINDOW_SHOWN};

const char HINT_RENDER_SCALE_QUALITY {*SDL_HINT_RENDER_SCALE_QUALITY};

void Init(Uint32 flags);

void Quit(void);

void SetHint(const char name, const char* value, const char* failure_msg);

}

#endif
