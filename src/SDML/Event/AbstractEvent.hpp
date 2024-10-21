#ifndef ABSTRACT_EVENT_H
#define ABSTRACT_EVENT_H

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>


namespace SDML
{
    namespace Event
    {
        class AbstractEvent
        {
        private:

            std::chrono::time_point<std::chrono::system_clock> timestamp;

        public:

            AbstractEvent(const SDL_Event& event,
                          const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            virtual ~AbstractEvent() = 0;

            virtual std::string to_string() const = 0;

            std::chrono::time_point<std::chrono::system_clock> GetTimeStamp() const;
        };
    }
}


#endif
