#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "Logging/Logfile.hpp"
#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Surface.hpp"
#include "SDML/Video/Renderer.hpp"
#include "SDML/Video/Texture.hpp"
#include "SDML/Events/MouseMotionEvent.hpp"
#include "SDML/Events/MouseButtonEvent.hpp"
#include "SDML/Events/MouseWheelEvent.hpp"
#include "SDML/Events/KeyboardEvent.hpp"
#include "SDML/Events/WindowEvent.hpp"
#include "SDML/Events/QuitEvent.hpp"
#include "SDML/Events/GenericEvent.hpp"
#include "SDML/Events/EventMisc.hpp"

// C++ Standard Libraries
#include <filesystem>
#include <iostream>
#include <chrono>
#include <memory>


constexpr std::string WINDOW_TITLE {"Test"};
constexpr std::array<int, 2> WINDOW_AREA {640, 480};
Logging::Logfile MainLogFile {std::filesystem::current_path().parent_path().parent_path(), "Test"};


int main( int argc, char* args[] )
{

	std::chrono::time_point<std::chrono::system_clock> init_time_point {SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS)};
	SDML::Image::Initialize(0);

	try {

		SDML::Video::windows.push_back(SDML::Video::Window {WINDOW_TITLE, WINDOW_AREA, SDML::Video::Window::InitFlag::RESIZABLE});
		SDML::Video::Renderer renderer{SDML::Video::windows[0]};
		SDML::Video::Texture hello_world_texture {renderer, std::filesystem::current_path().parent_path().parent_path()/"res"/"hello_world.bmp"};
		renderer.Copy(hello_world_texture);
		renderer.Update();
		
		SDL_Event event;
		std::unique_ptr<SDML::Events::Event> current_event;
		bool quit = false;

		while(!quit) {
			while(SDL_PollEvent(&event)){

				current_event = SDML::Events::SDL_to_SDML(event, init_time_point);

				quit = current_event->Quit();
			}
		}
		
		current_event = nullptr;

	}
	catch(const std::exception& error_message)
	{
		std::cerr << error_message.what() << std::endl;
	}

	SDML::Image::Quit();
	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
