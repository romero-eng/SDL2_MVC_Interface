#ifndef EVENT_MISC_H
#define EVENT_MISC_H

// Custom Code from this project
#include "Event.hpp"
#include "GenericEvent.hpp"
#include "KeyboardEvent.hpp"
#include "TextInputEvent.hpp"
#include "MouseButtonEvent.hpp"
#include "MouseMotionEvent.hpp"
#include "MouseWheelEvent.hpp"
#include "QuitEvent.hpp"
#include "WindowEvent.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <memory>
#include <optional>

namespace SDML
{
    namespace Events
    {
        std::optional<std::unique_ptr<Event>> PollEvent();
    }
}


#endif
