#ifndef TEXTURE_H
#define TEXTURE_H

// Custom Code from this project
#include "Renderer.hpp"
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
                    std::filesystem::path image_file);

            Texture(Texture&) = delete;

            Texture& operator=(Texture&) = delete;

            ~Texture();

            std::string GetName() const;

            std::string GetPixelFormatName() const;

            SDL_Texture* Access_SDL_Backend();

        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Texture& texture);

#endif
