#ifndef REGULAR_PICTURE_H
#define REGULAR_PICTURE_H

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Custom wrapper code for SDL2 API
#include "Rectangle.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <filesystem>  // Needed for specifying paths to Bitmaps and Image files
namespace fs = std::filesystem;


namespace SDL
{
    namespace Painting
    {
        class RegularPicture
        {
        private:

            SDL_Surface* picture_surface;

            void PostPicture(RegularPicture& src,
                             const Rect* srcrect,
                             Rect* dstrect);

        public:

            RegularPicture(const fs::path& image_path);

            RegularPicture(SDL_Surface* surface);

            RegularPicture(const RegularPicture& picture) = delete; // Copy Constructor

            RegularPicture& operator=(const RegularPicture& picture) = delete; // Copy Assignment

            void PostPicture(RegularPicture& src);

            void PostPicture(RegularPicture& src,
                             const Rect& srcrect,
                             Rect& dstrect);

            void PostPicture(RegularPicture& src,
                             const Rect& srcrect,
                             Rect&& dstrect);

            SDL_Surface* Access_SDL_Implementation();

            ~RegularPicture();
        };
    }
}


#endif
