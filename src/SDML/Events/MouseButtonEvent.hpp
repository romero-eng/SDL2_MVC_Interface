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
#include <string_view>

namespace SDML
{
    namespace Events
    {
        class MouseButtonEvent: public Event
        {
        private:

            static constexpr std::array<std::string_view, 3> button_names {"Left", "Middle", "Right"};

            Video::Window window;
            std::array<int, 2> position;
            std::string_view button_name;
            bool pressed;
            uint8_t clicks;
            uint32_t ID;

        public:

            MouseButtonEvent(const SDL_Event& event);

            std::string to_string() const override;

        };
    }
}

#endif
