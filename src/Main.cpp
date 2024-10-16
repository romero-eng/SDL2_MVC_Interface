#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Surface.hpp"
#include "SDML/Video/Renderer.hpp"
#include "SDML/Video/Texture.hpp"
#include "Misc/PrettyPrint.hpp"

// C++ Standard Libraries
#include <filesystem>
#include <iostream>
#include <chrono>


class GenericEvent
{
private:

	uint32_t type_integer;
	std::chrono::time_point<std::chrono::system_clock> timestamp;

public:

	GenericEvent(const SDL_CommonEvent& event,
				 const std::chrono::time_point<std::chrono::system_clock> init_time_point): type_integer{event.type},
				 																			timestamp {init_time_point + std::chrono::duration<int, std::milli>(event.timestamp)} {};

	uint32_t GetTypeInteger() const { return this->type_integer; }

	std::chrono::time_point<std::chrono::system_clock> GetTimeStamp() const { return this->timestamp; }
};


class QuitEvent
{
private:

	std::chrono::time_point<std::chrono::system_clock> timestamp;

public:

	QuitEvent(const SDL_QuitEvent& event,
			  const std::chrono::time_point<std::chrono::system_clock> init_time_point): timestamp{init_time_point + std::chrono::duration<int, std::milli>(event.timestamp)} {};

	std::chrono::time_point<std::chrono::system_clock> GetTimeStamp() const { return this->timestamp; }
};


std::ostream& operator<<(std::ostream& output,
						 const GenericEvent& event)
{
	Misc::Printables event_description {"Generic Event"};
	event_description.add_printable("Type", fmt::format("{:#x}", event.GetTypeInteger()));
	event_description.add_printable("Timestamp", Misc::time_to_string(event.GetTimeStamp()));

	return output << event_description.print() << std::endl;
}


std::ostream& operator<<(std::ostream& output,
						 const QuitEvent& event)
{
	Misc::Printables event_description {"Quit Event"};
	event_description.add_printable("Timestamp", Misc::time_to_string(event.GetTimeStamp()));

	return output << event_description.print() << std::endl;
}


int main( int argc, char* args[] )
{

	std::chrono::time_point<std::chrono::system_clock> init_time_point {SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS)};
	SDML::Image::Initialize(0);

	try
	{
		SDML::Video::Window windowTest {"Test", 
										std::array<int, 2> {640, 480},
										SDML::Video::WindowInitFlag::RESIZABLE};

		std::cout << std::hex;

		SDL_Event event;
		bool quit = false;
		while(!quit) {
			while(SDL_PollEvent(&event)){

				switch(event.type) {
					case SDL_QUIT:
						std::cout << QuitEvent(event.quit, init_time_point) << std::endl;
						break;
					default:
						std::cout << GenericEvent{event.common, init_time_point} << std::endl;
						break;
				}

				if(event.type == SDL_QUIT) {
					quit = true;
				}
			}
		}

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
