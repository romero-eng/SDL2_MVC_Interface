#ifndef TEXT_INPUT_EVENT_H
#define TEXT_INPUT_EVENT_H

// Custom Code from this project
#include "../../Logging/Logfile.hpp"
#include "../../Logging/PrettyPrint.hpp"
#include "../Video/Window.hpp"
#include "Event.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <string>

namespace SDML
{
    namespace Events
    {
        class TextInputEvent: public Event
        {
        private:

            Video::Window window;
            std::string text;

        public:

            TextInputEvent(const SDL_Event& event);

            std::string to_string() const override;

        };
    }
}

#endif
