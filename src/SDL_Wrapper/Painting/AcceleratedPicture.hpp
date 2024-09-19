#ifndef ACCELERATED_PICTURE_H
#define ACCELERATED_PICTURE_H

// Custom wrapper code for SDL2 API
#include "PictureIdea.hpp" // Abstract Base Class for AcceleratedPicture()
#include "AcceleratedPaintbrush.hpp"
#include "../Rectangle.hpp"


namespace SDL
{
    namespace Painting
    {
        class AcceleratedPicture: public PictureIdea
        {
        private:

            AcceleratedPaintbrush& paintbrush;

            SDL_Texture* picture_texture;

            SDL_Texture* createTextureFromFile(const fs::path& image_file);

        public:

            AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                               SDL_Surface* surfaceToConvert);

            AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                               const fs::path& image_file);

            AcceleratedPicture(const AcceleratedPicture& picture) = delete; // Copy Constructor

            AcceleratedPicture& operator=(const AcceleratedPicture& picture) = delete; // Copy Assignment

            void Copy();

            void Copy(const SDL::Rect* srcrect,
                      const SDL::Rect* dstrect);

            ~AcceleratedPicture();
        };
    }
}

#endif
