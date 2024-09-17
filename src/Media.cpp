
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "Media.hpp"
#include <filesystem>
namespace fs = std::filesystem;


Media::Resources Media::LoadResources(SDL::GPU_Painting::GPU_Paintbrush* renderer)
{
    fs::path RESOURCE_DIRECTORY { fs::current_path().parent_path().parent_path()/"res" };

    return Media::Resources {SDL::CPU_Images::LoadFromFile(RESOURCE_DIRECTORY/"hello_world.bmp"),
                             SDL::GPU_Images::LoadFromFile(RESOURCE_DIRECTORY/"texture.png", renderer)};
}

void Media::FreeResources(Media::Resources loaded_resources)
{
    SDL::CPU_Images::FreeSurface(loaded_resources.helloWorld);
    SDL::GPU_Images::Destroy(loaded_resources.GPU_PaintingPNG);
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
