
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "RegularPaintbrush.hpp"


SDL::Painting::Equipment::RegularPaintbrush::RegularPaintbrush(Canvas& canvas): canvas{canvas} {}


void SDL::Painting::Equipment::RegularPaintbrush::PaintImageOverArea(Image::RegularImage& image,
                            			    	     	      		 const Rect* imageArea,
                             				    	          		 Rect* canvasArea)
{
    if(SDL_BlitSurface(image.Access_SDL_Implementation(), imageArea, SDL_GetWindowSurface(this->canvas.Access_SDL_Implementation()), canvasArea) != 0)
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}
}


void SDL::Painting::Equipment::RegularPaintbrush::PaintImage(Image::RegularImage& image) { this->PaintImageOverArea(image, nullptr, nullptr); }


void SDL::Painting::Equipment::RegularPaintbrush::PaintImageOverArea(Image::RegularImage& image, const Rect& imageArea, Rect& canvasArea) { this->PaintImageOverArea(image, &imageArea, &canvasArea); }


void SDL::Painting::Equipment::RegularPaintbrush::CopyPasteImageIntoLargerImage(Image::RegularImage& largerImage,
    							                                                Image::RegularImage& smallerImage,
                                    								            const Rect& imageArea,
                                                								Rect& canvasArea)
{
    if(SDL_BlitSurface(largerImage.Access_SDL_Implementation(), &imageArea, smallerImage.Access_SDL_Implementation(), &canvasArea) != 0)
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}
}


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


void SDL::Painting::Equipment::RegularPaintbrush::Present()
{
	if(SDL_UpdateWindowSurface(this->canvas.Access_SDL_Implementation()) < 0)
	{
		throw fmt::format("Could not update '{:s}' Canvas: {:s}", SDL_GetWindowTitle(this->canvas.Access_SDL_Implementation()), SDL_GetError());
	}
}


#endif
