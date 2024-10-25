#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "EventMisc.hpp"


std::optional<std::unique_ptr<SDML::Events::Event>> SDML::Events::PollEvent(const std::chrono::time_point<std::chrono::system_clock>& init_time_point)
{
	SDL_Event sdl_event;
    std::optional<std::unique_ptr<SDML::Events::Event>> event;

	if(SDL_PollEvent(&sdl_event)){
    	switch(sdl_event.type) {
			case SDL_MOUSEMOTION:
				event = std::make_unique<SDML::Events::MouseMotionEvent>(sdl_event, init_time_point);
				break;
			case SDL_MOUSEBUTTONDOWN:
				event = std::make_unique<SDML::Events::MouseButtonEvent>(sdl_event, init_time_point);
				break;
			case SDL_MOUSEBUTTONUP:
				event = std::make_unique<SDML::Events::MouseButtonEvent>(sdl_event, init_time_point);
				break;
			case SDL_MOUSEWHEEL:
				event = std::make_unique<SDML::Events::MouseWheelEvent>(sdl_event, init_time_point);
				break;
			case SDL_KEYDOWN:
				event = std::make_unique<SDML::Events::KeyboardEvent>(sdl_event, init_time_point);
				break;
			case SDL_KEYUP:
				event = std::make_unique<SDML::Events::KeyboardEvent>(sdl_event, init_time_point);
				break;
			case SDL_TEXTINPUT:
				event = std::make_unique<SDML::Events::TextInputEvent>(sdl_event, init_time_point);
				break;
			case SDL_WINDOWEVENT:
				event = std::make_unique<SDML::Events::WindowEvent>(sdl_event, init_time_point);
				break;
			case SDL_QUIT:
				event = std::make_unique<SDML::Events::QuitEvent>(sdl_event, init_time_point);
				break;
			default:
				event = std::make_unique<SDML::Events::GenericEvent>(sdl_event, init_time_point);
				break;
		}
	} else {
		event = std::nullopt;
	}

    return event;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
