#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Window.hpp"

SDML::Video::Window::Window(const char *title,
				   			const std::array<int, 2>& area): Window(title,
														   			area,
											  	 					0) {}


SDML::Video::Window::Window(const char *title,
				   			const std::array<int, 2>& top_left_point,
				   			const std::array<int, 2>& area): Window(title,
							   					  					top_left_point,
												   					area,
												   					0) {}


SDML::Video::Window::Window(const char *title,
				   			const std::array<int, 2>& area,
				   			const WindowInitFlag& flag): Window(title,
										 						area,
										 						std::to_underlying(flag)) {}


SDML::Video::Window::Window(const char *title,
		                   	const std::array<int, 2>& top_left_point,
						   	const std::array<int, 2>& area,
				   			const WindowInitFlag& flag): Window(title,
					   											top_left_point,
													 			area,
													 			std::to_underlying(flag)) {}


SDML::Video::Window::Window(const char *title,
						   	const std::array<int, 2>& area,
						   	uint32_t flags): internal_SDL_window{SDL_CreateWindow(title,
					   						 								 	  SDL_WINDOWPOS_UNDEFINED,
																		 		  SDL_WINDOWPOS_UNDEFINED,
																		 		  area[0],
																				  area[1],
																		 		  flags)} {}


SDML::Video::Window::Window(const char *title,
                   			const std::array<int, 2>& top_left_point,
						    const std::array<int, 2>& area,
				   			uint32_t flags): internal_SDL_window{SDL_CreateWindow(title,
				   															      top_left_point[0],
																				  top_left_point[1],
																	   			  area[0],
																	   			  area[1],
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


int SDML::Video::Window::GetDisplayIndex() const
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


SDL_Rect SDML::Video::Window::GetFullscreenDisplayBounds() const
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


SDL_Rect SDML::Video::Window::GetUsableDisplayBounds() const
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


SDL_DisplayMode SDML::Video::Window::GetDisplayMode() const
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


std::string SDML::Video::Window::GetTitle() const { return std::string{SDL_GetWindowTitle(this->internal_SDL_window)}; }


std::string SDML::Video::Window::GetDisplayName() const
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


uint32_t SDML::Video::Window::GetID() const
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


std::array<int, 2> SDML::Video::Window::GetTopLeftpoint() const
{
	std::array<int, 2> point {};

	SDL_GetWindowPosition(this->internal_SDL_window, &point[0], &point[1]);

	return point;
}


std::array<int, 2> SDML::Video::Window::GetArea() const
{
	std::array<std::string, 2> area_names {"width", "height"};
	std::array<int, 2> area {};
	std::array<int, 2> area_in_pixels {};

	SDL_GetWindowSize(this->internal_SDL_window, &area[0], &area[1]);
	SDL_GetWindowSizeInPixels(this->internal_SDL_window, &area_in_pixels[0], &area_in_pixels[1]);

	for(std::size_t i = 0; i < area_names.size(); i++) {
		if(area[i] != area_in_pixels[i]) {
			std::cerr << fmt::format("Warning: For the '{window_name:s}' Window, The {value_name:s} of the client area is different from the {value_name:s} in pixels:\n{capitalized_value_name:s}: {value:d}\nPixel {capitalized_value_name:s}: {value_in_pixels:d}\n",
									 fmt::arg(	  		 "window_name", this->GetTitle()),
									 fmt::arg(	   		  "value_name", area_names[i]),
									 fmt::arg("capitalized_value_name", std::string{static_cast<char>(toupper(area_names[i][0]))} + std::string{area_names[i].begin() + 1, area_names[i].end()}),
									 fmt::arg(				   "value", area[i]),
									 fmt::arg(		 "value_in_pixels", area_in_pixels[i])) << std::endl;
		}
	}

	return area;
}


std::array<int, 2> SDML::Video::Window::GetMinimumArea() const
{
	std::array<int, 2> min_area {};

	SDL_GetWindowMinimumSize(this->internal_SDL_window, &min_area[0], &min_area[1]);

	return min_area;
}


void SDML::Video::Window::SetMinimumArea(const std::array<int, 2>& minimum_area) { SDL_SetWindowMinimumSize(this->internal_SDL_window, minimum_area[0], minimum_area[1]); }


std::array<int, 2> SDML::Video::Window::GetMaximumArea() const
{
	std::array<int, 2> max_area;

	SDL_GetWindowMaximumSize(this->internal_SDL_window, &max_area[0], &max_area[1]);

	return max_area;
}


void SDML::Video::Window::SetMaximumArea(const std::array<int, 2>& maximum_area) { SDL_SetWindowMaximumSize(this->internal_SDL_window, maximum_area[0], maximum_area[1]); }


float SDML::Video::Window::GetBrightness() const { return SDL_GetWindowBrightness(this->internal_SDL_window); }


float SDML::Video::Window::GetOpacity() const
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


std::string SDML::Video::Window::GetPixelFormatName() const
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


bool SDML::Video::Window::CheckWindowInitFlags(uint32_t flags) const { return flags == (flags & SDL_GetWindowFlags(this->internal_SDL_window)); }


bool SDML::Video::Window::CheckWindowInitFlags(const WindowInitFlag& flag) const { return std::to_underlying(flag) == (std::to_underlying(flag) & SDL_GetWindowFlags(this->internal_SDL_window)); }


std::array<int, 2> SDML::Video::Window::GetDisplayArea() const
{
	std::string_view display_name {this->GetDisplayName()};
	SDL_Rect fullscreen_bounds {this->GetFullscreenDisplayBounds()};
	SDL_Rect usable_bounds {this->GetUsableDisplayBounds()};

	if(fullscreen_bounds.w != usable_bounds.w) {
		std::cerr << fmt::format("Warning: difference detected between Fullscreen Width and Usable Width:\nFullscreen Width: {:d}\nUsable Width: {:d}",
								 fullscreen_bounds.w,
								 usable_bounds.w);
	}

	if(fullscreen_bounds.h != usable_bounds.h) {
		std::cerr << fmt::format("Warning: difference detected between Fullscreen Height and Usable Height:\nFullscreen Height: {:d}\nUsable Height: {:d}",
								 fullscreen_bounds.h,
								 usable_bounds.h);
	}

	return std::array<int, 2> {fullscreen_bounds.w, fullscreen_bounds.h};
}


SDML::Video::DisplayOrientation SDML::Video::Window::GetDisplayOrientation() const
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


std::string SDML::Video::Window::GetDisplayModePixelFormatName() const
{
	SDL_DisplayMode tmp {this->GetDisplayMode()};
	return std::string {SDL_GetPixelFormatName(tmp.format)};
}


std::array<int, 2> SDML::Video::Window::GetDisplayModeArea() const
{
	SDL_DisplayMode tmp {this->GetDisplayMode()};
	return std::array<int, 2> {tmp.w, tmp.h};
}


int SDML::Video::Window::GetDisplayModeRefreshRate() const
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
						 const SDML::Video::Window& window)
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

	Misc::Printables display_mode_settings {fmt::format("'{:s}' Display Mode", window.GetDisplayName())};

	std::array<int, 2> display_mode_area {window.GetDisplayModeArea()};
	const auto& [display_mode_width, display_mode_height] = display_mode_area;
	display_mode_settings.add_printable("Area", fmt::format("[Width: {:d}, Height: {:d}]", display_mode_width, display_mode_height));

	display_mode_settings.add_printable("Refresh Rate", window.GetDisplayModeRefreshRate());

	Misc::Printables display_settings {fmt::format("'{:s}' Display", window.GetDisplayName())};

	std::array<int, 2> display_area {window.GetDisplayArea()};
	const auto& [display_width, display_height] = display_area;
	display_settings.add_printable("Area", fmt::format("[Width: {:d}, Height: {:d}]", display_width, display_height));

	display_settings.add_printable(	     "Orientation", display_orientation_string);
	display_settings.add_printable("Pixel Format Name", window.GetDisplayModePixelFormatName());
	display_settings.add_printable(display_mode_settings);

	Misc::Printables window_settings {fmt::format("'{:s}' Window", window.GetTitle())};
	window_settings.add_printable(				   	  "ID", window.GetID());

	std::array<int, 2> point {window.GetTopLeftpoint()};
	const auto& [top_left_x, top_left_y] = point;
	window_settings.add_printable("Top-Left Point", fmt::format("[X: {:d}, Y: {:d}]", top_left_x, top_left_y));

	std::array<int, 2> area {window.GetArea()};
	const auto& [width, height] = area;
	window_settings.add_printable("Area", fmt::format("[Width: {:d}, Height: {:d}]", width, height));

	std::array<int, 2> minimum_area {window.GetMinimumArea()};
	const auto& [minimum_width, minimum_height] = minimum_area;
	window_settings.add_printable("Minimally Allowed Area", fmt::format("[Width: {:d}, Height: {:d}]", minimum_width, minimum_height));

	std::array<int, 2> maximum_area {window.GetMaximumArea()};
	const auto& [maximum_width, maximum_height] = maximum_area;
	window_settings.add_printable("Maximally Allowed Area", fmt::format("[Width: {:d}, Height: {:d}]", maximum_width, maximum_height));

	window_settings.add_printable(		   "Brightness", window.GetBrightness());
	window_settings.add_printable(			  "Opacity", window.GetOpacity());
	window_settings.add_printable(		 "Pixel Format", window.GetPixelFormatName());
	window_settings.add_printable(	  "Window is shown", window.CheckWindowInitFlags(SDML::Video::WindowInitFlag::SHOWN));
	window_settings.add_printable("Window is resizable", window.CheckWindowInitFlags(SDML::Video::WindowInitFlag::RESIZABLE));
	window_settings.add_printable(display_settings);

	std::cout << window_settings;

	return output_stream;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
