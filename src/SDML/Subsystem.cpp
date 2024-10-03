#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Subsystem.hpp"

void SDML::Subsystem::Initialize(Uint32 subsystems)
{
	if(SDL_Init(subsystems) < 0)
	{
		constexpr std::array<std::pair<std::string_view, InitFlag>, 7> subsystems {{{"Timer", 			InitFlag::TIMER},
																				    {"Audio", 			InitFlag::AUDIO},
																				    {"Video", 			InitFlag::VIDEO},
																				    {"Joystick", 		InitFlag::JOYSTICK},
																				    {"Haptic", 			InitFlag::HAPTIC},
																				    {"Game Controller", InitFlag::GAMECONTROLLER},
																				    {"Events", 			InitFlag::EVENTS}}};

		std::string err_msg {"Could not initialize SDL Subsystems: {:s}\n", SDL_GetError()};
		for(std::pair<std::string_view, InitFlag> subsystem : subsystems) {
			err_msg += fmt::format("{:s}: {:s}\n", subsystem.first, IsInitialized(subsystem.second) ? "On" : "Off");
		}

		throw std::runtime_error(err_msg);
	}

	if(IsInitialized(InitFlag::VIDEO))
	{

		std::size_t num_video_drivers {static_cast<std::size_t>(SDL_GetNumVideoDrivers())};

		if(num_video_drivers < 1) {
			throw std::runtime_error(fmt::format("Could not detect any Video Drivers: {:s}", SDL_GetError()));
		}

		std::vector<std::string> video_drivers(num_video_drivers);

		for (std::size_t video_driver_index = 0; video_driver_index < num_video_drivers; video_driver_index++) {
			video_drivers[video_driver_index] = std::string {SDL_GetVideoDriver(static_cast<int>(video_driver_index))};
		}

		using video_init_setting = std::pair<std::string, Misc::allowed_value_types>;
		std::vector<video_init_setting> video_init_settings {};
		video_init_settings.push_back(video_init_setting{"Available Video Drivers", video_drivers});
		video_init_settings.push_back(video_init_setting{   "Current Video Driver", SDL_GetCurrentVideoDriver()});

		std::cout << Misc::FormatKeyValuePairsForPrinting(video_init_settings, "SDML Video Subsystem Initialized").first << std::endl;

		if(SDL_GetNumRenderDrivers() < 1){
			std::cerr << "Warning: Could not find any Render drivers!" << std::endl;
		}
	}
}


void SDML::Subsystem::Initialize(InitFlag subsystem){ Initialize(std::to_underlying(subsystem)); }


bool SDML::Subsystem::IsInitialized(Uint32 subsystems) { return subsystems == (subsystems & SDL_WasInit(subsystems)); }


bool SDML::Subsystem::IsInitialized(InitFlag subsystem) { return IsInitialized(std::to_underlying(subsystem)); }


void SDML::Subsystem::Quit() { SDL_Quit(); }


Uint32 operator|(const SDML::Subsystem::InitFlag& first_flag,
				 const SDML::Subsystem::InitFlag& second_flag)
{ return std::to_underlying(first_flag) | std::to_underlying(second_flag); }


Uint32 operator|(Uint32 first_flag,
				 const SDML::Subsystem::InitFlag& second_flag)
{ return first_flag | std::to_underlying(second_flag); }


Uint32 operator|(const SDML::Subsystem::InitFlag& first_flag,
				 Uint32 second_flag)
{ return std::to_underlying(first_flag) | second_flag; }

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
