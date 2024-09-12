
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Media.hpp"
#include "SDL_Wrapper/Image.hpp"
#include <filesystem>
namespace fs = std::filesystem;


Media::Resources Media::LoadResources(void)
{
    fs::path RESOURCE_DIRECTORY { fs::current_path().parent_path().parent_path()/"res" };

    return Media::Resources {SDL::Load_BMP({ RESOURCE_DIRECTORY/"hello_world.bmp" })};
}

void Media::FreeResources(Media::Resources surface_resources)
{
    SDL::FreeSurface(surface_resources.helloWorld);
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
