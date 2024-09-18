
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Canvas.hpp"


SDL::Painting::Canvas::Canvas(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	this->window = SDL_CreateWindow(title, x, y, w, h, flags);

	if (this->window == nullptr)
	{
		throw fmt::format("\nWindow could not be created! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}
}


const char* SDL::Painting::Canvas::GetTitle() { return SDL_GetWindowTitle(this->window); }


SDL::Painting::RegularPicture SDL::Painting::Canvas::GetRegularPicture()
{
	SDL_Surface* surface { SDL_GetWindowSurface(this->window) };

	if (surface == nullptr)
	{
		throw fmt::format("\nSurface could not be obtained from '{:s}' Window! SDL_Error:\n\n{:s}\n\n", this->GetTitle(), SDL_GetError() );
	}

	return RegularPicture(surface);
}


int SDL::Painting::Canvas::UpdateRegularPicture() { return SDL_UpdateWindowSurface(this->window); }


SDL_Window* SDL::Painting::Canvas::Access_SDL_Implementation()
{
	return this->window;
}


SDL::Painting::Canvas::~Canvas() { SDL_DestroyWindow(this->window); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
