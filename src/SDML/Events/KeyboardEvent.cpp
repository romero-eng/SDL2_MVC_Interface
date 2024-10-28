#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "KeyboardEvent.hpp"


SDML::Events::KeyboardEvent::Modifier SDML::Events::KeyboardEvent::SDL_to_SDML(uint16_t sdl_mod)
{
    Modifier mod;

    switch(sdl_mod) {
        case 0x0000:
            mod = Modifier::NONE;
            break;
        case 0x0001:
            mod = Modifier::LSHIFT;
            break;
        case 0x0002:
            mod = Modifier::RSHIFT;
            break;
        case 0x0040:
            mod = Modifier::LCTRL;
            break;
        case 0x0080:
            mod = Modifier::RCTRL;
            break;
        case 0x0100:
            mod = Modifier::LALT;
            break;
        case 0x0200:
            mod = Modifier::RALT;
            break;
        case 0x0400:
            mod = Modifier::LGUI;
            break;
        case 0x0800:
            mod = Modifier::RGUI;
            break;
        case 0x1000:
            mod = Modifier::NUM;
            break;
        case 0x2000:
            mod = Modifier::CAPS;
            break;
        case 0x4000:
            mod = Modifier::MODE;
            break;
        case 0x8000:
            mod = Modifier::SCROLL;
            break;
    }

    return mod;
}


SDML::Events::KeyboardEvent::KeyboardEvent(const SDL_Event& event): Event(event, false),
                                                                    window{Video::FindWindowByID(event.key.windowID)},
                                                                    pressed{event.key.state == SDL_PRESSED},
                                                                    scancode{SDL_GetScancodeName(event.key.keysym.scancode)},
                                                                    unicode{SDL_GetKeyName(event.key.keysym.sym)},
                                                                    repeat{event.key.repeat},
                                                                    mod{this->SDL_to_SDML(event.key.keysym.mod)}
{ Logging::MainLogFile.Write(this->to_string()); }


std::string SDML::Events::KeyboardEvent::to_string() const
{
    std::string mod_string;
    switch (this->mod) {
        case Modifier::NONE:
            mod_string = "None";
            break;
        case Modifier::LSHIFT:
            mod_string = "Left Shift";
            break;
        case Modifier::RSHIFT:
            mod_string = "Right Shift";
            break;
        case Modifier::LCTRL:
            mod_string = "Left Control";
            break;
        case Modifier::RCTRL:
            mod_string = "Right Control";
            break;
        case Modifier::LALT:
            mod_string = "Left Alternate";
            break;
        case Modifier::RALT:
            mod_string = "Right Alternate";
            break;
        case Modifier::LGUI:
            mod_string = "Left GUI";
            break;
        case Modifier::RGUI:
            mod_string = "Right GUI";
            break;
        case Modifier::NUM:
            mod_string = "Number";
            break;
        case Modifier::CAPS:
            mod_string = "CAPS";
            break;
        case Modifier::MODE:
            mod_string = "Mode";
            break;
        case Modifier::SCROLL:
            mod_string = "Scroll";
            break;
    }

    Logging::Printables event_description {fmt::format("{:s}: '{:s}' Key {:s} in '{:s}' Window",
                                                       Logging::time_to_string(this->GetTimeStamp()),
                                                       this->unicode,
                                                       this->pressed ? "Pressed" : "Released",
                                                       this->window.GetTitle())};
    event_description.add_printable("Scancode", this->scancode);
    event_description.add_printable("Repeats", this->repeat);
    event_description.add_printable("Modifier", mod_string);

    return fmt::format("{:s}\n", event_description.print());
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
