#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Texture.hpp"


SDML::Video::Texture::Texture(const char* name,
                              Renderer& renderer,
                              uint32_t pixel_format,
                              const TextureAccess& access,
                              const std::array<int, 2>& area): name{std::string{name}},
                                                               renderer_name{std::string_view{renderer.GetName()}},
                                                               internal_SDL_texture{SDL_CreateTexture(renderer.Access_SDL_Backend(),
                                                                                                      pixel_format,
                                                                                                      std::to_underlying(access),
                                                                                                      area[0],
                                                                                                      area[1])} {}


SDML::Video::Texture::Texture(const char* name,
                              SDL_Texture* texture): name{std::string{name}},
                                                     renderer_name{std::nullopt},
                                                     internal_SDL_texture{texture} {}


SDML::Video::Texture::~Texture() { SDL_DestroyTexture(this->internal_SDL_texture); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
