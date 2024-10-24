#ifndef QUIT_EVENT_H
#define QUIT_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "../../Logging/Logfile.hpp"
#include "Event.hpp"

// Third-Party APIs
#include <fmt/format.h>
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>

namespace SDML
{
    namespace Events
    {
        class QuitEvent: public Event
        {
        public:

        	QuitEvent(const SDL_Event& event,
	        		  const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Events::QuitEvent& event);

#endif
