#ifndef QUIT_EVENT_H
#define QUIT_EVENT_H

// Custom Code from this project
#include "../../Misc/PrettyPrint.hpp"
#include "AbstractEvent.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>

namespace SDML
{
    namespace Event
    {
        class QuitEvent: public AbstractEvent
        {
        public:

        	QuitEvent(const SDL_Event& event,
	        		  const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Event::QuitEvent& event);

#endif
