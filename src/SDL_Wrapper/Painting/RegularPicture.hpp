#ifndef REGULAR_PICTURE_H
#define REGULAR_PICTURE_H

#include "PictureIdea.hpp"

namespace SDL
{
    namespace Painting
    {
        class RegularPicture: public PictureIdea
        {
        private:

            SDL_Surface* picture_surface;

        public:

            RegularPicture(fs::path& image_path);

            RegularPicture(SDL_Surface* surface);

            ~RegularPicture();
        };
    }
}


#endif
