#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "MouseButtonEvent.hpp"


SDML::Event::MouseButtonEvent::MouseButtonEvent(const SDL_Event& event,
                                                const std::chrono::time_point<std::chrono::system_clock>& init_time_point): Event(event, init_time_point),
                                                                                                                            window{Video::FindWindow(event.button.windowID)},
                                                                                                                            position{event.button.x, event.button.y},
                                                                                                                            ID {event.button.which}
{ MainLogFile.Write(this->to_string()); }


std::string SDML::Event::MouseButtonEvent::to_string() const
{
    const auto& [X, Y] = this->position;

    Logging::Printables event_description {fmt::format("{:s}: Button Click for Mouse #{:d} in '{:s}' Window",
                                                       Logging::time_to_string(this->GetTimeStamp()),
                                                       this->ID,
                                                       this->window.GetTitle())};
    event_description.add_printable("Position", fmt::format("[X: {:d}, Y: {:d}]", X, Y));

    return fmt::format("{:s}\n", event_description.print());
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
