#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "TextInputEvent.hpp"


SDML::Events::TextInputEvent::TextInputEvent(const SDL_Event& event,
                                             const std::chrono::time_point<std::chrono::system_clock>& init_time_point): Event(event, init_time_point, false),
                                                                                                                         window{Video::FindWindow(event.text.windowID)},
                                                                                                                         text{event.text.text}
{ MainLogFile.Write(this->to_string()); }


std::string SDML::Events::TextInputEvent::to_string() const
{
    return fmt::format("{:s}: '{:s}' Text inputted in '{:s}' Window\n",
                       Logging::time_to_string(this->GetTimeStamp()),
                       this->text,
                       this->window.GetTitle());
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
