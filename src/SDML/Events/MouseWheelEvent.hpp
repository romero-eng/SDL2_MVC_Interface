#ifndef MOUSE_WHEEL_EVENT_H
#define MOUSE_WHEEL_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "../../Logging/Logfile.hpp"
#include "../Video/Window.hpp"
#include "Event.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <array>
#include <chrono>

namespace SDML
{
    namespace Events
    {
        class MouseWheelEvent: public Event
        {
        private:

            Video::Window window;
            std::array<int, 2> position;
            std::array<float, 2> scroll;
            bool flipped;
            uint32_t ID;

        public:

            MouseWheelEvent(const SDL_Event& event);

            std::string to_string() const override;
        };
    }
}

#endif
