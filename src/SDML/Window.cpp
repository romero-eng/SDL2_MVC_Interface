#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Window.hpp"

SDML::Video::Window::Window(const char *title,
				   			int width,
                   			int height): Window(title,
				   					   			SDL_WINDOWPOS_UNDEFINED,
									   			SDL_WINDOWPOS_UNDEFINED,
									   			width,
									   			height,
									  	 		0) {}


SDML::Video::Window::Window(const char *title,
				   			int x, int y,
				   			int width,
                   			int height): Window(title,
				   					  			x, y,
									   			width,
									   			height,
									   			0) {}


SDML::Video::Window::Window(const char *title,
				   			int width,
                   			int height,
				   			WindowFlag flag): Window(title,
				   									 SDL_WINDOWPOS_UNDEFINED,
													 SDL_WINDOWPOS_UNDEFINED,
										 			 width,
										 			 height,
										 			 std::to_underlying(flag)) {}


SDML::Video::Window::Window(const char *title,
		                   	int x, int y,
						   	int width,
                		   	int height,
				   			WindowFlag flag): Window(title,
				   									 x, y,
										 			 width,
										 			 height,
										 			 std::to_underlying(flag)) {}


SDML::Video::Window::Window(const char *title,
						   	int width,
        		           	int height,
						   	Uint32 flags): Window(title,
				   						 	 	  SDL_WINDOWPOS_UNDEFINED,
										 		  SDL_WINDOWPOS_UNDEFINED,
										 		  width,
										 		  height,
										 		  flags) {}


SDML::Video::Window::Window(const char *title,
                   			int x, int y,
						    int width,
                   			int height,
				   			Uint32 flags): internal_SDL_window{SDL_CreateWindow(title,
				   															    x, y,
																	   			width,
																	   			height,
																	   			flags)} {}


int SDML::Video::Window::GetX()
{
	int x {};

	SDL_GetWindowPosition(this->internal_SDL_window, &x, nullptr);

	return x;
}


int SDML::Video::Window::GetY()
{
	int y {};

	SDL_GetWindowPosition(this->internal_SDL_window, nullptr, &y);

	return y;
}


int SDML::Video::Window::GetWidth()
{
	int width {};
	int width_in_pixels {};

	SDL_GetWindowSize(this->internal_SDL_window, &width, nullptr);
	SDL_GetWindowSizeInPixels(this->internal_SDL_window, &width_in_pixels, nullptr);

	if(width != width_in_pixels)
	{
		std::cerr << fmt::format("Warning: For the '{:s}' Window, The width of the client area is different from the width in pixels:\nWidth: {:d}\nPixel Width: {:d}\n",
								 SDL_GetWindowTitle(this->AccessInternalWindow()),
								 width,
								 width_in_pixels) << std::endl;
	}

	return width;
}


int SDML::Video::Window::GetHeight()
{
	int height {};
	int height_in_pixels {};

	SDL_GetWindowSize(this->internal_SDL_window, nullptr, &height);
	SDL_GetWindowSizeInPixels(this->internal_SDL_window, nullptr, &height_in_pixels);

	if(height != height_in_pixels)
	{
		std::cerr << fmt::format("Warning: For the '{:s}' Window, The height of the client area is different from the height in pixels:\nHeight: {:d}\nPixel Height: {:d}\n",
								 SDL_GetWindowTitle(this->AccessInternalWindow()),
								 height,
								 height_in_pixels) << std::endl;
	}

	return height;
}


void SDML::Video::Window::Flash(FlashOperation operation)
{
	SDL_FlashOperation internal_SDL_operation;
	switch(operation)
	{
		case FlashOperation::CANCEL:
			internal_SDL_operation = SDL_FLASH_CANCEL;
            break;
		case FlashOperation::BRIEFLY:
			internal_SDL_operation = SDL_FLASH_BRIEFLY;
            break;
		case FlashOperation::UNTIL_FOCUSED:
			internal_SDL_operation = SDL_FLASH_UNTIL_FOCUSED;
            break;
	}

	if(SDL_FlashWindow(this->internal_SDL_window, internal_SDL_operation) < 0)
	{
		throw fmt::format("Could not Flash the '{:s}' Window: {:s}",
						  SDL_GetWindowTitle(this->internal_SDL_window),
						  SDL_GetError());
	}
}


SDML::Video::Window::~Window()
{
	if(SDL_HasWindowSurface(this->internal_SDL_window))
	{
		if(SDL_DestroyWindowSurface(this->internal_SDL_window) < 0)
		{
			std::cerr << fmt::format("Could not Destroy Surface for '{:s}' Window: {:s}",
									 SDL_GetWindowTitle(this->internal_SDL_window),
									 SDL_GetError());
		}
	}
	SDL_DestroyWindow(this->internal_SDL_window);
}


SDL_Window* SDML::Video::Window::AccessInternalWindow() { return this->internal_SDL_window; }


Uint32 operator|(const SDML::Video::WindowFlag& first_flag,
				 const SDML::Video::WindowFlag& second_flag)
{ return std::to_underlying(first_flag) | std::to_underlying(second_flag) ; }


Uint32 operator|(const SDML::Video::WindowFlag& first_flag,
				 Uint32 second_flag)
{ return std::to_underlying(first_flag) | second_flag ; }


Uint32 operator|(Uint32 first_flag,
				 const SDML::Video::WindowFlag& second_flag)
{ return first_flag | std::to_underlying(second_flag) ; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
