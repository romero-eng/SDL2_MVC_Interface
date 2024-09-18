
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "RegularPicture.hpp"


SDL::Painting::RegularPicture::RegularPicture(fs::path& image_path): picture_surface{this->LoadSurfaceFromFile(image_path)} {}


SDL::Painting::RegularPicture::RegularPicture(SDL_Surface* surface): picture_surface{surface} {}


SDL::Painting::RegularPicture::~RegularPicture() { SDL_FreeSurface(this->picture_surface); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
