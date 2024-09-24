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

                void PaintImageOverArea(Image::RegularImage& image,
                                        const Rect* imageArea,
                                        Rect* canvasArea);

            public:

                RegularPaintbrush(Canvas& canvas);

                void OptimizeImageForPainting(Image::RegularImage& image);

                void PaintImage(Image::RegularImage& image);

                void PaintImageOverArea(Image::RegularImage& image,
                                        const Rect& imageArea,
                                        Rect& canvasArea);

                void CopyPasteImageIntoLargerImage(Image::RegularImage& largerImage,
                                                   Image::RegularImage& smallerImage,
                                                   const Rect& imageArea,
                                                   Rect& canvasArea);

                void Fill(Uint8 r, Uint8 g, Uint8 b);

            };
        }
    }
}

#endif
