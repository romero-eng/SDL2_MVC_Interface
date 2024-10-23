#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "MouseButtonEvent.hpp"


SDML::Event::MouseButtonEvent::MouseButtonEvent(const SDL_Event& event,
                                                const std::chrono::time_point<std::chrono::system_clock>& init_time_point): Event(event, init_time_point)
{ MainLogFile.Write(this->to_string()); }


std::string SDML::Event::MouseButtonEvent::to_string() const
{
    return fmt::format("{:s}: Unfinished Mouse Button Event", Logging::time_to_string(this->GetTimeStamp()));
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
