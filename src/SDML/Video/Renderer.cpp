#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Renderer.hpp"



#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
