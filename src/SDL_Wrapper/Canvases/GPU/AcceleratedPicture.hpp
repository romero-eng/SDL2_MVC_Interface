#ifndef TEXTURE_WRAPPER_H
#define TEXTURE_WRAPPER_H

// Original SDL2 API
#include <SDL2/SDL.h>

// Custom wrapper code for SDL2 API
#include "Paintbrush.hpp"
#include "../CPU/Picture.hpp"


namespace SDL
{
    class AcceleratedPicture
    {
    private:

        SDL_Texture* picture_texture;

    protected:

        SDL_Texture* CreateTextureFromSurface(GPU::Painting::Paintbrush* renderer,
                                              SDL_Surface* surfaceToConvert);

        SDL_Surface* LoadSurfaceFromFile(fs::path& image_path);

        SDL_Texture* LoadTextureFromFile(fs::path& bitmap_path,
                                         SDL::GPU::Painting::Paintbrush* render);

    public:

        AcceleratedPicture(SDL::GPU::Painting::Paintbrush* render,
                           SDL_Surface* surfaceToConvert);

        AcceleratedPicture(SDL::GPU::Painting::Paintbrush* render,
                           fs::path& image_file);

        ~AcceleratedPicture();
    };
}

#endif
