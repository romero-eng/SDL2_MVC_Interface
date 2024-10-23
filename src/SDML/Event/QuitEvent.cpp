#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "QuitEvent.hpp"


SDML::Event::QuitEvent::QuitEvent(const SDL_Event& event,
			                      const std::chrono::time_point<std::chrono::system_clock>& init_time_point): Event{event, init_time_point}
{ MainLogFile.Write(this->to_string()); }


std::string SDML::Event::QuitEvent::to_string() const { return fmt::format("{:s}: Quit",  Logging::time_to_string(this->GetTimeStamp())); }


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::QuitEvent& event)
{ return output << event.to_string() << std::endl; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif