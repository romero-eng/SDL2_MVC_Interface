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
            Renderer(Window& window);

            Renderer(Renderer&) = delete;

            Renderer& operator=(Renderer&) = delete;

            ~Renderer();
        };
    }
}

#endif
