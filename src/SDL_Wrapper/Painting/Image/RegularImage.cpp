
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "RegularImage.hpp"


SDL::Painting::Image::RegularImage::RegularImage(const fs::path& image_path): picture_surface{IMG_Load(image_path.string().c_str())}
{
    if(this->picture_surface == nullptr)
    {
        throw fmt::format("Could not load image file ('{:s}') as a picture: {:s}", image_path.string().c_str(), SDL_GetError());
    }
}


SDL::Painting::Image::RegularImage::RegularImage(SDL_Surface* surface): picture_surface{surface} {}


void SDL::Painting::Image::RegularImage::PostOntoPicture(RegularImage& src,
                                                           const Equipment::Rect* srcrect,
                                                           Equipment::Rect* dstrect)
{
    if(SDL_BlitSurface(src.Access_SDL_Implementation(), srcrect, this->picture_surface, dstrect) != 0)
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}
}


void SDL::Painting::Image::RegularImage::CopyOntoPicture(RegularImage& src) { this->PostOntoPicture(src, nullptr, nullptr); }


void SDL::Painting::Image::RegularImage::PostOntoPicture(RegularImage& src, const Equipment::Rect& srcrect, Equipment::Rect& dstrect) { this->PostOntoPicture(src, &srcrect, &dstrect); }


void SDL::Painting::Image::RegularImage::PostOntoPicture(RegularImage& src, const Equipment::Rect& srcrect, Equipment::Rect&& dstrect) { this->PostOntoPicture(src, &srcrect, &dstrect); }


SDL_Surface* SDL::Painting::Image::RegularImage::Access_SDL_Implementation()
{
    return this->picture_surface;
}


SDL::Painting::Image::RegularImage::~RegularImage()
{
    SDL_FreeSurface(this->picture_surface);
    this->picture_surface = nullptr;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
