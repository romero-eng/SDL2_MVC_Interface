#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "QuitEvent.hpp"


SDML::Events::QuitEvent::QuitEvent(const SDL_Event& event): Event{event, true}
{ ::MainLogFile.Write(this->to_string()); }


std::string SDML::Events::QuitEvent::to_string() const { return fmt::format("{:s}: Quit",  Logging::time_to_string(this->GetTimeStamp())); }


std::ostream& operator<<(std::ostream& output,
						 const SDML::Events::QuitEvent& event)
{ return output << event.to_string() << std::endl; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
