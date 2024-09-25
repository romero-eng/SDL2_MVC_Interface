#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

// SDL2 Library
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <map>
#include <string>
#include <bitset>

namespace SDML
{
	namespace Subsystems
	{
        /* NOTE: It would be convenient in the future to implement subsystem_bit_per_name
                  with a LinkedHashMap<Key, Value> type instead of just a Map<Key, Value>.*/
        extern std::map<const std::string, const std::size_t> subsystem_bit_per_name;

		void Initialize(bool init_video=false,
						bool init_events=false,
						bool init_timer=false,
						bool init_audio=false,
						bool init_joystick=false,
						bool init_haptic=false,
						bool init_gamecontroller=false);

		std::string QueryInitializations();

		void Quit();
	}
}


#endif
