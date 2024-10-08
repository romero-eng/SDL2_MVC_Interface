#ifndef TEXTURE_H
#define TEXTURE_H

// Custom Code from this project
#include "Renderer.hpp"
#include "BlendMode.hpp"
#include "../../Misc/PrettyPrint.hpp"

// Third-Party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fmt/format.h>

//C++ Standard Libraries
#include <array>
#include <iostream>
#include <filesystem>


namespace SDML
{
    namespace Video
    {
        enum class TextureAccess: int
        {
           STATIC    = SDL_TEXTUREACCESS_STATIC,
           STREAMING = SDL_TEXTUREACCESS_STREAMING,
           TARGET    = SDL_TEXTUREACCESS_TARGET
        };

        enum class ScaleMode: int
        {
           NEAREST = SDL_ScaleModeNearest,
           LINEAR  = SDL_ScaleModeLinear,
           BEST    = SDL_ScaleModeBest
        };

        class Renderer;

        class Texture
        {
        private:
            std::string name;
            SDL_Texture* internal_SDL_texture;

        public:

            Texture(const char* name,
                    Renderer& renderer,
                    uint32_t pixel_format,
                    const TextureAccess& access,
                    const std::array<int, 2>& area);

            Texture(const char* name,
                    SDL_Texture* texture);

            Texture(Renderer& renderer,
                    const std::filesystem::path& image_file);

            Texture(Texture&) = delete;

            Texture& operator=(Texture&) = delete;

            ~Texture();

            std::string GetName() const;

            std::string GetPixelFormatName() const;

            TextureAccess GetTextureAccess() const;

            std::array<int, 2> GetArea() const;

            std::array<uint8_t, 4> GetColor() const;

            void SetColor(const std::array<uint8_t, 4> color);

            BlendMode GetBlendMode() const;

            void SetBlendMode(const BlendMode& mode);

            ScaleMode GetScaleMode() const;

            void SetScaleMode(const ScaleMode& mode);

            SDL_Texture* Access_SDL_Backend();

        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Texture& texture);

#endif
