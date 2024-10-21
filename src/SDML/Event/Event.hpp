#ifndef EVENT_H
#define EVENT_H

// Custom Code from this project
#include "../../Misc/PrettyPrint.hpp"
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
        private:
            
            Video::Window window;
            uint8_t event;
            int32_t data1;
            int32_t data2;

            Video::Window FindWindow(const SDL_Event& event);
        
        public:

            WindowEvent(const SDL_Event& event,
                        const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;
        };


        class QuitEvent: public AbstractEvent
        {
        public:

        	QuitEvent(const SDL_Event& event,
	        		  const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;
        };


        class GenericEvent: public AbstractEvent
        {
        private:

    	    uint32_t type_integer;

        public:

        	GenericEvent(const SDL_Event& event,
	        			 const std::chrono::time_point<std::chrono::system_clock>& init_time_point);

            std::string to_string() const override;

    	    uint32_t GetTypeInteger() const;
        };

    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Event::WindowEvent& event);

std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::QuitEvent& event);

std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::GenericEvent& event);

#endif
