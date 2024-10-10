#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Surface.hpp"


SDML::Video::Surface::Surface(Window& window,
                              const std::filesystem::path& image_file): name{image_file.stem()},
                                                                        internal_SDL_surface{SDL_ConvertSurface(IMG_Load(image_file.string().c_str()),
                                                                                                                SDL_GetWindowSurface(window.Access_SDL_Backend())->format,
                                                                                                                0)} {}


SDML::Video::Surface::~Surface() { SDL_FreeSurface(this->internal_SDL_surface); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
