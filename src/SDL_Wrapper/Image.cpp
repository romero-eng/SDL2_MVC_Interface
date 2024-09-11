
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Image.hpp"


Uint32 SDL::MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(format, r, g, b);
}


#endif
