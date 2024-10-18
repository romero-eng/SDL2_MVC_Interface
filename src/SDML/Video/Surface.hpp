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
#include <optional>

namespace SDML
{
    namespace Video
    {
        class Window;

        class Surface
        {
        public:

            enum class YUV_CONVERSION_MODE
            {
                JPEG,
                BT601,
                BT709,
                AUTOMATIC
            };

        private:

            std::string name;
            SDL_Surface* internal_SDL_surface;

            static YUV_CONVERSION_MODE SDL_to_SDML(const SDL_YUV_CONVERSION_MODE& mode);

            static SDL_YUV_CONVERSION_MODE SDML_to_SDL(const YUV_CONVERSION_MODE& mode);

        public:

            static YUV_CONVERSION_MODE Get_YUV_ConversionMode();

            static YUV_CONVERSION_MODE Get_YUV_ConversionModeForResolution(Window& window);

            static void Set_YUV_ConversionMode(YUV_CONVERSION_MODE mode);

            static std::string to_string(YUV_CONVERSION_MODE mode);

            Surface(Window& window,
                    const std::filesystem::path& image_file);

            Surface();

            Surface(const Surface&) = delete;

            Surface& operator=(const Surface&) = delete;

            Surface(Surface&& surfaceToMove) noexcept;

            Surface& operator=(Surface&& surfaceToMove);

            ~Surface();

            std::string to_string() const;

            std::string GetName() const;

            std::array<int, 2> GetArea() const;

            std::array<uint8_t, 4> GetColor() const;

            void SetColor(const std::array<uint8_t, 4>& color);

            Blending::Mode GetBlendMode() const;

            void SetBlendMode(const Blending::Mode& mode);

            std::optional<std::array<uint8_t, 3>> GetTransparentColor() const;

            void EnableOrDisableTransparentColor(std::array<uint8_t, 3> color,
                                                 bool enable);

            void EnableOrDisable_RLE_Acceleration(bool enable);

            bool Has_RLE_Acceleration() const;

            std::pair<std::array<int, 2>, std::array<int, 2>> GetClipRectangle() const;

            bool SetClipRectangle(const std::pair<std::array<int, 2>, std::array<int, 2>>& clip_rect_info);

            void DisableClipping();

            void Blit(Surface& src,
					  const std::pair<std::array<int, 2>, std::array<int, 2>>& dst_rect_info,
					  const std::pair<std::array<int, 2>, std::array<int, 2>>& src_rect_info);

            void Blit(Surface& src);

            SDL_Surface* Access_SDL_Backend();
        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Surface& surface);

#endif
