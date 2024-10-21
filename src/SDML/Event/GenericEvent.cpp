#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "GenericEvent.hpp"


SDML::Event::GenericEvent::GenericEvent(const SDL_Event& event,
			                            const std::chrono::time_point<std::chrono::system_clock>& init_time_point): AbstractEvent{event, init_time_point},
																												    type_integer{event.type} {}


std::string SDML::Event::GenericEvent::to_string() const
{
	Misc::Printables event_description {fmt::format("Generic Event at {:s}", Misc::time_to_string(this->GetTimeStamp()))};
	event_description.add_printable("Type", fmt::format("{:#x}", this->GetTypeInteger()));

	return event_description.print();
}


uint32_t SDML::Event::GenericEvent::GetTypeInteger() const { return this->type_integer; }


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::GenericEvent& event)
{ return output << event.to_string() << std::endl; }



#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
