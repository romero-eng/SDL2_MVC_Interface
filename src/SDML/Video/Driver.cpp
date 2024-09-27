#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Driver.hpp"

std::size_t SDML::Video::Drivers::GetNumDrivers()
{
	std::size_t num_video_drivers {static_cast<std::size_t>(SDL_GetNumVideoDrivers())};

	if(num_video_drivers < 1) { throw std::string("Could not detect any Video Drivers: {:s}", SDL_GetError()); }

	return num_video_drivers;
}


std::string SDML::Video::Drivers::GetCurrentDriverName() { return std::string {SDL_GetCurrentVideoDriver()}; }


std::vector<std::string> SDML::Video::Drivers::GetDriverNames()
{
	{
		std::size_t num_video_drivers {GetNumDrivers()};

		std::vector<std::string> video_drivers(num_video_drivers);

		for (std::size_t video_driver_index = 0; video_driver_index < num_video_drivers; video_driver_index++)
		{
			video_drivers[video_driver_index] = std::string {SDL_GetVideoDriver(static_cast<int>(video_driver_index))};
		}

		return video_drivers;
	}
}


std::ostream& operator<<(std::ostream& output_stream, std::vector<std::string> strings_to_concatenate)
{
	if(strings_to_concatenate.size() > 1)
	{
		output_stream << "[";
		for (std::size_t string_index = 0; string_index < strings_to_concatenate.size(); string_index++)
		{
			output_stream << strings_to_concatenate[string_index];
			if(string_index < strings_to_concatenate.size() - 1)
			{
				output_stream << ", ";
			}
		}
		output_stream << "]";
	}
	else
	{
		output_stream << "[" + strings_to_concatenate[0] + "]";
	}

	return output_stream;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
