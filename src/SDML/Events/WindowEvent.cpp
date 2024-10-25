#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "WindowEvent.hpp"


SDML::Events::WindowEvent::Description SDML::Events::WindowEvent::SDL_to_SDML(SDL_Event event)
{
	Description description;
	switch(event.window.event) {
		case SDL_WINDOWEVENT_NONE:
			description = Description::NONE;
			break;
		case SDL_WINDOWEVENT_SHOWN:
			description = Description::SHOWN;
			break;
    	case SDL_WINDOWEVENT_HIDDEN:
			description = Description::HIDDEN;
			break;
    	case SDL_WINDOWEVENT_EXPOSED:
			description = Description::EXPOSED;
			break;
	    case SDL_WINDOWEVENT_MOVED:
			description = Description::MOVED;
			break;
    	case SDL_WINDOWEVENT_RESIZED:
			description = Description::RESIZED;
			break;
	    case SDL_WINDOWEVENT_SIZE_CHANGED:
			description = Description::SIZE_CHANGED;
			break;
    	case SDL_WINDOWEVENT_MINIMIZED:
			description = Description::MINIMIZED;
			break;
	    case SDL_WINDOWEVENT_MAXIMIZED:
			description = Description::MAXIMIZED;
			break;
    	case SDL_WINDOWEVENT_RESTORED:
			description = Description::RESTORED;
			break;
	    case SDL_WINDOWEVENT_ENTER:
			description = Description::ENTER;
			break;
    	case SDL_WINDOWEVENT_LEAVE:
			description = Description::LEAVE;
			break;
	    case SDL_WINDOWEVENT_FOCUS_GAINED:
			description = Description::FOCUS_GAINED;
			break;
    	case SDL_WINDOWEVENT_FOCUS_LOST:
			description = Description::FOCUS_LOST;
			break;
	    case SDL_WINDOWEVENT_CLOSE:
			description = Description::CLOSE;
			break;
    	case SDL_WINDOWEVENT_TAKE_FOCUS:
			description = Description::TAKE_FOCUS;
			break;
	    case SDL_WINDOWEVENT_HIT_TEST:
			description = Description::HIT_TEST;
			break;
    	case SDL_WINDOWEVENT_ICCPROF_CHANGED:
			description = Description::ICC_CHANGED;
			break;
    	case SDL_WINDOWEVENT_DISPLAY_CHANGED:
			description = Description::DISPLAY_CHANGED;
			break;
	}

	return description;
}


SDML::Events::WindowEvent::WindowEvent(const SDL_Event& event,
									   const std::chrono::time_point<std::chrono::system_clock>& init_time_point): Event{event, init_time_point, false},
									  																			   window{Video::FindWindow(event.window.windowID)},
																												   description{this->SDL_to_SDML(event)},
																												   data{event.window.data1, event.window.data2}
{ ::MainLogFile.Write(this->to_string()); }


std::string SDML::Events::WindowEvent::to_string() const
{
	std::string event_description_string;
	switch(this->description) {
		case Description::NONE:
			event_description_string = "none";
			break;
		case Description::SHOWN:
			event_description_string = "shown";
			break;
		case Description::HIDDEN:
			event_description_string = "hidden";
			break;
		case Description::EXPOSED:
			event_description_string = "exposed";
			break;
		case Description::MOVED:
			event_description_string = fmt::format("moved to [X: {:d}, Y: {:d}]", data[0], data[1]);
			break;
		case Description::RESIZED:
			event_description_string = fmt::format("resized to [W: {:d}, H: {:d}]", data[0], data[1]);
			break;
		case Description::SIZE_CHANGED:
			event_description_string = "size changed";
			break;
		case Description::MINIMIZED:
			event_description_string = "minimized";
			break;
		case Description::MAXIMIZED:
			event_description_string = "maximized";
			break;
		case Description::RESTORED:
			event_description_string = "restored";
			break;
		case Description::ENTER:
			event_description_string = "enter";
			break;
		case Description::LEAVE:
			event_description_string = "leave";
			break;
		case Description::FOCUS_GAINED:
			event_description_string = "focus gained";
			break;
		case Description::FOCUS_LOST:
			event_description_string = "focus lost";
			break;
		case Description::CLOSE:
			event_description_string = "close";
			break;
		case Description::TAKE_FOCUS:
			event_description_string = "take focus";
			break;
		case Description::HIT_TEST:
			event_description_string = "hit test";
			break;
		case Description::ICC_CHANGED:
			event_description_string = "ICC changed";
			break;
		case Description::DISPLAY_CHANGED:
			event_description_string = "display changed";
			break;
	}

	return fmt::format("{:s}: '{:s}' Window {:s}",
					   Logging::time_to_string(this->GetTimeStamp()),
					   this->window.GetTitle(),
					   event_description_string);
}


std::ostream& operator<<(std::ostream& output,
						 const SDML::Events::WindowEvent& event)
{ return output << event.to_string() << std::endl; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
