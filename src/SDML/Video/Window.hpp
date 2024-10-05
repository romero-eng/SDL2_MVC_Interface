#ifndef WINDOW_H
#define WINDOW_H

// Custom Code from this project
#include "../../Misc/PrettyPrint.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <array>
#include <vector>
#include <string_view>
#include <iostream>
#include <utility>

namespace SDML
{
	namespace Video
	{
		enum class WindowInitFlag: uint32_t
		{
			FULLSCREEN    	   = SDL_WINDOW_FULLSCREEN,
			OPENGL 	      	   = SDL_WINDOW_OPENGL,
			SHOWN 	      	   = SDL_WINDOW_SHOWN,
			HIDDEN 	      	   = SDL_WINDOW_HIDDEN,
			BORDERLESS    	   = SDL_WINDOW_BORDERLESS,
			RESIZABLE     	   = SDL_WINDOW_RESIZABLE,
			MINIMIZED     	   = SDL_WINDOW_MINIMIZED,
			MAXIMIZED  	  	   = SDL_WINDOW_MAXIMIZED,
			MOUSE_GRABBED 	   = SDL_WINDOW_MOUSE_GRABBED,
			INPUT_FOCUS   	   = SDL_WINDOW_INPUT_FOCUS,
			MOUSE_FOCUS   	   = SDL_WINDOW_MOUSE_FOCUS,
			FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
			FOREIGN 		   = SDL_WINDOW_FOREIGN,
			ALLOW_HIGHDPI 	   = SDL_WINDOW_ALLOW_HIGHDPI,
			MOUSE_CAPTURE	   = SDL_WINDOW_MOUSE_CAPTURE,
			ALWAYS_ON_TOP 	   = SDL_WINDOW_ALWAYS_ON_TOP,
			SKIP_TASKBAR 	   = SDL_WINDOW_SKIP_TASKBAR,
			UTILITY 		   = SDL_WINDOW_UTILITY,
			TOOLTIP 		   = SDL_WINDOW_TOOLTIP,
			POPUP_MENU 		   = SDL_WINDOW_POPUP_MENU,
			KEYBOARD_GRABBED   = SDL_WINDOW_KEYBOARD_GRABBED,
			VULKAN 			   = SDL_WINDOW_VULKAN,
			METAL 			   = SDL_WINDOW_METAL,
			INPUT_GRABBED 	   = SDL_WINDOW_INPUT_GRABBED
		};

		enum class FlashOperation
		{
    		CANCEL,
    		BRIEFLY,
    		UNTIL_FOCUSED
		};

		enum class DisplayOrientation
		{
			UNKNOWN,
            LANDSCAPE,
            LANDSCAPE_FLIPPED,
            PORTRAIT,
            PORTRAIT_FLIPPED
		};

		class Window
		{
		private:

			SDL_Window* internal_SDL_window;

			int GetDisplayIndex();

			SDL_Rect GetFullscreenDisplayBounds();

			SDL_Rect GetUsableDisplayBounds();

			SDL_DisplayMode GetDisplayMode();

		public:

			Window(const char *title,
				   const std::array<int, 2>& area);

			Window(const char *title,
				   const std::array<int, 2>& top_left_point,
				   const std::array<int, 2>& area);

			Window(const char *title,
				   const std::array<int, 2>& area,
				   const WindowInitFlag& flag);

			Window(const char *title,
                   const std::array<int, 2>& top_left_point,
				   const std::array<int, 2>& area,
				   const WindowInitFlag& flag);

			Window(const char *title,
				   const std::array<int, 2>& area,
				   uint32_t flags);

			Window(const char *title,
                   const std::array<int, 2>& top_left_point,
				   const std::array<int, 2>& area,
				   uint32_t flags);

			Window(Window&) = delete;
			
			Window& operator=(Window&) = delete;

			~Window();

			std::string GetTitle();

			std::string GetDisplayName();

			uint32_t GetID();

			std::array<int, 2> GetTopLeftpoint();

			std::array<int, 2> GetArea();

			std::array<int, 2> GetMinimumArea();

			std::array<int, 2> GetMaximumArea();

			float GetBrightness();

			float GetOpacity();

			std::string GetPixelFormatName();

			bool CheckWindowInitFlags(uint32_t flags);

			bool CheckWindowInitFlags(const WindowInitFlag& flag);

			void SetMinimumArea(const std::array<int, 2>& minimum_area);

			void SetMaximumArea(const std::array<int, 2>& maximum_area);

			std::array<int, 2> GetDisplayArea();

			DisplayOrientation GetDisplayOrientation();

			std::string GetDisplayModePixelFormatName();

			std::array<int, 2> GetDisplayModeArea();

			int GetDisplayModeRefreshRate();

			/*Not sure this function actually does anything, but I'll
			leave it for the sake of completeness.*/
			void Flash(FlashOperation operation);

			SDL_Window* Access_SDL_Backend();
		};
	}
}

uint32_t operator|(const SDML::Video::WindowInitFlag& first_flag,
				   const SDML::Video::WindowInitFlag& second_flag);

uint32_t operator|(const SDML::Video::WindowInitFlag& first_flag, uint32_t second_flag);

uint32_t operator|(uint32_t first_flag, const SDML::Video::WindowInitFlag& second_flag);

std::ostream& operator<<(std::ostream& output_stream, SDML::Video::Window& window);

#endif
