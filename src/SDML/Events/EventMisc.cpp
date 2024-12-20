#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "EventMisc.hpp"


std::optional<std::unique_ptr<SDML::Events::Event>> SDML::Events::PollEvent()
{
	SDL_Event sdl_event;
    std::optional<std::unique_ptr<SDML::Events::Event>> event {std::nullopt};
	std::unique_ptr<SDML::Events::WindowEvent> window_event;

	if(SDL_PollEvent(&sdl_event)){
    	switch(sdl_event.type) {
			case SDL_MOUSEMOTION:
				event = std::make_unique<SDML::Events::MouseMotionEvent>(sdl_event);
				break;
			case SDL_MOUSEBUTTONDOWN:
				event = std::make_unique<SDML::Events::MouseButtonEvent>(sdl_event);
				break;
			case SDL_MOUSEBUTTONUP:
				event = std::make_unique<SDML::Events::MouseButtonEvent>(sdl_event);
				break;
			case SDL_MOUSEWHEEL:
				event = std::make_unique<SDML::Events::MouseWheelEvent>(sdl_event);
				break;
			case SDL_KEYDOWN:
				event = std::make_unique<SDML::Events::KeyboardEvent>(sdl_event);
				break;
			case SDL_KEYUP:
				event = std::make_unique<SDML::Events::KeyboardEvent>(sdl_event);
				break;
			case SDL_TEXTINPUT:
				event = std::make_unique<SDML::Events::TextInputEvent>(sdl_event);
				break;
			case SDL_WINDOWEVENT:
				window_event = std::make_unique<SDML::Events::WindowEvent>(sdl_event);
				switch(window_event->GetDescription()) {
					case WindowEvent::Description::CLOSE:
						window_event->GetWindow().Hide();
						break;
					default:
						event = std::move(window_event);
						break;
				}
				break;
			case SDL_QUIT:
				event = std::make_unique<SDML::Events::QuitEvent>(sdl_event);
				break;
			default:
				event = std::make_unique<SDML::Events::GenericEvent>(sdl_event);
				break;
		}
	}

    return event;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
