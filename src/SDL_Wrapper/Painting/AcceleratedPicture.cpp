
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "AcceleratedPicture.hpp"


SDL::Painting::AcceleratedPicture::AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                                                      SDL_Surface* surfaceToConvert): paintbrush{paintbrush},
                                                                                      picture_texture{SDL_CreateTextureFromSurface(this->paintbrush.Access_SDL_Implementation(),
                                                                                                                                   surfaceToConvert)}
{
    if (this->picture_texture == nullptr)
    {
        throw fmt::format("Could not create Texture from Surface: {:s}", SDL_GetError());
    }
}


SDL::Painting::AcceleratedPicture::AcceleratedPicture(AcceleratedPaintbrush& paintbrush,
                                				      fs::path& image_file): paintbrush{paintbrush},
                                                                             picture_texture{createTextureFromFile(image_file)}
{
	if (this->picture_texture == nullptr)
	{
		throw fmt::format("Could not load the '{:s}' Image", image_file.filename().c_str()); 
	}
}


SDL_Texture* SDL::Painting::AcceleratedPicture::createTextureFromFile(fs::path& image_file)
{
    SDL_Surface* tmpSurface { this->LoadSurfaceFromFile(image_file) };
	SDL_Texture* texture { SDL_CreateTextureFromSurface(this->paintbrush.Access_SDL_Implementation(), tmpSurface) };
	SDL_FreeSurface(tmpSurface);

    return texture;
}

void SDL::Painting::AcceleratedPicture::Copy()
{
    SDL::Painting::AcceleratedPicture::Copy(nullptr, nullptr);
}


void SDL::Painting::AcceleratedPicture::Copy(const SDL::Rect* srcrect,
                          				     const SDL::Rect* dstrect)
{
    if (SDL_RenderCopy(this->paintbrush.Access_SDL_Implementation(), this->picture_texture, srcrect, dstrect) < 0)
    {
        throw fmt::format("Could not copy the Accelerated Picture with the Paintbrush: {:s}", SDL_GetError());
    }
}


SDL::Painting::AcceleratedPicture::~AcceleratedPicture() { SDL_DestroyTexture(this->picture_texture); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
