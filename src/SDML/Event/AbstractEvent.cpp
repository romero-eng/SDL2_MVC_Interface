#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Event.hpp"


SDML::Event::AbstractEvent::AbstractEvent(const SDL_Event& event,
                          				  const std::chrono::time_point<std::chrono::system_clock>& init_time_point): timestamp{init_time_point + std::chrono::duration<int, std::milli>(event.common.timestamp)} {}


SDML::Event::AbstractEvent::~AbstractEvent() {}


std::chrono::time_point<std::chrono::system_clock> SDML::Event::AbstractEvent::GetTimeStamp() const { return this->timestamp; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
