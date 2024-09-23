
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "AcceleratedImage.hpp"


SDL::Painting::Image::AcceleratedImage::AcceleratedImage(Equipment::AcceleratedPaintbrush& paintbrush,
                                                         RegularImage& picture): picture_texture{SDL_CreateTextureFromSurface(paintbrush.Access_SDL_Implementation(),
                                                                                                                              picture.Access_SDL_Implementation())}
{
    if (this->picture_texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }
}


SDL::Painting::Image::AcceleratedImage::AcceleratedImage(Equipment::AcceleratedPaintbrush& paintbrush,
                                    				         const fs::path& image_file): picture_texture{IMG_LoadTexture(paintbrush.Access_SDL_Implementation(),
                                                                                                                          image_file.string().c_str())}
{
	if (this->picture_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", image_file.filename().c_str()); 
	}
}


SDL_Texture* SDL::Painting::Image::AcceleratedImage::Access_SDL_Implementation() { return this->picture_texture; }


SDL::Painting::Image::AcceleratedImage::~AcceleratedImage()
{
    SDL_DestroyTexture(this->picture_texture);
    this->picture_texture = nullptr;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
