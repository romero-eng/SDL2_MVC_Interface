
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "AcceleratedPicture.hpp"


SDL::Painting::AcceleratedPicture::AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                                                      SDL_Surface* surfaceToConvert): paintbrush{paintbrush}
{
	this->picture_texture = SDL_CreateTextureFromSurface(this->paintbrush.Access_SDL_Implementation(), surfaceToConvert);

    if (this->picture_texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }
}

SDL::Painting::AcceleratedPicture::AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                                				      fs::path& image_file): paintbrush{paintbrush}
{
	SDL_Surface* tmpSurface { this->LoadSurfaceFromFile(image_file) };
	this->picture_texture = SDL_CreateTextureFromSurface(this->paintbrush.Access_SDL_Implementation(), tmpSurface);
	SDL_FreeSurface(tmpSurface);

	if (this->picture_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", image_file.filename().c_str()); 
	}
}

void SDL::Painting::AcceleratedPicture::Copy(const SDL::Rect* srcrect,
                          				     const SDL::Rect* dstrect)
{
    if (SDL_RenderCopy(this->paintbrush.Access_SDL_Implementation(), this->picture_texture, srcrect, dstrect) < 0)
    {
        throw fmt::format("Could not copy from the texture to the renderer: {:s}", SDL_GetError());
    }
}

SDL::Painting::AcceleratedPicture::~AcceleratedPicture()
{
    SDL_DestroyTexture(this->picture_texture);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
