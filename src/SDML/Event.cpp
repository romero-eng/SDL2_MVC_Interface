#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Event.hpp"


SDML::Event::AbstractEvent::AbstractEvent(const SDL_Event& event,
                          				  const std::chrono::time_point<std::chrono::system_clock>& init_time_point): timestamp{init_time_point + std::chrono::duration<int, std::milli>(event.common.timestamp)} {}


SDML::Event::AbstractEvent::~AbstractEvent() {}


std::chrono::time_point<std::chrono::system_clock> SDML::Event::AbstractEvent::GetTimeStamp() const { return this->timestamp; }


SDML::Event::GenericEvent::GenericEvent(const SDL_Event& event,
			                            const std::chrono::time_point<std::chrono::system_clock>& init_time_point): AbstractEvent{event, init_time_point},
																												    type_integer{event.type} {};


std::string SDML::Event::GenericEvent::to_string() const
{
	Misc::Printables event_description {"Generic Event"};
	event_description.add_printable("Type", fmt::format("{:#x}", this->GetTypeInteger()));
	event_description.add_printable("Timestamp", Misc::time_to_string(this->GetTimeStamp()));

	return event_description.print();
}


uint32_t SDML::Event::GenericEvent::GetTypeInteger() const { return this->type_integer; }


SDML::Event::QuitEvent::QuitEvent(const SDL_Event& event,
			                      const std::chrono::time_point<std::chrono::system_clock>& init_time_point): AbstractEvent{event, init_time_point} {};


std::string SDML::Event::QuitEvent::to_string() const
{
	Misc::Printables event_description {"Quit Event"};
	event_description.add_printable("Timestamp", Misc::time_to_string(this->GetTimeStamp()));

	return event_description.print();
}


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::GenericEvent& event)
{ return output << event.to_string() << std::endl; }


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::QuitEvent& event)
{ return output << event.to_string() << std::endl; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
