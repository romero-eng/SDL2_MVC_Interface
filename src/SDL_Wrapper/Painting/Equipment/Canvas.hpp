#ifndef WINDOWS_WRAPPER_h
#define WINDOWS_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// Custom wrapper code for SDL2 API
#include "../Image/RegularImage.hpp"  // Every Canvas has an inherent Regular Picture (i.e., every Window has an inherent Surface in the SDL2 API)

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations
#include <utility> // Needed for retrieving underlying type of scoped enumerations


namespace SDL
{
    namespace Painting
    {
        namespace Equipment
        {
            enum class CanvasInitFlags: std::uint32_t
            {
                FULLSCREEN         = SDL_WINDOW_FULLSCREEN,
                OPENGL             = SDL_WINDOW_OPENGL,
                SHOWN              = SDL_WINDOW_SHOWN,
                HIDDEN             = SDL_WINDOW_HIDDEN,
                BORDERLESS         = SDL_WINDOW_BORDERLESS,
                RESIZABLE          = SDL_WINDOW_RESIZABLE,
                MINIMIZED          = SDL_WINDOW_MINIMIZED,
                MAXIMIZED          = SDL_WINDOW_MAXIMIZED,
                MOUSE_GRABBED      = SDL_WINDOW_MOUSE_GRABBED,
                INPUT_FOCUS        = SDL_WINDOW_INPUT_FOCUS,
                MOUSE_FOCUS        = SDL_WINDOW_MOUSE_FOCUS,
                FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
                FOREIGN            = SDL_WINDOW_FOREIGN,
                ALLOW_HIGHDPI      = SDL_WINDOW_ALLOW_HIGHDPI,

                MOUSE_CAPTURE      = SDL_WINDOW_MOUSE_CAPTURE,
                ALWAYS_ON_TOP      = SDL_WINDOW_ALWAYS_ON_TOP,
                SKIP_TASKBAR       = SDL_WINDOW_SKIP_TASKBAR,
                UTILITY            = SDL_WINDOW_UTILITY,
                TOOLTIP            = SDL_WINDOW_TOOLTIP,
                POPUP_MENU         = SDL_WINDOW_POPUP_MENU,
                KEYBOARD_GRABBED   = SDL_WINDOW_KEYBOARD_GRABBED,
                VULKAN             = SDL_WINDOW_VULKAN,
                METAL              = SDL_WINDOW_METAL,

                INPUT_GRABBED = MOUSE_GRABBED
            };

            enum class CanvasPositionFlags: std::uint32_t
            {
                UNDEFINED = SDL_WINDOWPOS_UNDEFINED,
                CENTERED  = SDL_WINDOWPOS_CENTERED
            };

            class Canvas
            {
            private:

                SDL_Window* window;

            public:

                Canvas(const char* title, CanvasPositionFlags position_flag, int w, int h, CanvasInitFlags init_flag);

                Canvas(const char* title, CanvasPositionFlags position_flag, int w, int h, Uint32 init_flags);

                Canvas(const char* title, int x, int y, int w, int h, CanvasInitFlags init_flag);

                Canvas(const char* title, int x, int y, int w, int h, Uint32 init_flags);

                Canvas(const Canvas& canvas) = delete; // Copy Constructor

                Canvas& operator=(const Canvas& canvas) = delete; // Copy Assignment

                const char* GetTitle();

                SDL_Window* Access_SDL_Implementation();

                ~Canvas();
            };
        }
    }
}


#endif
