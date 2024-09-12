
#include <filesystem>
namespace fs = std::filesystem;

const fs::path RESOURCE_DIRECTORY { fs::current_path().parent_path().parent_path()/"res" };
