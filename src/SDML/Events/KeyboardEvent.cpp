#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "KeyboardEvent.hpp"


SDML::Events::KeyboardEvent::KeyboardEvent(const SDL_Event& event,
                                           const std::chrono::time_point<std::chrono::system_clock> init_time_point): Event(event, init_time_point, false),
                                                                                                                      window{Video::FindWindow(event.key.windowID)},
                                                                                                                      pressed{event.key.state == SDL_PRESSED},
                                                                                                                      repeat{event.key.repeat}
{

    std::array<std::string, 2> codes {fmt::format("Scancode: {:#x}", event.key.keysym.scancode),
                                      fmt::format(" Unicode: {:#x}", event.key.keysym.sym)};

    MainLogFile.Write(this->to_string());
    std::cout << fmt::format("\n{:s}\n", fmt::join(codes, "\n")) << std::endl;
}


std::string SDML::Events::KeyboardEvent::to_string() const
{
    Logging::Printables event_description {fmt::format("Unfinished Key {:s} Event in '{:s}' Window",
                                                       this->pressed ? "Pressed" : "Released",
                                                       this->window.GetTitle())};
    event_description.add_printable("Repeats", this->repeat);

    return fmt::format("{:s}\n", event_description.print());
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
