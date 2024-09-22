#ifndef ACCELERATED_IMAGE_H
#define ACCELERATED_IMAGE_H

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Custom wrapper code for SDL2 API
#include "../Equipment/AcceleratedPaintbrush.hpp"
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
        namespace Equipment
        {
            class AcceleratedPaintbrush; // Forward Declaration of AcceleratedPaintbrush Class to resolve circular include
        }

        namespace Image
        {
            class AcceleratedImage
            {
            private:

                SDL_Texture* picture_texture;

            public:

                AcceleratedImage(Equipment::AcceleratedPaintbrush& paintbrush,
                                   SDL_Surface* surfaceToConvert);

                AcceleratedImage(Equipment::AcceleratedPaintbrush& paintbrush,
                                   const fs::path& image_file);

                AcceleratedImage(const AcceleratedImage& picture) = delete; // Copy Constructor

                AcceleratedImage& operator=(const AcceleratedImage& picture) = delete; // Copy Assignment

                SDL_Texture* Access_SDL_Implementation();

                ~AcceleratedImage();
            };
        }
    }
}

#endif
