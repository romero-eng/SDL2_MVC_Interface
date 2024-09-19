#ifndef IMAGE_WRAPPER_h
#define IMAGE_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <cstdint> // Needed for setting underlying type for scoped enumerations
#include <utility> // Needed for retrieving underlying type of scoped enumerations

namespace SDL
{
    namespace Painting
    {
        enum class ImageFileTypes : std::uint32_t
        {
            JPG  = IMG_INIT_JPG,
            PNG  = IMG_INIT_PNG,
            TIF  = IMG_INIT_TIF,
            WEBP = IMG_INIT_WEBP,
            JXL  = IMG_INIT_JXL,
            AVIF = IMG_INIT_AVIF
        };

        void InitImageLoading(ImageFileTypes file_type);

        void InitImageLoading(Uint32 file_types);

        bool QueryImageLoadingInitialization();

        void QuitImageLoading(void);
    }
}

Uint32 operator|(SDL::Painting::ImageFileTypes first_flag, SDL::Painting::ImageFileTypes second_flag);
Uint32 operator|(                       Uint32 first_flag, SDL::Painting::ImageFileTypes second_flag);
Uint32 operator|(SDL::Painting::ImageFileTypes first_flag,                        Uint32 second_flag);

#endif
