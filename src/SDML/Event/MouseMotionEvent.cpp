#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "MouseMotionEvent.hpp"


SDML::Event::MouseMotionEvent::MouseMotionEvent(const SDL_Event& event,
	        			                        const std::chrono::time_point<std::chrono::system_clock>& init_time_point): Event(event, init_time_point),
                                                                                                                            window{Video::FindWindow(event.motion.windowID)},
                                                                                                                            position{event.motion.x, event.motion.y},
                                                                                                                            velocity{event.motion.xrel, event.motion.yrel},
                                                                                                                            state{event.motion.state},
                                                                                                                            ID{event.motion.which}
{ MainLogFile.Write(this->to_string()); }


std::string SDML::Event::MouseMotionEvent::to_string() const
{
    const auto& [X, Y] = this->position;
    const auto& [dX_dt, dY_dt] = this->velocity;

    Logging::Printables event_description {fmt::format("{:s}: Motion for Mouse #{:d} in '{:s}' Window",
                                                          Logging::time_to_string(this->GetTimeStamp()),
                                                          this->ID,
                                                          this->window.GetTitle())};
    event_description.add_printable("Position", fmt::format("[X: {:d}, Y: {:d}]", X, Y));
    event_description.add_printable("Velocity", fmt::format("[dX_dt: {:d}, dY_dt: {:d}]", dX_dt, dY_dt));
    event_description.add_printable("Left Button Held", this->state.test(0));
    event_description.add_printable("Right Button Held", this->state.test(2));
    event_description.add_printable("Middle Button Held", this->state.test(1));

	return fmt::format("{:s}\n", event_description.print());
}


std::ostream& operator<<(std::ostream& output,
						 const SDML::Event::MouseMotionEvent& event)
{ return output << event.to_string() << std::endl; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
