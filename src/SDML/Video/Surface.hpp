#ifndef SURFACE_H
#define SURFACE_H

// Custom Code from this project
#include "Window.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// C++ Standard Libraries
#include <filesystem>

namespace SDML
{
    namespace Video
    {
        class Window;

        class Surface
        {
        private:

            std::string name;
            SDL_Surface* internal_SDL_surface;

        public:

            Surface(Window& window,
                    const std::filesystem::path& image_file);

            Surface(Surface&) = delete;

            Surface& operator=(Surface&) = delete;

            ~Surface();

        };
    }
}

#endif
