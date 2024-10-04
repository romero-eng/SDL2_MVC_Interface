#ifndef RENDERER_H
#define RENDERER_H

// Custom Code from this project
#include "Window.hpp"

// Third-Party Libraries
#include <SDL2/SDL.h>


namespace SDML
{
    namespace Video
    {
        class Renderer
        {
        private:
            SDL_Renderer* internal_SDL_renderer;

        public:

            enum class InitFlag: uint32_t
            {
                SOFTWARE      = SDL_RENDERER_SOFTWARE,
                ACCELERATED   = SDL_RENDERER_ACCELERATED,
                PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,
                TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
            };

            Renderer(Window& window,
                     uint32_t flags);

            Renderer(Window& window,
                     InitFlag flag);

            Renderer(Window& window);

            Renderer(Renderer&) = delete;

            Renderer& operator=(Renderer&) = delete;

            ~Renderer();
        };
    }
}

uint32_t operator|(const SDML::Video::Renderer::InitFlag& first_flag, const SDML::Video::Renderer::InitFlag& second_flag);

uint32_t operator|(uint32_t first_flag, const SDML::Video::Renderer::InitFlag& second_flag);

uint32_t operator|(const SDML::Video::Renderer::InitFlag& first_flag, uint32_t second_flag);

#endif
