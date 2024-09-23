
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Canvas.hpp"


SDL::Painting::Equipment::Canvas::Canvas(const char* title,
									     CanvasPositionFlags position_flag,
									     int w,
									     int h,
									     CanvasInitFlags init_flag): Canvas::Canvas(title,
									  											    static_cast<int>(std::to_underlying(position_flag)), 
																				    static_cast<int>(std::to_underlying(position_flag)),
																				 	w, h,
																				 	std::to_underlying(init_flag)) {}


SDL::Painting::Equipment::Canvas::Canvas(const char* title,
									     CanvasPositionFlags position_flag,
									     int w,
									     int h,
									     Uint32 init_flags): Canvas::Canvas(title,
									  									 	static_cast<int>(std::to_underlying(position_flag)),
																		 	static_cast<int>(std::to_underlying(position_flag)),
																		 	w, h,
																		 	init_flags) {}


SDL::Painting::Equipment::Canvas::Canvas(const char* title,
									     int x,
									     int y,
									     int w,
									     int h,
									     CanvasInitFlags init_flag): Canvas::Canvas(title,
									  											    x, y,
																				    w, h,
																				 	std::to_underlying(init_flag)) {}


SDL::Painting::Equipment::Canvas::Canvas(const char* title,
									  	 int x,
									  	 int y,
									  	 int w,
									  	 int h,
									  	 Uint32 init_flags): window{SDL_CreateWindow(title, x, y, w, h, init_flags)}
{
	if (this->window == nullptr)
	{
		throw fmt::format("\nWindow could not be created! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}
}


const char* SDL::Painting::Equipment::Canvas::GetTitle() { return SDL_GetWindowTitle(this->window); }


SDL_Window* SDL::Painting::Equipment::Canvas::Access_SDL_Implementation() { return this->window; }


SDL::Painting::Equipment::Canvas::~Canvas()
{
	SDL_DestroyWindow(this->window);
	this->window = nullptr;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
