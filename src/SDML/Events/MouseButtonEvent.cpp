#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "MouseButtonEvent.hpp"


SDML::Events::MouseButtonEvent::MouseButtonEvent(const SDL_Event& event): Event(event, false),
                                                                          window{Video::FindWindow(event.button.windowID)},
                                                                          position{event.button.x, event.button.y},
                                                                          button_name{this->button_names[event.button.button - 1]},
                                                                          pressed{event.button.state == SDL_PRESSED},
                                                                          clicks{event.button.clicks},
                                                                          ID {event.button.which}
{ ::MainLogFile.Write(this->to_string()); }


std::string SDML::Events::MouseButtonEvent::to_string() const
{
    const auto& [X, Y] = this->position;

    Logging::Printables event_description {fmt::format("{:s}: {:s} Button {:s} for Mouse #{:d} in '{:s}' Window",
                                                       Logging::time_to_string(this->GetTimeStamp()),
                                                       this->button_name,
                                                       this->pressed ? "Pressed" : "Released",
                                                       this->ID,
                                                       this->window.GetTitle())};
    event_description.add_printable("Position", fmt::format("[X: {:d}, Y: {:d}]", X, Y));
    event_description.add_printable("Clicks", this->clicks);

    return fmt::format("{:s}\n", event_description.print());
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
