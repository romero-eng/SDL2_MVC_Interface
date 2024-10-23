#ifndef MOUSE_WHEEL_EVENT_H
#define MOUSE_WHEEL_EVENT_H

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
    namespace Event
    {
        class MouseWheelEvent: public Event
        {
        public:

            MouseWheelEvent(const SDL_Event& event,
                            const std::chrono::time_point<std::chrono::system_clock> init_time_point);

            std::string to_string() const override;
        };
    }
}

#endif
