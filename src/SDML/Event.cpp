#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Event.hpp"


GenericEvent::GenericEvent(const SDL_CommonEvent& event,
			               const std::chrono::time_point<std::chrono::system_clock> init_time_point): type_integer{event.type},
				 																		        	  timestamp {init_time_point + std::chrono::duration<int, std::milli>(event.timestamp)} {};

uint32_t GenericEvent::GetTypeInteger() const { return this->type_integer; }

std::chrono::time_point<std::chrono::system_clock> GenericEvent::GetTimeStamp() const { return this->timestamp; }



QuitEvent::QuitEvent(const SDL_QuitEvent& event,
			         const std::chrono::time_point<std::chrono::system_clock> init_time_point): timestamp{init_time_point + std::chrono::duration<int, std::milli>(event.timestamp)} {};

std::chrono::time_point<std::chrono::system_clock> QuitEvent::GetTimeStamp() const { return this->timestamp; }


std::ostream& operator<<(std::ostream& output,
						 const GenericEvent& event)
{
	Misc::Printables event_description {"Generic Event"};
	event_description.add_printable("Type", fmt::format("{:#x}", event.GetTypeInteger()));
	event_description.add_printable("Timestamp", Misc::time_to_string(event.GetTimeStamp()));

	return output << event_description.print() << std::endl;
}


std::ostream& operator<<(std::ostream& output,
						 const QuitEvent& event)
{
	Misc::Printables event_description {"Quit Event"};
	event_description.add_printable("Timestamp", Misc::time_to_string(event.GetTimeStamp()));

	return output << event_description.print() << std::endl;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif