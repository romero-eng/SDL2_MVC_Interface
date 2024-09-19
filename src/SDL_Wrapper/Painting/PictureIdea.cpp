
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "PictureIdea.hpp"


SDL_Surface* SDL::Painting::PictureIdea::LoadSurfaceFromFile(const fs::path& image_path)
{
	if(!fs::exists(image_path))
	{
		throw fmt::format("The '{:s}' Image file does not exist", image_path.string().c_str());
	}

	if(!fs::is_regular_file(image_path))
	{
		throw fmt::format("The '{:s}' Image file does not seem to be a regular file", image_path.string().c_str());
	}

	SDL_Surface* tmpSurface {IMG_Load(image_path.string().c_str())};

	return tmpSurface;
}


SDL::Painting::PictureIdea::~PictureIdea() {}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
