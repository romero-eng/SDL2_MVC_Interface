#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "../Video/Window.hpp"
#include "AbstractEvent.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>

namespace SDML
{
    namespace Event
    {
        class WindowEvent: public AbstractEvent
        {
        public:

            enum class Description
            {
                SHOWN,
                HIDDEN,
                EXPOSED,
                MOVED,
                RESIZED,
                SIZE_CHANGED,
                MINIMIZED,
                MAXIMIZED,
                RESTORED,
                ENTER,
                LEAVE,
                FOCUS_GAINED,
                FOCUS_LOST,
                CLOSE,
                TAKE_FOCUS,
                HIT_TEST,
                ICC_CHANGED,
                DISPLAY_CHANGED
            };

        private:
            
            Video::Window window;
            Description description;
            std::array<int32_t, 2> data;

            Description SDL_to_SDML(SDL_Event event);
        
        public:

            WindowEvent(const SDL_Event& event,
                        const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Event::WindowEvent& event);

#endif
