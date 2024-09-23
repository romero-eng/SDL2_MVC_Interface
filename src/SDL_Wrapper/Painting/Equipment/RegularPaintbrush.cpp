
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "RegularPaintbrush.hpp"


SDL::Painting::Equipment::RegularPaintbrush::RegularPaintbrush(Canvas& canvas): canvas{canvas} {}


void SDL::Painting::Equipment::RegularPaintbrush::Fill(Uint8 r, Uint8 g, Uint8 b)
{
	if(SDL_FillRect(SDL_GetWindowSurface(this->canvas.Access_SDL_Implementation()),
					NULL,
					SDL_MapRGB(SDL_GetWindowSurface(this->canvas.Access_SDL_Implementation())->format,
							   r, g, b)) < 0)
	{
		throw fmt::format("Could not fill in the '{:s}' Canvas: {:s}", SDL_GetWindowTitle(this->canvas.Access_SDL_Implementation()), SDL_GetError());
	}
}


void SDL::Painting::Equipment::RegularPaintbrush::PostPicture(Image::RegularImage& src) { this->PostPicture(src, nullptr, nullptr); }


void SDL::Painting::Equipment::RegularPaintbrush::PostPicture(Image::RegularImage& src,
                            			    	     	      const Rect* srcrect,
                             				    	          Rect* dstrect)
{
    if(SDL_BlitSurface(src.Access_SDL_Implementation(), srcrect, SDL_GetWindowSurface(this->canvas.Access_SDL_Implementation()), dstrect) != 0)
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}
}


void SDL::Painting::Equipment::RegularPaintbrush::Present()
{
	if(SDL_UpdateWindowSurface(this->canvas.Access_SDL_Implementation()) < 0)
	{
		throw fmt::format("Could not update '{:s}' Canvas: {:s}", SDL_GetWindowTitle(this->canvas.Access_SDL_Implementation()), SDL_GetError());
	}
}


#endif
