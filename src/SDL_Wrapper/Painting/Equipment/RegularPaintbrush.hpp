#ifndef REGULAR_PAINTBRUSH_WRAPPER_H
#define REGULAR_PAINTBRUSH_WRAPPER_H

// Custom wrapper code for SDL2 API
#include "Canvas.hpp"
#include "../Image/RegularImage.hpp"

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

namespace SDL
{
    namespace Painting
    {
        namespace Equipment
        {
            class RegularPaintbrush
            {
            private:

                Canvas& canvas;

            public:

                RegularPaintbrush(Canvas& canvas);

                void Fill(Uint8 r, Uint8 g, Uint8 b);

                void PostPicture(Image::RegularImage& src);

                void PostPicture(Image::RegularImage& src,
                                 const Rect* srcrect,
                                 Rect* dstrect);

                void Present();

            };
        }
    }
}

#endif
