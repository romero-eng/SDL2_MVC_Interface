#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Event.hpp"


SDML::Events::Event::Event(const SDL_Event& event,
                          				  const std::chrono::time_point<std::chrono::system_clock>& init_time_point): timestamp{init_time_point + std::chrono::duration<int, std::milli>(event.common.timestamp)} {}


SDML::Events::Event::~Event() {}


std::chrono::time_point<std::chrono::system_clock> SDML::Events::Event::GetTimeStamp() const { return this->timestamp; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
