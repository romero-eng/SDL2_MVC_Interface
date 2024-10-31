#ifndef TEXTURE_H
#define TEXTURE_H

// Custom Code from this project
#include "Renderer.hpp"
#include "Surface.hpp"
#include "BlendMode.hpp"
#include "../../Logging/PrettyPrint.hpp"
#include "../../Logging/Logfile.hpp"

// Third-Party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fmt/format.h>

//C++ Standard Libraries
#include <array>
#include <filesystem>


namespace SDML
{
    namespace Video
    {
        class Surface;
        class Renderer;

        class Texture
        {

        friend class Renderer;

        public:

            enum class Access: int
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

        private:
    
            std::string name;

            SDL_Texture* internal_SDL_texture;

            bool _internal_SDL_texture_ownership;

        public:

            Texture(const char* name,
                    Renderer& renderer,
                    uint32_t pixel_format,
                    const Access& access,
                    const std::array<int, 2>& area);

            Texture(const char* name,
                    SDL_Texture* texture);

            Texture(Renderer& renderer,
                    Surface& surface);

            Texture(Renderer& renderer,
                    const std::filesystem::path& image_file);

            Texture();

            Texture(const Texture& textureToCopy);

            Texture& operator=(const Texture& textureToCopy);

            Texture(Texture&& textureToMove) noexcept;

            Texture& operator=(Texture&& textureToMove);

            ~Texture();

            std::string to_string() const;

            std::string GetName() const;

            std::string GetPixelFormatName() const;

            Access GetAccess() const;

            std::array<int, 2> GetArea() const;

            std::array<uint8_t, 3> GetColor() const;

            std::pair<SDML::Video::Blending::Mode, uint8_t> GetBlendModeAndAlpha() const;

            void SetColor(const std::array<uint8_t, 3> color,
                          const Blending::Mode& mode = SDML::Video::Blending::Mode::REPLACE,
                          uint8_t alpha = 0xFF);

            ScaleMode GetScaleMode() const;

            void SetScaleMode(const ScaleMode& mode);

        };
    }
}

std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Texture& texture);

#endif
