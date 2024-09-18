#ifndef WINDOWS_WRAPPER_h
#define WINDOWS_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>

// Custom wrapper code for SDL2 API
#include "RegularPicture.hpp"  // Every Canvas has an inherent Regular Picture (i.e., every Window has an inherent Surface in the SDL2 API)

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages


namespace SDL
{
    namespace Painting
    {
        class Canvas
        {
        private:

            SDL_Window* window;

        public:

            Canvas(const char* title, int x, int y, int w, int h, Uint32 flags);

            const char* GetTitle();

            RegularPicture GetRegularPicture();

            int UpdateRegularPicture();

            SDL_Window* Access_SDL_Implementation();

            ~Canvas();
        };
    }
}


#endif
