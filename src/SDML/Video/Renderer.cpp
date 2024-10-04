#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Renderer.hpp"

SDML::Video::Renderer::Renderer(Window& window): internal_SDL_renderer{SDL_CreateRenderer(window.Access_SDL_Backend(),
                                                                                          -1,
                                                                                          0)} {};

SDML::Video::Renderer::~Renderer() { SDL_DestroyRenderer(this->internal_SDL_renderer); }

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
