#ifndef HINTS_WRAPPER_h
#define HINTS_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations
#include <utility> // Needed for retrieving underlying type of scoped enumerations
#include <iostream> // Needed for outputting warnings to command shell

namespace SDL
{
    enum class Hints: char32_t
    {
        RENDER_SCALE_QUALITY = *SDL_HINT_RENDER_SCALE_QUALITY
    };

    void SetHint(const Hints& hint_name, const char* value, const char* failure_msg);
}

#endif
