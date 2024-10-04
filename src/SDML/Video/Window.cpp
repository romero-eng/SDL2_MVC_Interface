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
				   			WindowInitFlag flag): Window(title,
				   									 SDL_WINDOWPOS_UNDEFINED,
													 SDL_WINDOWPOS_UNDEFINED,
										 			 width,
										 			 height,
										 			 std::to_underlying(flag)) {}


SDML::Video::Window::Window(const char *title,
		                   	int x, int y,
						   	int width,
                		   	int height,
				   			WindowInitFlag flag): Window(title,
				   									 x, y,
										 			 width,
										 			 height,
										 			 std::to_underlying(flag)) {}


SDML::Video::Window::Window(const char *title,
						   	int width,
        		           	int height,
						   	uint32_t flags): Window(title,
				   						 	 	  SDL_WINDOWPOS_UNDEFINED,
										 		  SDL_WINDOWPOS_UNDEFINED,
										 		  width,
										 		  height,
										 		  flags) {}


SDML::Video::Window::Window(const char *title,
                   			int x, int y,
						    int width,
                   			int height,
				   			uint32_t flags): internal_SDL_window{SDL_CreateWindow(title,
				   															    x, y,
																	   			width,
																	   			height,
																	   			flags)} {}


SDML::Video::Window::~Window()
{
	if(SDL_HasWindowSurface(this->internal_SDL_window))
	{
		if(SDL_DestroyWindowSurface(this->internal_SDL_window) < 0)
		{
			std::cerr << fmt::format("Could not Destroy Surface for '{:s}' Window: {:s}",
									 this->GetTitle(),
									 SDL_GetError());
		}
	}
	SDL_DestroyWindow(this->internal_SDL_window);
}


int SDML::Video::Window::GetDisplayIndex()
{
	int display_index {SDL_GetWindowDisplayIndex(this->internal_SDL_window)};

	if(display_index < 0)
	{
		throw std::runtime_error(fmt::format("Could not find a Display for the '{:s}' Window: {:s}",
										     this->GetTitle(),
										     SDL_GetError()));
	}

	return display_index;
}


SDL_Rect SDML::Video::Window::GetFullscreenDisplayBounds()
{
	SDL_Rect bounds {};

	if(SDL_GetDisplayBounds(this->GetDisplayIndex(), &bounds) < 0)
	{
		throw std::runtime_error(fmt::format("Could not retrive fullscreen boundaries for '{:s}' Display: {:s}",
										     this->GetDisplayName(),
										     SDL_GetError()));
	}

	return bounds;
}


SDL_Rect SDML::Video::Window::GetUsableDisplayBounds()
{
	SDL_Rect bounds {};

	if(SDL_GetDisplayUsableBounds(this->GetDisplayIndex(), &bounds) < 0)
	{
		throw std::runtime_error(fmt::format("Could not retrive usable boundaries for '{:s}' Display: {:s}",
										     this->GetDisplayName(),
										     SDL_GetError()));
	}

	return bounds;
}


SDL_DisplayMode SDML::Video::Window::GetDisplayMode()
{
	SDL_DisplayMode display_mode {};

	if(SDL_GetWindowDisplayMode(this->internal_SDL_window, &display_mode) < 0)
	{
		throw std::runtime_error(fmt::format("Could not retrieve the Display Mode for the '{:s}' Window: {:s}",
										  	 this->GetTitle(),
										  	 SDL_GetError()));
	}

	return display_mode;
}


std::string SDML::Video::Window::GetTitle() { return std::string{SDL_GetWindowTitle(this->internal_SDL_window)}; }


std::string SDML::Video::Window::GetDisplayName()
{
	int display_index {GetDisplayIndex()};
	const char* display_name {SDL_GetDisplayName(display_index)};

	if(display_name == nullptr)
	{
		throw std::runtime_error(fmt::format("Could not get name for Display #{:d}: {:s}",
										  	 display_index,
										  	 SDL_GetError()));
	}

	return std::string {display_name};
}


uint32_t SDML::Video::Window::GetID()
{
	uint32_t ID {SDL_GetWindowID(this->internal_SDL_window)};

	if(ID == 0)
	{
		throw std::runtime_error(fmt::format("Could not retrieve the ID for the '{:s}' Window: {:s}",
										     this->GetTitle(),
										     SDL_GetError()));
	}

	return ID;
}


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
								 this->GetTitle(),
								 width,
								 width_in_pixels) << std::endl;
	}

	return width;
}


int SDML::Video::Window::GetMinimumWidth()
{
	int min_width {};

	SDL_GetWindowMinimumSize(this->internal_SDL_window, &min_width, nullptr);

	return min_width;
}


int SDML::Video::Window::GetMaximumWidth()
{
	int max_width {};

	SDL_GetWindowMaximumSize(this->internal_SDL_window, &max_width, nullptr);

	return max_width;
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
								 this->GetTitle(),
								 height,
								 height_in_pixels) << std::endl;
	}

	return height;
}


int SDML::Video::Window::GetMinimumHeight()
{
	int min_height {};

	SDL_GetWindowMinimumSize(this->internal_SDL_window, nullptr, &min_height);

	return min_height;
}


int SDML::Video::Window::GetMaximumHeight()
{
	int max_height {};

	SDL_GetWindowMaximumSize(this->internal_SDL_window, nullptr, &max_height);

	return max_height;
}


float SDML::Video::Window::GetBrightness() { return SDL_GetWindowBrightness(this->internal_SDL_window); }


float SDML::Video::Window::GetOpacity()
{
	float opacity {};

	if(SDL_GetWindowOpacity(this->internal_SDL_window, &opacity) < 0)
	{
		throw std::runtime_error(fmt::format("Could not get the opacity for the '{:s}' Window: {:s}",
										  	 this->GetTitle(),
										  	 SDL_GetError()));
	}

	return opacity;
}


std::string SDML::Video::Window::GetPixelFormatName()
{
	std::string pixel_format {SDL_GetPixelFormatName(SDL_GetWindowPixelFormat(this->internal_SDL_window))};

	if(pixel_format == "SDL_PIXELFORMAT_UNKNOWN")
	{
		throw fmt::format("Could not get the pixel format for the '{:s}' WIndow: {:s}",
						  this->GetTitle(),
						  SDL_GetError());
	}

	return pixel_format;
}


bool SDML::Video::Window::CheckWindowInitFlags(uint32_t flags) { return flags == (flags & SDL_GetWindowFlags(this->internal_SDL_window)); }


bool SDML::Video::Window::CheckWindowInitFlags(WindowInitFlag flag) { return std::to_underlying(flag) == (std::to_underlying(flag) & SDL_GetWindowFlags(this->internal_SDL_window)); }


void SDML::Video::Window::SetMinimumArea(int min_width, int min_height) { SDL_SetWindowMinimumSize(this->internal_SDL_window, min_width, min_height); }


void SDML::Video::Window::SetMaximumArea(int max_width, int max_height) { SDL_SetWindowMaximumSize(this->internal_SDL_window, max_width, max_height); }


int SDML::Video::Window::GetDisplayWidth()
{
	std::string_view display_name {this->GetDisplayName()};
	SDL_Rect fullscreen_bounds {this->GetFullscreenDisplayBounds()};
	SDL_Rect usable_bounds {this->GetUsableDisplayBounds()};

	if(fullscreen_bounds.w != usable_bounds.w)
	{
				std::cerr << fmt::format("Warning: difference detected between Fullscreen width and Usable Width:\nFullscreen Width: {:d}\nUsable Width: {:d}",
										 fullscreen_bounds.w,
										 usable_bounds.w);
	}

	return fullscreen_bounds.w;
}


int SDML::Video::Window::GetDisplayHeight()
{
	std::string_view display_name {this->GetDisplayName()};
	SDL_Rect fullscreen_bounds {this->GetFullscreenDisplayBounds()};
	SDL_Rect usable_bounds {this->GetUsableDisplayBounds()};

	if(fullscreen_bounds.h != usable_bounds.h)
	{
		std::cerr << fmt::format("Warning: difference detected between Fullscreen Height and Usable Height:\nFullscreen Height: {:d}\nUsable Height: {:d}",
								 fullscreen_bounds.h,
								 usable_bounds.h);
	}

	return fullscreen_bounds.h;
}


SDML::Video::DisplayOrientation SDML::Video::Window::GetDisplayOrientation()
{
	DisplayOrientation display_orientation;

    switch(SDL_GetDisplayOrientation(GetDisplayIndex()))
    {
        case SDL_ORIENTATION_UNKNOWN:
            display_orientation = DisplayOrientation::UNKNOWN;
            break;
        case SDL_ORIENTATION_LANDSCAPE:
            display_orientation = DisplayOrientation::LANDSCAPE;
            break;
        case SDL_ORIENTATION_LANDSCAPE_FLIPPED:
            display_orientation = DisplayOrientation::LANDSCAPE_FLIPPED;
            break;
        case SDL_ORIENTATION_PORTRAIT:
            display_orientation = DisplayOrientation::PORTRAIT;
            break;
        case SDL_ORIENTATION_PORTRAIT_FLIPPED:
            display_orientation = DisplayOrientation::PORTRAIT_FLIPPED;
            break;
    }

    return display_orientation;
}


std::string SDML::Video::Window::GetDisplayModePixelFormatName()
{
	SDL_DisplayMode tmp {this->GetDisplayMode()};
	return std::string {SDL_GetPixelFormatName(tmp.format)};
}


int SDML::Video::Window::GetDisplayModeWidth()
{
	SDL_DisplayMode tmp {this->GetDisplayMode()};
	return tmp.w;
}


int SDML::Video::Window::GetDisplayModeHeight()
{
	SDL_DisplayMode tmp {this->GetDisplayMode()};
	return tmp.h;
}


int SDML::Video::Window::GetDisplayModeRefreshRate()
{
	SDL_DisplayMode tmp {this->GetDisplayMode()};
	return tmp.refresh_rate;
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

	if(SDL_FlashWindow(this->internal_SDL_window, internal_SDL_operation) < 0)  // SDL_FlashWindow() seems to have no effect
	{
		throw std::runtime_error(fmt::format("Could not Flash the '{:s}' Window: {:s}",
										  	 this->GetTitle(),
										  	 SDL_GetError()));
	}
}


SDL_Window* SDML::Video::Window::Access_SDL_Backend() { return this->internal_SDL_window; }


uint32_t operator|(const SDML::Video::WindowInitFlag& first_flag, const SDML::Video::WindowInitFlag& second_flag) { return std::to_underlying(first_flag) | std::to_underlying(second_flag) ; }


uint32_t operator|(const SDML::Video::WindowInitFlag& first_flag, uint32_t second_flag) { return std::to_underlying(first_flag) | second_flag ; }


uint32_t operator|(uint32_t first_flag, const SDML::Video::WindowInitFlag& second_flag) { return first_flag | std::to_underlying(second_flag) ; }


std::ostream& operator<<(std::ostream& output_stream,
						 SDML::Video::Window& window)
{
	std::string display_orientation_string;
	switch(window.GetDisplayOrientation())
	{
		case SDML::Video::DisplayOrientation::UNKNOWN:
			display_orientation_string = "Unknown";
			break;
		case SDML::Video::DisplayOrientation::LANDSCAPE:
			display_orientation_string = "Landscape";
			break;
		case SDML::Video::DisplayOrientation::LANDSCAPE_FLIPPED:
			display_orientation_string = "Flipped Landscape";
			break;
		case SDML::Video::DisplayOrientation::PORTRAIT:
			display_orientation_string = "Portrait";
			break;
		case SDML::Video::DisplayOrientation::PORTRAIT_FLIPPED:
			display_orientation_string = "Flipped Portrait";
			break;
	}

	Misc::Printables display_mode_settings {fmt::format("Display Mode", window.GetDisplayName())};
	display_mode_settings.add_printable(   	   "Width", window.GetDisplayModeWidth());
	display_mode_settings.add_printable(	  "Height", window.GetDisplayModeHeight());
	display_mode_settings.add_printable("Refresh Rate", window.GetDisplayModeRefreshRate());

	Misc::Printables display_settings {fmt::format("'{:s}' Display", window.GetDisplayName())};
	display_settings.add_printable(			   "Width", window.GetDisplayWidth());
	display_settings.add_printable(		      "Height", window.GetDisplayHeight());
	display_settings.add_printable(	     "Orientation", display_orientation_string);
	display_settings.add_printable("Pixel Format Name", window.GetDisplayModePixelFormatName());
	display_settings.add_printable(display_mode_settings);

	Misc::Printables window_settings {fmt::format("'{:s}' Window", window.GetTitle())};
	window_settings.add_printable(				   	    "ID", window.GetID());
	window_settings.add_printable(   "Top-Left X-Coordinate", window.GetX());
	window_settings.add_printable(   "Top-Left Y-Coordinate", window.GetY());
	window_settings.add_printable(				     "Width", window.GetWidth());
	window_settings.add_printable( "Minimally Allowed Width", window.GetMinimumWidth());
	window_settings.add_printable( "Maximally Allowed Width", window.GetMaximumWidth());
	window_settings.add_printable(			        "Height", window.GetHeight());
	window_settings.add_printable("Minimally Allowed Height", window.GetMinimumHeight());
	window_settings.add_printable("Maximally Allowed Height", window.GetMaximumHeight());
	window_settings.add_printable(		   	    "Brightness", window.GetBrightness());
	window_settings.add_printable(			   	   "Opacity", window.GetOpacity());
	window_settings.add_printable(		 	  "Pixel Format", window.GetPixelFormatName());
	window_settings.add_printable(		   "Window is shown", window.CheckWindowInitFlags(SDML::Video::WindowInitFlag::SHOWN));
	window_settings.add_printable(	   "Window is resizable", window.CheckWindowInitFlags(SDML::Video::WindowInitFlag::RESIZABLE));
	window_settings.add_printable(display_settings);

	std::cout << window_settings;

	return output_stream;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
