#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "KeyboardEvent.hpp"


SDML::Event::KeyboardEvent::KeyboardEvent(const SDL_Event& event,
                                          const std::chrono::time_point<std::chrono::system_clock> init_time_point): Event(event, init_time_point)
{ MainLogFile.Write(this->to_string()); }


std::string SDML::Event::KeyboardEvent::to_string() const
{
    return "Unfinished Keyboard Event\n";
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
