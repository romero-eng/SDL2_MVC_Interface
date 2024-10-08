#ifndef TEXTURE_H
#define TEXTURE_H

// Custom Code from this project
#include "Renderer.hpp"
#include "../../Misc/PrettyPrint.hpp"

// Third-Party Libraries
#include <SDL2/SDL.h>
#include <fmt/format.h>

//C++ Standard Libraries
#include <array>


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
            std::optional<std::string_view> renderer_name;
            SDL_Texture* internal_SDL_texture;

        public:

            Texture(const char* name,
                    Renderer& renderer,
                    uint32_t pixel_format,
                    const TextureAccess& access,
                    const std::array<int, 2>& area);

            Texture(Texture&) = delete;

            Texture& operator=(Texture&) = delete;

            Texture(const char* name,
                    SDL_Texture* texture);

            ~Texture();

        };
    }
}


#endif
