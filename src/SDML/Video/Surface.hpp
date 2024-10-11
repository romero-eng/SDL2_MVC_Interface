#ifndef SURFACE_H
#define SURFACE_H

// Custom Code from this project
#include "../../Misc/PrettyPrint.hpp"
#include "Window.hpp"
#include "BlendMode.hpp"

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

            std::array<int, 2> GetArea() const;

            std::array<uint8_t, 4> GetColor() const;

            void SetColor(const std::array<uint8_t, 4>& color);

            BlendMode GetBlendMode() const;

            void SetBlendMode(const BlendMode& mode);

            std::optional<std::array<uint8_t, 3>> GetTransparentColor() const;

            void EnableOrDisableTransparentColor(std::array<uint8_t, 3> color,
                                                 bool enable);

            void EnableOrDisable_RLE_Acceleration(bool enable);

            bool Has_RLE_Acceleration() const;

            std::pair<std::array<int, 2>, std::array<int, 2>> GetClipRectangle() const;

            bool SetClipRectangle(const std::pair<std::array<int, 2>, std::array<int, 2>>& clip_rect_info);

            void DisableClipping();

            /*
            void DrawRect(const std::pair<std::array<int, 2>, std::array<int, 2>>& rect_info,
                          const std::array<uint8_t, 3>& color);
            */

            SDL_Surface* Access_SDL_Backend();
        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Surface& surface);

#endif
