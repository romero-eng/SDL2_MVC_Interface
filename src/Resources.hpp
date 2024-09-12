
#include <filesystem>
namespace fs = std::filesystem;

namespace Resources
{

const fs::path RESOURCE_DIRECTORY { fs::current_path().parent_path().parent_path()/"res" };
fs::path bitmap_path { RESOURCE_DIRECTORY/"hello_world.bmp" };

SDL::Surface* HelloWorldSurface {SDL::Load_BMP({ RESOURCE_DIRECTORY/"hello_world.bmp" })};

}
