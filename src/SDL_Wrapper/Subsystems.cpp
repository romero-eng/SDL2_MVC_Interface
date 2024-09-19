
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Subsystems.hpp"


void SDL::Init(SDL::SubsystemInitFlags flag)
{
	SDL::Init(std::to_underlying(flag));
}


void SDL::Init(Uint32 flags)
{
	if (SDL_Init(flags) < 0)
	{
		throw fmt::format("\nSDL could not initialize! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}
}


void SDL::Quit(void)
{
	SDL_Quit();
}


Uint32 operator|(SDL::SubsystemInitFlags first_flag,
                 SDL::SubsystemInitFlags second_flag)
{
	return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
