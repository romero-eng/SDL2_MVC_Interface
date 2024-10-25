#ifndef QUIT_EVENT_H
#define QUIT_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "../../Logging/Logfile.hpp"
#include "Event.hpp"

// Third-Party APIs
#include <fmt/format.h>
#include <SDL2/SDL.h>

namespace SDML
{
    namespace Events
    {
        class QuitEvent: public Event
        {
        public:

        	QuitEvent(const SDL_Event& event);

            std::string to_string() const override;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Events::QuitEvent& event);

#endif
