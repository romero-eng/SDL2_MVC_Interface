#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

// Third-party Libraries
#include <SDL2/SDL.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <iostream>
#include <utility>
#include <array>
#include <vector>
#include <string>
#include <string_view>

namespace SDML
{
	namespace Subsystem
	{
		enum class InitFlag: uint32_t
		{
			TIMER 		   = SDL_INIT_TIMER,
			AUDIO 	 	   = SDL_INIT_AUDIO,
			VIDEO 		   = SDL_INIT_VIDEO,
			JOYSTICK 	   = SDL_INIT_JOYSTICK,
			HAPTIC 		   = SDL_INIT_HAPTIC,
			GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
			EVENTS 		   = SDL_INIT_EVENTS,
			EVERYTHING     = SDL_INIT_EVERYTHING
		};

		void Initialize(Uint32 subsystems);

		void Initialize(InitFlag subsystem);

		bool IsInitialized(Uint32 subsystems);

		bool IsInitialized(InitFlag subsystem);

		void Quit();
	}
}

Uint32 operator|(const SDML::Subsystem::InitFlag& first_flag,
				 const SDML::Subsystem::InitFlag& second_flag);

Uint32 operator|(Uint32 first_flag,
				 const SDML::Subsystem::InitFlag& second_flag);

Uint32 operator|(const SDML::Subsystem::InitFlag& first_flag,
				 Uint32 second_flag);

#endif
