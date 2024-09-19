
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Subsystems.hpp"


void SDL::Init(SDL::SubsystemInitFlags subsystem_flag)
{
	SDL::Init(std::to_underlying(subsystem_flag));
}


void SDL::Init(SubsystemInitFlags subsystem_flag,
               Painting::ImageFileTypes file_type)
{
	SDL::Init(subsystem_flag);
	Painting::InitImageLoading(file_type);
}


void SDL::Init(SubsystemInitFlags subsystem_flag,
               Uint32 file_types)
{
	SDL::Init(subsystem_flag);
	Painting::InitImageLoading(file_types);
}


void SDL::Init(Uint32 subsystem_flags)
{
	if (SDL_Init(subsystem_flags) < 0)
	{
		throw fmt::format("\nSDL could not initialize! SDL_Error:\n\n{:s}\n\n", SDL_GetError() );
	}
}


void SDL::Init(Uint32 subsystem_flags,
               Painting::ImageFileTypes file_type)
{
	SDL::Init(subsystem_flags);
	Painting::InitImageLoading(file_type);
}


void SDL::Init(Uint32 subsystem_flags,
               Uint32 file_types)
{
	SDL::Init(subsystem_flags);
	Painting::InitImageLoading(file_types);
}


void SDL::Quit(void)
{
	if(Painting::QueryImageLoadingInitialization())
	{
		Painting::QuitImageLoading();
	}
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
