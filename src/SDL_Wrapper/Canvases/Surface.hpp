#ifndef SURFACE_WRAPPER_h
#define SURFACE_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// C++ Standard Libaries
#include <filesystem>  // Needed for specifying paths to Bitmaps and Image files
namespace fs = std::filesystem;

// Type Aliases and Custom wrapper code for SDL2 API
namespace SDL{ namespace Surfaces { using Surface = SDL_Surface; } }

namespace SDL
{
    namespace Surfaces
    {
        
        Surface* Load_BMP(fs::path&& bitmap_path);

        Surface* Load_BMP(fs::path& bitmap_path);

        Surface* LoadSurface(fs::path&& bitmap_path);

        Surface* LoadSurface(fs::path& bitmap_path);

        void FreeSurface(Surface* surface);
    }
}


#endif
