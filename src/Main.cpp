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


class GenericEvent
{
private:
	uint32_t type_integer;
	uint32_t timestamp;

public:
	GenericEvent(SDL_CommonEvent& event): type_integer{event.type},
				 					  	  timestamp{event.timestamp} {};

	uint32_t GetTypeInteger() const { return this->type_integer; }

	uint32_t GetTimeStamp() const {return this->timestamp; }
};


std::ostream& operator<<(std::ostream& output, const GenericEvent& event)
{
	Misc::Printables event_description {"Generic Event"};
	event_description.add_printable("Type", fmt::format("{:#x}", event.GetTypeInteger()));
	event_description.add_printable("Timestamp", fmt::format("{:d}", event.GetTimeStamp()));

	return output << event_description.print() << std::endl;
}


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::EVENTS);
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
			while( SDL_PollEvent( &event ) ){

				std::cout << GenericEvent{event.common} << std::endl;

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
