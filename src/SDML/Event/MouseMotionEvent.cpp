#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "MouseMotionEvent.hpp"


SDML::Event::MouseMotionEvent::MouseMotionEvent(const SDL_Event& event,
	        			                        const std::chrono::time_point<std::chrono::system_clock>& init_time_point): AbstractEvent(event, init_time_point),
                                                                                                                            window{Video::FindWindow(event.motion.windowID)},
                                                                                                                            position{event.motion.x, event.motion.y},
                                                                                                                            velocity{event.motion.xrel, event.motion.yrel},
                                                                                                                            state{event.motion.state} {}


std::string SDML::Event::MouseMotionEvent::to_string() const
{
    const auto& [X, Y] = position;
    const auto& [dX_dt, dY_dt] = velocity;

    Misc::Printables mouse_event_description {fmt::format("{:s}: '{:s}' Window mouse motion", Misc::time_to_string(this->GetTimeStamp()), this->window.GetTitle())};
    mouse_event_description.add_printable("Position", fmt::format("[X: {:d}, Y: {:d}]", X, Y));
    mouse_event_description.add_printable("Velocity", fmt::format("[dX_dt: {:d}, dY_dt: {:d}]", dX_dt, dY_dt));
    mouse_event_description.add_printable("State", state.to_string());

	return mouse_event_description.print();
}


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::MouseMotionEvent& event)
{ return output << event.to_string() << std::endl; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
