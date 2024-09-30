#ifndef WINDOW_H
#define WINDOW_H

// Third-party Libraries
#include <SDL2/SDL.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <string_view>
#include <iostream>
#include <utility>

namespace SDML
{
	namespace Video
	{
		enum class WindowFlag: uint32_t
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
				   int width,
                   int height);

			Window(const char *title,
				   int x, int y,
				   int width,
                   int height);

			Window(const char *title,
				   int width,
                   int height,
				   WindowFlag flag);

			Window(const char *title,
                   int x, int y,
				   int width,
                   int height,
				   WindowFlag flag);

			Window(const char *title,
				   int width,
                   int height,
				   Uint32 flags);

			Window(const char *title,
                   int x, int y,
				   int width,
                   int height,
				   Uint32 flags);

			Window(Window&) = delete;
			
			Window& operator=(Window&) = delete;

			std::string_view GetTitle();

			std::string_view GetDisplayName();

			Uint32 GetID();

			int GetX();

			int GetY();

			int GetWidth();

			int GetMinimumWidth();

			int GetMaximumWidth();

			int GetHeight();

			int GetMinimumHeight();

			int GetMaximumHeight();

			float GetBrightness();

			float GetOpacity();

			std::string_view GetPixelFormatName();

			bool CheckWindowFlags(Uint32 flags);

			bool CheckWindowFlags(WindowFlag flag);

			void SetMinimumArea(int min_width, int min_height);

			void SetMaximumArea(int max_width, int max_height);

			int GetDisplayWidth();

			int GetDisplayHeight();

			DisplayOrientation GetDisplayOrientation();

			std::string_view GetDisplayModePixelFormatName();

			int GetDisplayModeWidth();

			int GetDisplayModeHeight();

			int GetDisplayModeRefreshRate();

			/*Not sure this function actually does anything, but I'll
			leave it for the sake of completeness.*/
			void Flash(FlashOperation operation);

			~Window();

			SDL_Window* AccessInternalWindow();
		};
	}
}


Uint32 operator|(const SDML::Video::WindowFlag& first_flag,
				 const SDML::Video::WindowFlag& second_flag);


Uint32 operator|(const SDML::Video::WindowFlag& first_flag,
				 Uint32 second_flag);


Uint32 operator|(Uint32 first_flag,
				 const SDML::Video::WindowFlag& second_flag);

#endif
