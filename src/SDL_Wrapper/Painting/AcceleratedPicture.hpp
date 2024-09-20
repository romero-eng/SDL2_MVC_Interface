#ifndef ACCELERATED_PICTURE_H
#define ACCELERATED_PICTURE_H

// Custom wrapper code for SDL2 API
#include "AcceleratedPaintbrush.hpp"
#include "Rectangle.hpp"


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
