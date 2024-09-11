
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Main.hpp"
#include <fmt/format.h>


void SDL::Init(Uint32 flags)
{
	int initialization_status{ SDL_Init(flags) };

	if (initialization_status < 0)
	{
		throw fmt::format("\nSDL could not initialize! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}
}

void SDL::Quit(void)
{
	SDL_Quit();
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
