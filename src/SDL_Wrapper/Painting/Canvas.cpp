
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Canvas.hpp"


SDL::Painting::Canvas::Canvas(const char* title,
							  int x,
							  int y,
							  int w,
							  int h,
							  Uint32 flags): window{SDL_CreateWindow(title, x, y, w, h, flags)}
{
	if (this->window == nullptr)
	{
		throw fmt::format("\nWindow could not be created! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}
}


const char* SDL::Painting::Canvas::GetTitle() { return SDL_GetWindowTitle(this->window); }


void SDL::Painting::Canvas::PostPicture(RegularPicture& src)
{
	this->PostPicture(src, nullptr, nullptr);
}


void SDL::Painting::Canvas::PostPicture(RegularPicture& src,
                            		 	const Rect* srcrect,
                             			Rect* dstrect)
{
    if(SDL_BlitSurface(src.Access_SDL_Implementation(), srcrect, SDL_GetWindowSurface(this->window), dstrect) != 0)
	{
		throw fmt::format("Could not blit 'src' Surface onto 'dst' Surface: {:s}", SDL_GetError());
	}

	if(SDL_UpdateWindowSurface(this->window) < 0)
	{
		throw fmt::format("Could not update '{:s}' Canvas: {:s}", this->GetTitle(), SDL_GetError());
	}
}


SDL_Window* SDL::Painting::Canvas::Access_SDL_Implementation()
{
	return this->window;
}


SDL::Painting::Canvas::~Canvas() { SDL_DestroyWindow(this->window); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
