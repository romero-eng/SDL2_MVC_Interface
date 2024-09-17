
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Media.hpp"
#include <filesystem>
namespace fs = std::filesystem;


Media::Resources Media::LoadResources(SDL::Rendering::Renderer* renderer)
{
    fs::path RESOURCE_DIRECTORY { fs::current_path().parent_path().parent_path()/"res" };

    return Media::Resources {SDL::Surfaces::Load_BMP(RESOURCE_DIRECTORY/"hello_world.bmp"),
                             IMG::LoadTexture(RESOURCE_DIRECTORY/"texture.png", renderer)};
}

void Media::FreeResources(Media::Resources loaded_resources)
{
    SDL::Surfaces::FreeSurface(loaded_resources.helloWorld);
    SDL::Textures::Destroy(loaded_resources.renderingPNG);
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
