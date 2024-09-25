
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Subsystem.hpp"


std::map<const std::string, const std::size_t> SDML::Subsystems::subsystem_bit_per_name {{"Video", 5},
        					    	    											     {"Events", 14},
	        					    	    										     {"Timer", 0},
		        					    	    								         {"Audio", 4},
			        					    	    								     {"Joystick", 9},
				        					    	    							     {"Haptic", 12},
					        					    	    						     {"Game Controller", 13},
						        					    	    					     {"Everything", 15}};

void SDML::Subsystems::Initialize(bool init_video,
								  bool init_events,
								  bool init_timer,
								  bool init_audio,
								  bool init_joystick,
								  bool init_haptic,
								  bool init_gamecontroller)
{
	std::bitset<32> subsystem_flags {0x0};

	if(init_video		  ) { subsystem_flags.set(subsystem_bit_per_name["Video"]); }
	if(init_events		  ) { subsystem_flags.set(subsystem_bit_per_name["Events"]); }
	if(init_timer		  ) { subsystem_flags.set(subsystem_bit_per_name["Timer"]); }
	if(init_audio		  ) { subsystem_flags.set(subsystem_bit_per_name["Audio"]); }
	if(init_joystick	  ) { subsystem_flags.set(subsystem_bit_per_name["Joystick"]); }
	if(init_haptic		  ) { subsystem_flags.set(subsystem_bit_per_name["Haptic"]); }
	if(init_gamecontroller) { subsystem_flags.set(subsystem_bit_per_name["Game Controller"]); }

	if(init_video && init_events && init_timer && init_audio && init_joystick && init_haptic && init_gamecontroller)
	{
		subsystem_flags.set(subsystem_bit_per_name["Everything"]);
	}

	SDL_Init(static_cast<uint32_t>(subsystem_flags.to_ulong()));
}


std::string SDML::Subsystems::QueryInitializations()
{
	std::bitset<32> subsystem_flags {SDL_WasInit(0)};

	std::string subsystem_statuses {};
	for (const auto& [subsystem_name, subsystem_bit]: subsystem_bit_per_name)
	{
		subsystem_statuses += subsystem_name + ": " + (subsystem_flags.test(subsystem_bit) ? "On" : "Off") + "\n";
	}

	return subsystem_statuses;
}


void SDML::Subsystems::Quit() { SDL_Quit(); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
