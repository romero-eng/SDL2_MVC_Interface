#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "MouseWheelEvent.hpp"


SDML::Events::MouseWheelEvent::MouseWheelEvent(const SDL_Event& event,
                                               const std::chrono::time_point<std::chrono::system_clock> init_time_point): Event(event, init_time_point, false),
                                                                                                                          window{Video::FindWindow(event.wheel.windowID)},
                                                                                                                          position{event.wheel.mouseX, event.wheel.mouseY},
                                                                                                                          scroll{event.wheel.preciseX, event.wheel.preciseY},
                                                                                                                          flipped{event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED},
                                                                                                                          ID{event.wheel.which}
{ MainLogFile.Write(this->to_string()); }


std::string SDML::Events::MouseWheelEvent::to_string() const
{
    const auto& [X, Y] = this->position;
    const auto& [horizontal, vertical] = this->scroll;

    Logging::Printables event_description {fmt::format("{:s}: Wheel Scroll Event for Mouse #{:d} in '{:s}' Window",
                                                       Logging::time_to_string(this->GetTimeStamp()),
                                                       this->ID,
                                                       this->window.GetTitle())};
    event_description.add_printable("Position", fmt::format("[X: {:d}, Y: {:d}]", X, Y));
    event_description.add_printable("Scroll", fmt::format("[Horizontal: {:f}, Vertical: {:f}]", horizontal, vertical));
    event_description.add_printable("Flipped", this->flipped);

    return fmt::format("{:s}\n", event_description.print());
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
