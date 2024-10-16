#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

// Custom Code from this project
#include "../Misc/PrettyPrint.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <iostream>
#include <utility>
#include <array>
#include <vector>
#include <string>
#include <string_view>
#include <chrono>

namespace SDML
{
	namespace Image
	{
		enum class InitFlag: uint32_t
		{
			JPG  = IMG_INIT_JPG,
			PNG  = IMG_INIT_PNG,
			TIF  = IMG_INIT_TIF,
			WEBP = IMG_INIT_WEBP,
			JXL  = IMG_INIT_JXL,
			AVIF = IMG_INIT_AVIF
		};

		void Initialize(uint32_t subsystems);

		void Initialize(InitFlag subsystem);

		bool IsInitialized(uint32_t subsystems);

		bool IsInitialized(InitFlag subsystem);

		void Quit();
	}

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

		std::chrono::time_point<std::chrono::system_clock> Initialize(uint32_t subsystems);

		std::chrono::time_point<std::chrono::system_clock> Initialize(InitFlag subsystem);

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

uint32_t operator|(const SDML::Image::InitFlag& first_flag,
				   const SDML::Image::InitFlag& second_flag);

uint32_t operator|(uint32_t first_flag,
				   const SDML::Image::InitFlag& second_flag);

uint32_t operator|(const SDML::Image::InitFlag& first_flag,
				   uint32_t second_flag);


#endif
