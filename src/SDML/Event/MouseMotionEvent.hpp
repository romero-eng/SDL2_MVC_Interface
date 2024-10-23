#ifndef MOUSE_MOTION_EVENT_H
#define MOUSE_MOTION_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "../Video/Window.hpp"
#include "AbstractEvent.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>
#include <bitset>

namespace SDML
{
    namespace Event
    {
        class MouseMotionEvent: public AbstractEvent
        {
        private:

            Video::Window window;
            std::array<int, 2> position;
            std::array<int, 2> velocity;
            std::bitset<32> state;
            uint32_t ID;

        public:

        	MouseMotionEvent(const SDL_Event& event,
	        			     const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::MouseMotionEvent& event);

#endif
