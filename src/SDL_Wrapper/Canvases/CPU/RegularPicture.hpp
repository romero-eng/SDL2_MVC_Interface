#ifndef SURFACE_WRAPPER_h
#define SURFACE_WRAPPER_h

// Original SDL2 API
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// C++ Standard Libaries
#include <filesystem>  // Needed for specifying paths to Bitmaps and Image files
namespace fs = std::filesystem;


namespace SDL
{
    class RegularPicture
    {
    private:

        SDL_Surface* picture_surface;

    protected:

        SDL_Surface* LoadSurfaceFromFile(fs::path& image_path);

    public: 

        RegularPicture(fs::path&& image_path);

        RegularPicture(fs::path& image_path);

        ~RegularPicture();
    };
}


#endif
