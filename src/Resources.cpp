
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Resources.hpp"
#include "SDL_Wrapper/Image.hpp"
#include <filesystem>
namespace fs = std::filesystem;


Resources::Surfaces Resources::LoadResources(void)
{
    fs::path RESOURCE_DIRECTORY { fs::current_path().parent_path().parent_path()/"res" };

    return Resources::Surfaces {SDL::Load_BMP({ RESOURCE_DIRECTORY/"hello_world.bmp" })};
}

void Resources::FreeResources(Resources::Surfaces surface_resources)
{
    SDL::FreeSurface(surface_resources.helloWorld);
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
