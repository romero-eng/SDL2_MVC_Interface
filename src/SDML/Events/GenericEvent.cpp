#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "GenericEvent.hpp"


SDML::Events::GenericEvent::GenericEvent(const SDL_Event& event): Event{event, false},
																  type_integer{event.type}
{ Logging::MainLogFile.Write(this->to_string()); }


std::string SDML::Events::GenericEvent::to_string() const
{
	Logging::Printables event_description {fmt::format("{:s}: Generic Event", Logging::time_to_string(this->GetTimeStamp()))};
	event_description.add_printable("Type", fmt::format("{:#x}", this->GetTypeInteger()));

	return fmt::format("{:s}\n", event_description.print());
}


uint32_t SDML::Events::GenericEvent::GetTypeInteger() const { return this->type_integer; }


std::ostream& operator<<(std::ostream& output,
						 const SDML::Events::GenericEvent& event)
{ return output << event.to_string() << std::endl; }



#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
