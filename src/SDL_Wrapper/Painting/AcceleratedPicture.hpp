#ifndef ACCELERATED_PICTURE_H
#define ACCELERATED_PICTURE_H

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Custom wrapper code for SDL2 API
#include "AcceleratedPaintbrush.hpp"
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
        class AcceleratedPaintbrush; // Forward Declaration of AcceleratedPaintbrush Class to resolve circular include

        class AcceleratedPicture
        {
        private:

            SDL_Texture* picture_texture;

        public:

            AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                               SDL_Surface* surfaceToConvert);

            AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                               const fs::path& image_file);

            AcceleratedPicture(const AcceleratedPicture& picture) = delete; // Copy Constructor

            AcceleratedPicture& operator=(const AcceleratedPicture& picture) = delete; // Copy Assignment

            SDL_Texture* Access_SDL_Implementation();

            ~AcceleratedPicture();
        };
    }
}

#endif
