#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

// Custom Code from this project
#include "../Misc/PrettyPrint.hpp"

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
#include <stdexcept>

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

		void Initialize(uint32_t subsystems);

		void Initialize(InitFlag subsystem);

		bool IsInitialized(uint32_t subsystems);

		bool IsInitialized(InitFlag subsystem);

		void Quit();
	}
}

uint32_t operator|(const SDML::Subsystem::InitFlag& first_flag,
				 const SDML::Subsystem::InitFlag& second_flag);

uint32_t operator|(uint32_t first_flag,
				 const SDML::Subsystem::InitFlag& second_flag);

uint32_t operator|(const SDML::Subsystem::InitFlag& first_flag,
				 uint32_t second_flag);

#endif
