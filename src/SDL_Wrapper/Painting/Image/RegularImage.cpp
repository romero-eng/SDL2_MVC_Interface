
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "RegularImage.hpp"


SDL::Painting::Image::RegularImage::RegularImage(const fs::path& image_path): picture_surface{IMG_Load(image_path.string().c_str())}
{
    if(this->picture_surface == nullptr)
    {
        throw fmt::format("Could not load image file ('{:s}') as a picture: {:s}", image_path.string().c_str(), SDL_GetError());
    }
}


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
