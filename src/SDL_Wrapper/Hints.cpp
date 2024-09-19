
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Hints.hpp"


void SDL::SetHint(const Hints& hint_name, const char* value, const char* failure_msg)
{
	const char name {static_cast<char>(std::to_underlying(hint_name))}; 

	if(!(SDL_SetHint(&name, value)))
	{
		std::cerr << failure_msg << "\n";
	}
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
