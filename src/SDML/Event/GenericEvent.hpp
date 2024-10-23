#ifndef GENERIC_EVENT_H
#define GENERIC_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "AbstractEvent.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>


namespace SDML
{
    namespace Event
    {
        class GenericEvent: public AbstractEvent
        {
        private:

    	    uint32_t type_integer;

        public:

        	GenericEvent(const SDL_Event& event,
	        			 const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;

    	    uint32_t GetTypeInteger() const;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::GenericEvent& event);

#endif
