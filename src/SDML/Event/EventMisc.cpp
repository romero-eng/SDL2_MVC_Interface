#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "EventMisc.hpp"


std::unique_ptr<SDML::Events::Event> SDML::Events::SDL_to_SDML(const SDL_Event& sdl_event,
                                                               const std::chrono::time_point<std::chrono::system_clock>& init_time_point)
{
    std::unique_ptr<SDML::Events::Event> current_event;

    switch(sdl_event.type) {
		case SDL_MOUSEMOTION:
			current_event = std::make_unique<SDML::Events::MouseMotionEvent>(sdl_event, init_time_point);
			break;
		case SDL_MOUSEBUTTONDOWN:
			current_event = std::make_unique<SDML::Events::MouseButtonEvent>(sdl_event, init_time_point);
			break;
		case SDL_MOUSEBUTTONUP:
			current_event = std::make_unique<SDML::Events::MouseButtonEvent>(sdl_event, init_time_point);
			break;
		case SDL_MOUSEWHEEL:
			current_event = std::make_unique<SDML::Events::MouseWheelEvent>(sdl_event, init_time_point);
			break;
		case SDL_KEYDOWN:
			current_event = std::make_unique<SDML::Events::KeyboardEvent>(sdl_event, init_time_point);
			break;
		case SDL_KEYUP:
			current_event = std::make_unique<SDML::Events::KeyboardEvent>(sdl_event, init_time_point);
			break;
		case SDL_WINDOWEVENT:
			current_event = std::make_unique<SDML::Events::WindowEvent>(sdl_event, init_time_point);
			break;
		case SDL_QUIT:
			current_event = std::make_unique<SDML::Events::QuitEvent>(sdl_event, init_time_point);
			break;
		default:
			current_event = std::make_unique<SDML::Events::GenericEvent>(sdl_event, init_time_point);
			break;
	}

    return current_event;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
