#ifndef ABSTRACT_EVENT_H
#define ABSTRACT_EVENT_H

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>
#include <memory>


namespace SDML
{
    namespace Event
    {
        class Event
        {
        private:

            std::chrono::time_point<std::chrono::system_clock> timestamp;

        public:

            Event(const SDL_Event& event,
                          const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            virtual ~Event() = 0;

            virtual std::string to_string() const = 0;

            std::chrono::time_point<std::chrono::system_clock> GetTimeStamp() const;
        };
    }
}


#endif
