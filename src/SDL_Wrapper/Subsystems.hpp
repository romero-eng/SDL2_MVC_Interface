#ifndef MAIN_WRAPPER_h
#define MAIN_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// Custom wrapper code for SDL2 API
#include "Painting/Image/FileLoading.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

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

    void Init(SubsystemInitFlags subsystem_flag);

    void Init(SubsystemInitFlags subsystem_flag,
              Painting::Image::FileTypes file_type);

    void Init(SubsystemInitFlags subsystem_flag,
              Uint32 file_types);

    void Init(Uint32 subsystem_flags);

    void Init(Uint32 subsystem_flags,
              Painting::Image::FileTypes file_type);

    void Init(Uint32 subsystem_flags,
              Uint32 file_types);

    void Quit(void);
}

Uint32 operator|(SDL::SubsystemInitFlags first_flag,
                 SDL::SubsystemInitFlags second_flag);

#endif
