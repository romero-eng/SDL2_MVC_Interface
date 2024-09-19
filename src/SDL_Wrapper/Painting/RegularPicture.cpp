
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "RegularPicture.hpp"


SDL::Painting::RegularPicture::RegularPicture(const fs::path& image_path): picture_surface{this->LoadSurfaceFromFile(image_path)} {}


SDL::Painting::RegularPicture::RegularPicture(SDL_Surface* surface): picture_surface{surface} {}


void SDL::Painting::RegularPicture::PostPicture(SDL::Painting::RegularPicture& src)
{
    this->PostPicture(src, nullptr, nullptr);
}


void SDL::Painting::RegularPicture::PostPicture(SDL::Painting::RegularPicture& src,
                                                const SDL::Rect* srcrect,
                                                SDL::Rect* dstrect)
{
    if(SDL_BlitSurface(src.Access_SDL_Implementation(), srcrect, this->picture_surface, dstrect) != 0)
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}
}


SDL_Surface* SDL::Painting::RegularPicture::Access_SDL_Implementation()
{
    return this->picture_surface;
}


SDL::Painting::RegularPicture::~RegularPicture(){ SDL_FreeSurface(this->picture_surface); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
