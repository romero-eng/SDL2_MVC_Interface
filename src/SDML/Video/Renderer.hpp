#ifndef RENDERER_H
#define RENDERER_H

// Custom Code from this project
#include "Window.hpp"
#include "../../Misc/PrettyPrint.hpp"

// Third-Party Libraries
#include <SDL2/SDL.h>
#include <fmt/format.h>

//C++ Standard Libraries
#include <array>
#include <vector>


namespace SDML
{
    namespace Video
    {
        enum class RendererInitFlag: uint32_t
        {
            SOFTWARE      = SDL_RENDERER_SOFTWARE,
            ACCELERATED   = SDL_RENDERER_ACCELERATED,
            PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,
            TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
        };

        class Renderer
        {
        private:
            SDL_Renderer* internal_SDL_renderer;

        public:

            Renderer(Window& window,
                     uint32_t flags);

            Renderer(Window& window,
                     RendererInitFlag flag);

            Renderer(Window& window);

            Renderer(Renderer&) = delete;

            Renderer& operator=(Renderer&) = delete;

            ~Renderer();

            std::string GetName();

            int GetWidth();

            int GetHeight();

            std::array<uint8_t, 4> GetColor();

            int GetMaxTextureWidth();

            int GetMaxTextureHeight();

            std::vector<std::string> GetTextureFormats();

            bool CheckInitFlags(uint32_t flags);

            bool CheckInitFlags(RendererInitFlag flag);
        };
    }
}

uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, const SDML::Video::RendererInitFlag& second_flag);

uint32_t operator|(uint32_t first_flag, const SDML::Video::RendererInitFlag& second_flag);

uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, uint32_t second_flag);

std::ostream& operator<<(std::ostream& output,
                         SDML::Video::Renderer& renderer);

#endif
