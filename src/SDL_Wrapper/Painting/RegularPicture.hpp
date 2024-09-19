#ifndef REGULAR_PICTURE_H
#define REGULAR_PICTURE_H

// Custom wrapper code for SDL2 API
#include "PictureIdea.hpp" // Abstract Base Class for RegularPicture()
#include "../Rectangle.hpp"


namespace SDL
{
    namespace Painting
    {
        class RegularPicture: public PictureIdea
        {
        private:

            SDL_Surface* picture_surface;

        public:

            RegularPicture(const fs::path& image_path);

            RegularPicture(SDL_Surface* surface);

            RegularPicture(const RegularPicture& picture) = delete; // Copy Constructor

            RegularPicture& operator=(const RegularPicture& picture) = delete; // Copy Assignment

            void PostPicture(RegularPicture& src);

            void PostPicture(RegularPicture& src,
                             const Rect* srcrect,
                             Rect* dstrect);

            SDL_Surface* Access_SDL_Implementation();

            ~RegularPicture();
        };
    }
}


#endif
