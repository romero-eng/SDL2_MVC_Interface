#ifndef MOUSE_BUTTON_EVENT_H
#define MOUSE_BUTTON_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "../../Logging/Logfile.hpp"
#include "../Video/Window.hpp"
#include "Event.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <array>
#include <chrono>

namespace SDML
{
    namespace Event
    {
        class MouseButtonEvent: public Event
        {
        private:

            Video::Window window;
            std::array<int, 2> position;
            uint32_t ID;

        public:

            MouseButtonEvent(const SDL_Event& event,
                             const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;

        };
    }
}

#endif
