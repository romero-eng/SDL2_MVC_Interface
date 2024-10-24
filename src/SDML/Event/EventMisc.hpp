#ifndef EVENT_MISC_H
#define EVENT_MISC_H

// Custom Code from this project
#include "Event.hpp"
#include "GenericEvent.hpp"
#include "KeyboardEvent.hpp"
#include "MouseButtonEvent.hpp"
#include "MouseMotionEvent.hpp"
#include "MouseWheelEvent.hpp"
#include "QuitEvent.hpp"
#include "WindowEvent.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

namespace SDML
{
    namespace Events
    {
        std::unique_ptr<Event> SDL_to_SDML(const SDL_Event& sdl_event,
                                           const std::chrono::time_point<std::chrono::system_clock>& init_time_point);
    }
}


#endif
