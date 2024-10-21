#ifndef WINDOW_H
#define WINDOW_H

// Custom Code from this project
#include "../../Misc/PrettyPrint.hpp"
#include "Surface.hpp"

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
		class Surface;

		class Window
		{
		public:

			enum class InitFlag: uint32_t
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

		private:

			SDL_Window* internal_SDL_window;
			
			bool internal_SDL_window_ownership;

			int GetDisplayIndex() const;

			SDL_Rect GetFullscreenDisplayBounds() const;

			SDL_Rect GetUsableDisplayBounds() const;

			SDL_DisplayMode GetDisplayMode() const;

		public:

			Window(const std::string& title,
				   const std::array<int, 2>& area,
				   const InitFlag& flag);

			Window(const std::string& title,
				   const std::array<int, 2>& area,
				   uint32_t flags);

			Window(const std::string& title,
				   const std::array<int, 2>& area);

			Window(const std::string& title,
				   const std::pair<std::array<int, 2>, std::array<int, 2>>& rectangle,
				   const InitFlag& flag);

			Window(const std::string& title,
				   const std::pair<std::array<int, 2>, std::array<int, 2>>& rectangle,
				   uint32_t flags);

			Window(const std::string& title,
				   const std::pair<std::array<int, 2>, std::array<int, 2>>& rectangle);

			Window(const char *title,
				   const std::array<int, 2>& area,
				   const InitFlag& flag);

			Window(const char *title,
				   const std::array<int, 2>& area,
				   uint32_t flags);

			Window(const char *title,
				   const std::array<int, 2>& area);

			Window(const std::array<int, 2>& area);

			Window(const char *title,
				   const std::pair<std::array<int, 2>, std::array<int, 2>>& rectangle,
				   const InitFlag& flag);

			Window(const char *title,
				   const std::pair<std::array<int, 2>, std::array<int, 2>>& rectangle,
				   uint32_t flags);

			Window(const char *title,
				   const std::pair<std::array<int, 2>, std::array<int, 2>>& rectangle);

			Window(const std::pair<std::array<int, 2>, std::array<int, 2>>& rectangle);

			Window();

			Window(const Window& windowToCopy);
			
			Window& operator=(const Window& windowToCopy);

			Window(Window&& windowToMove) noexcept;

			Window& operator=(Window&& windowToMove);

			~Window();

			std::string to_string() const;

			std::string GetTitle() const;

			std::string GetDisplayName() const;

			uint32_t GetID() const;

			std::array<int, 2> GetTopLeftpoint() const;

			std::array<int, 2> GetArea() const;

			std::array<int, 2> GetMinimumArea() const;
			
			void SetMinimumArea(const std::array<int, 2>& minimum_area);

			std::array<int, 2> GetMaximumArea() const;

			void SetMaximumArea(const std::array<int, 2>& maximum_area);

			float GetBrightness() const;

			float GetOpacity() const;

			std::string GetPixelFormatName() const;

			bool CheckInitFlags(uint32_t flags) const;

			bool CheckInitFlags(const InitFlag& flag) const;

			std::array<int, 2> GetDisplayArea() const;

			DisplayOrientation GetDisplayOrientation() const;

			std::string GetDisplayModePixelFormatName() const;

			std::array<int, 2> GetDisplayModeArea() const;

			int GetDisplayModeRefreshRate() const;

			/*Not sure this function actually does anything, but I'll
			leave it for the sake of completeness.*/
			void Flash(FlashOperation operation);

			void BlitOntoSurface(Surface& src,
								 const std::pair<std::array<int, 2>, std::array<int, 2>>& dst_rect_info,
								 const std::pair<std::array<int, 2>, std::array<int, 2>>& src_rect_info);

			void BlitOntoSurface(Surface& src);

			void DrawRect(const std::pair<std::array<int, 2>, std::array<int, 2>>& rect_info,
                          const std::array<uint8_t, 3>& color);

			void DrawRects(const std::vector<std::pair<std::array<int, 2>, std::array<int, 2>>>& rects_info,
                           const std::array<uint8_t, 3>& color);

			void Update();

			void UpdateRects(const std::vector<std::pair<std::array<int, 2>, std::array<int, 2>>>& rects_info);

			SDL_Window* Access_SDL_Backend();
		};

		extern std::vector<Window> windows;

		Window FindWindow(uint32_t windowID);

	}
}

uint32_t operator|(const SDML::Video::Window::InitFlag& first_flag,
				   const SDML::Video::Window::InitFlag& second_flag);

uint32_t operator|(const SDML::Video::Window::InitFlag& first_flag, uint32_t second_flag);

uint32_t operator|(uint32_t first_flag,
				   const SDML::Video::Window::InitFlag& second_flag);

std::ostream& operator<<(std::ostream& output_stream,
						 const SDML::Video::Window& window);

#endif
