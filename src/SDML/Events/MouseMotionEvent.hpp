#ifndef MOUSE_MOTION_EVENT_H
#define MOUSE_MOTION_EVENT_H

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
#include <bitset>

namespace SDML
{
    namespace Events
    {
        class MouseMotionEvent: public Event
        {
        private:

            Video::Window window;
            std::array<int, 2> position;
            std::array<int, 2> velocity;
            std::bitset<32> state;
            uint32_t ID;

        public:

        	MouseMotionEvent(const SDL_Event& event);

            std::string to_string() const override;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
						 const SDML::Events::MouseMotionEvent& event);

#endif
