#ifndef MAIN_WRAPPER_h
#define MAIN_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations
#include <utility> // Needed for retrieving underlying type of scoped enumerations

namespace SDL
{
    enum class SubsystemInitFlags : std::uint32_t
    {
        TIMER          = SDL_INIT_TIMER,
        AUDIO          = SDL_INIT_AUDIO,
        VIDEO          = SDL_INIT_VIDEO,
        JOYSTICK       = SDL_INIT_JOYSTICK,
        HAPTIC         = SDL_INIT_HAPTIC,
        GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
        EVENTS         = SDL_INIT_EVENTS,
        EVERYTHING     = SDL_INIT_EVERYTHING,
        NOPARACHUTE    = SDL_INIT_NOPARACHUTE
    };

    enum class Hints: char32_t
    {
        RENDER_SCALE_QUALITY = *SDL_HINT_RENDER_SCALE_QUALITY
    };

    void Init(SubsystemInitFlags flag);

    void Init(Uint32 flags);

    void Quit(void);

    void SetHint(const Hints& hint_name, const char* value, const char* failure_msg);

}

Uint32 operator|(SDL::SubsystemInitFlags first_flag,
                 SDL::SubsystemInitFlags second_flag);

#endif
