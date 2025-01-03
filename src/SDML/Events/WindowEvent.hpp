#ifndef WINDOW_EVENT_H
#define WINDOW_EVENT_H

// Custom Code from this project
#include "../../Logging/PrettyPrint.hpp"
#include "../../Logging/Logfile.hpp"
#include "../Video/Window.hpp"
#include "Event.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

namespace SDML
{
    namespace Events
    {
        class WindowEvent: public Event
        {
        public:

            enum class Description
            {
                NONE,
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

            WindowEvent(const SDL_Event& event);

            Description GetDescription() const;

            Video::Window GetWindow() const;

            std::string to_string() const override;
        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Events::WindowEvent& event);

#endif
