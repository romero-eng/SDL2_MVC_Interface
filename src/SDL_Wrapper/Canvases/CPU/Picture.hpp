#ifndef SURFACE_WRAPPER_h
#define SURFACE_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// C++ Standard Libaries
#include <filesystem>  // Needed for specifying paths to Bitmaps and Image files
namespace fs = std::filesystem;

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL{ namespace CPU { namespace Pictures { using Picture = SDL_Surface; } } }

namespace SDL
{
    namespace CPU
    {
        namespace Pictures
        {
            Picture* LoadFromFile(fs::path&& image_path);

            Picture* LoadFromFile(fs::path& image_path);

            void FreeSurface(Picture* surface);
        }
    }
}


#endif
