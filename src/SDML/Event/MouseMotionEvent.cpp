#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "MouseMotionEvent.hpp"


SDML::Event::MouseMotionEvent::MouseMotionEvent(const SDL_Event& event,
	        			                        const std::chrono::time_point<std::chrono::system_clock>& init_time_point): AbstractEvent(event, init_time_point) {}


std::string SDML::Event::MouseMotionEvent::to_string() const
{
	return "Unfinished Mouse Motion Event";
}


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::MouseMotionEvent& event)
{ return output << event.to_string() << std::endl; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
