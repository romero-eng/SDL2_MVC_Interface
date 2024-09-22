
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "FileLoading.hpp"


void SDL::Painting::Image::InitLoading(FileTypes file_type) { SDL::Painting::Image::InitLoading(std::to_underlying(file_type)); }


void SDL::Painting::Image::InitLoading(Uint32 file_types)
{
	if(!( static_cast<Uint32>(IMG_Init(static_cast<int>(file_types))) & file_types ))
	{
		throw fmt::format("SDL Pictures could not be initialized: {:s}\n", IMG_GetError());
	}
}


bool SDL::Painting::Image::QueryLoadingInit() { return IMG_Init(0) > 0; }


void SDL::Painting::Image::QuitLoading(void) { IMG_Quit(); }


Uint32 operator|(SDL::Painting::Image::FileTypes first_flag, SDL::Painting::Image::FileTypes second_flag) { return std::to_underlying(first_flag) | std::to_underlying(second_flag); }

Uint32 operator|(						  Uint32 first_flag, SDL::Painting::Image::FileTypes second_flag) { return first_flag | std::to_underlying(second_flag); }

Uint32 operator|(SDL::Painting::Image::FileTypes first_flag, Uint32 second_flag) { return std::to_underlying(first_flag) | second_flag; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
