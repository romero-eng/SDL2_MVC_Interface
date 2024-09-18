#ifndef PICTURE_IDEA_H
#define PICTURE_IDEA_H

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Third-Party Libaries
#include <fmt/format.h> // Needed for formatting Exception messages

// C++ Standard Libaries
#include <filesystem>  // Needed for specifying paths to Bitmaps and Image files
namespace fs = std::filesystem;


namespace SDL
{
    namespace Painting
    {
        class PictureIdea
        {
        protected:

            SDL_Surface* LoadSurfaceFromFile(fs::path& image_path);

        public:

            virtual ~PictureIdea() = 0;

        };
    }
}

#endif
