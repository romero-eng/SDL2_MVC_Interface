#ifndef GENERIC_EVENT_H
#define GENERIC_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "../../Logging/Logfile.hpp"
#include "Event.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>


namespace SDML
{
    namespace Events
    {
        class GenericEvent: public Event
        {
        private:

    	    uint32_t type_integer;

        public:

        	GenericEvent(const SDL_Event& event);

            std::string to_string() const override;

    	    uint32_t GetTypeInteger() const;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
						 const SDML::Events::GenericEvent& event);

#endif
