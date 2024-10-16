#ifndef EVENT_H
#define EVENT_H

// Custom Code from this project
#include "../Misc/PrettyPrint.hpp"

// Third-Party APIs
#include <SDL2/SDL.h>

// C++ Standard Libraries
#include <chrono>


class GenericEvent
{
private:

	uint32_t type_integer;
	std::chrono::time_point<std::chrono::system_clock> timestamp;

public:

	GenericEvent(const SDL_CommonEvent& event,
				 const std::chrono::time_point<std::chrono::system_clock> init_time_point);

	uint32_t GetTypeInteger() const;

	std::chrono::time_point<std::chrono::system_clock> GetTimeStamp() const;
};


class QuitEvent
{
private:

	std::chrono::time_point<std::chrono::system_clock> timestamp;

public:

	QuitEvent(const SDL_QuitEvent& event,
			  const std::chrono::time_point<std::chrono::system_clock> init_time_point);

	std::chrono::time_point<std::chrono::system_clock> GetTimeStamp() const;
};


std::ostream& operator<<(std::ostream& output,
						 const GenericEvent& event);


std::ostream& operator<<(std::ostream& output,
						 const QuitEvent& event);

#endif
