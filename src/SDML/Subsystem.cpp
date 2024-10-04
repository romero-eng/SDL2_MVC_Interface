#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Subsystem.hpp"

void SDML::Subsystem::Initialize(uint32_t subsystems)
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
		
		std::size_t num_render_drivers {static_cast<std::size_t>(SDL_GetNumRenderDrivers())};
		if(num_render_drivers < 1) {
			throw std::runtime_error(fmt::format("Could not detect any Render Drivers: {:s}", SDL_GetError()));
		}

		std::vector<std::string> video_drivers(num_video_drivers);

		for (std::size_t video_driver_index = 0; video_driver_index < num_video_drivers; video_driver_index++) {
			video_drivers[video_driver_index] = std::string {SDL_GetVideoDriver(static_cast<int>(video_driver_index))};
		}

		Misc::Printables video_init_msgs {"SDML Video Subsystem Initialized"};
		video_init_msgs.add_printable("Available Video Drivers", video_drivers);
		video_init_msgs.add_printable(   "Current Video Driver", SDL_GetCurrentVideoDriver());

		SDL_RendererInfo current_render_driver_info {};
		Misc::Printables printable_render_driver_info;

		for(std::size_t render_driver_index = 0; render_driver_index < num_render_drivers; render_driver_index++) {
			if(SDL_GetRenderDriverInfo(static_cast<int>(render_driver_index), &current_render_driver_info) < 0) {
				throw std::runtime_error(fmt::format("Could not retrieve information for Render Driver #{:d}: {:s}",
													 render_driver_index,
													 SDL_GetError()));
			} else {

				std::size_t num_texture_formats {static_cast<std::size_t>(current_render_driver_info.num_texture_formats)};

				printable_render_driver_info.clear();
				printable_render_driver_info.set_title(fmt::format("'{:s}' Render Driver", current_render_driver_info.name));
				for(std::size_t render_format_index = 0; render_format_index < num_texture_formats; render_format_index++){
					printable_render_driver_info.add_printable(fmt::format("Texture Format #{:d}",
																		   render_format_index + 1),
															   SDL_GetPixelFormatName(current_render_driver_info.texture_formats[0]));
				}
				printable_render_driver_info.add_printable( 	   "Maximum Texture Width", current_render_driver_info.max_texture_width);
				printable_render_driver_info.add_printable(		  "Maximum Texture Height", current_render_driver_info.max_texture_height);
				printable_render_driver_info.add_printable(  		"Is Software Fallback", SDL_RENDERER_SOFTWARE == (SDL_RENDERER_SOFTWARE & current_render_driver_info.flags));
				printable_render_driver_info.add_printable(  	   "Supports Acceleration", SDL_RENDERER_ACCELERATED == (SDL_RENDERER_ACCELERATED & current_render_driver_info.flags));
				printable_render_driver_info.add_printable(  		  	  "Supports VSync", SDL_RENDERER_PRESENTVSYNC == (SDL_RENDERER_PRESENTVSYNC & current_render_driver_info.flags));
				printable_render_driver_info.add_printable("Supports rendering to texture", SDL_RENDERER_TARGETTEXTURE == (SDL_RENDERER_TARGETTEXTURE & current_render_driver_info.flags));
				video_init_msgs.copy_into_printables(printable_render_driver_info);
			}
		}

		std::cout << video_init_msgs << "\n" << std::endl;
	}
}


void SDML::Subsystem::Initialize(InitFlag subsystem){ Initialize(std::to_underlying(subsystem)); }


bool SDML::Subsystem::IsInitialized(uint32_t subsystems) { return subsystems == (subsystems & SDL_WasInit(subsystems)); }


bool SDML::Subsystem::IsInitialized(InitFlag subsystem) { return IsInitialized(std::to_underlying(subsystem)); }


void SDML::Subsystem::Quit() { SDL_Quit(); }


uint32_t operator|(const SDML::Subsystem::InitFlag& first_flag,
				 const SDML::Subsystem::InitFlag& second_flag)
{ return std::to_underlying(first_flag) | std::to_underlying(second_flag); }


uint32_t operator|(uint32_t first_flag,
				 const SDML::Subsystem::InitFlag& second_flag)
{ return first_flag | std::to_underlying(second_flag); }


uint32_t operator|(const SDML::Subsystem::InitFlag& first_flag,
				 uint32_t second_flag)
{ return std::to_underlying(first_flag) | second_flag; }

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
