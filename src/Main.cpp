#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDML/Subsystem.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>

// C++ Standard Libraries
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

		class Window
		{
		private:

			SDL_Window* internal_SDL_window;

		public:

			Window(const char *title,
				   int width,
                   int height): Window(title,
				   					   SDL_WINDOWPOS_UNDEFINED,
									   SDL_WINDOWPOS_UNDEFINED,
									   width,
									   height,
									   0) {}

			Window(const char *title,
				   int x, int y,
				   int width,
                   int height): Window(title,
				   					   x, y,
									   width,
									   height,
									   0) {}

			Window(const char *title,
				   int width,
                   int height,
				   WindowFlag flag): Window(title,
				   							SDL_WINDOWPOS_UNDEFINED,
											SDL_WINDOWPOS_UNDEFINED,
										 	width,
										 	height,
										 	std::to_underlying(flag)) {}

			Window(const char *title,
                   int x, int y,
				   int width,
                   int height,
				   WindowFlag flag): Window(title,
				   							x, y,
										 	width,
										 	height,
										 	std::to_underlying(flag)) {}

			Window(const char *title,
				   int width,
                   int height,
				   Uint32 flags): Window(title,
				   						 SDL_WINDOWPOS_UNDEFINED,
										 SDL_WINDOWPOS_UNDEFINED,
										 width,
										 height,
										 flags) {}

			Window(const char *title,
                   int x, int y,
				   int width,
                   int height,
				   Uint32 flags): internal_SDL_window{SDL_CreateWindow(title,
				   													   x, y,
																	   width,
																	   height,
																	   flags)} {}

			Window(Window&) = delete;
			
			Window& operator=(Window&) = delete;

			/*Not sure this function actually does anything, but I'll
			leave it for the sake of completeness.*/
			void Flash(FlashOperation operation)
			{
				SDL_FlashOperation internal_SDL_operation;
				switch(operation)
				{
					case FlashOperation::CANCEL:
						internal_SDL_operation = SDL_FLASH_CANCEL;
					case FlashOperation::BRIEFLY:
						internal_SDL_operation = SDL_FLASH_BRIEFLY;
					case FlashOperation::UNTIL_FOCUSED:
						internal_SDL_operation = SDL_FLASH_UNTIL_FOCUSED;
				}

				if(SDL_FlashWindow(this->internal_SDL_window, internal_SDL_operation) < 0)
				{
					throw fmt::format("Could not Flash the '{:s}' Window: {:s}",
									  SDL_GetWindowTitle(this->internal_SDL_window),
									  SDL_GetError());
				}
			}

			~Window()
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

		};
	}
}


Uint32 operator|(const SDML::Video::WindowFlag& first_flag,
				 const SDML::Video::WindowFlag& second_flag)
{ return std::to_underlying(first_flag) | std::to_underlying(second_flag) ; }


Uint32 operator|(const SDML::Video::WindowFlag& first_flag,
				 Uint32 second_flag)
{ return std::to_underlying(first_flag) | second_flag ; }


Uint32 operator|(Uint32 first_flag,
				 const SDML::Video::WindowFlag& second_flag)
{ return first_flag | std::to_underlying(second_flag) ; }


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);

	try
	{
		SDML::Video::Window windowTest {"Test", 640, 480};
		windowTest.Flash(SDML::Video::FlashOperation::UNTIL_FOCUSED);

		SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
