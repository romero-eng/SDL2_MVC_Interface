#ifndef KEYBOARD_EVENT_H
#define KEYBOARD_EVENT_H

// Custom Code from this project
#include "../../Logging/Logfile.hpp"
#include "../../Logging/PrettyPrint.hpp"
#include "../Video/Window.hpp"
#include "Event.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>
#include <string>

namespace SDML
{
    namespace Events
    {
        class KeyboardEvent: public Event
        {
        public:

            enum class Modifier
            {
                NONE,
                LSHIFT,
                RSHIFT,
                LCTRL,
                RCTRL,
                LALT,
                RALT,
                LGUI,
                RGUI,
                NUM,
                CAPS,
                MODE,
                SCROLL
            };

        private:

            std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter {};

            Video::Window window;
            bool pressed;
            std::string scancode;
            std::string unicode;
            uint8_t repeat;
            Modifier mod;

            Modifier SDL_to_SDML(uint16_t sdl_mod);

        public:

            KeyboardEvent(const SDL_Event& event);

            std::string to_string() const override;
        };
    }
}

#endif
