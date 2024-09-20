
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "AcceleratedPicture.hpp"


SDL::Painting::AcceleratedPicture::AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                                                      SDL_Surface* surfaceToConvert): picture_texture{SDL_CreateTextureFromSurface(paintbrush.Access_SDL_Implementation(),
                                                                                                                                   surfaceToConvert)}
{
    if (this->picture_texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }
}


SDL::Painting::AcceleratedPicture::AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                                				      const fs::path& image_file): picture_texture{IMG_LoadTexture(paintbrush.Access_SDL_Implementation(),
                                                                                                                   image_file.string().c_str())}
{
	if (this->picture_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", image_file.filename().c_str()); 
	}
}


SDL_Texture* SDL::Painting::AcceleratedPicture::Access_SDL_Implementation()
{
    return this->picture_texture;
}


SDL::Painting::AcceleratedPicture::~AcceleratedPicture() { SDL_DestroyTexture(this->picture_texture); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
