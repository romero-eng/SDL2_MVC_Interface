#ifndef SURFACE_H
#define SURFACE_H

// Custom Code from this project
#include "../../Misc/PrettyPrint.hpp"
#include "Window.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <array>
#include <iostream>
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

            std::string GetName() const;

            std::array<uint8_t, 4> GetColor() const;

            void SetColor(const std::array<uint8_t, 4>& color);

        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Surface& surface);

#endif
