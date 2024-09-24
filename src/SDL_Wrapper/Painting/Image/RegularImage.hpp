#ifndef REGULAR_IMAGE_H
#define REGULAR_IMAGE_H

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Custom wrapper code for SDL2 API
#include "../Equipment/Rectangle.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <filesystem>  // Needed for specifying paths to Bitmaps and Image files
namespace fs = std::filesystem;


namespace SDL
{
    namespace Painting
    {
        namespace Image
        {
            class RegularImage
            {
            private:

                SDL_Surface* picture_surface;

            public:

                RegularImage(const fs::path& image_path);

                RegularImage(const RegularImage& picture) = delete; // Copy Constructor

                RegularImage& operator=(const RegularImage& picture) = delete; // Copy Assignment

                SDL_Surface* Access_SDL_Implementation();

                ~RegularImage();
            };
        }
    }
}


#endif
