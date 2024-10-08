#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Texture.hpp"


SDML::Video::Texture::Texture(const char* name,
                              Renderer& renderer,
                              uint32_t pixel_format,
                              const TextureAccess& access,
                              const std::array<int, 2>& area): name{std::string{name}},
                                                               renderer_name{std::string{renderer.GetName()}},
                                                               internal_SDL_texture{SDL_CreateTexture(renderer.Access_SDL_Backend(),
                                                                                                      pixel_format,
                                                                                                      std::to_underlying(access),
                                                                                                      area[0],
                                                                                                      area[1])} {}

SDML::Video::Texture::Texture(const char* name,
                              Renderer& renderer,
                              SDL_Texture* texture): name{std::string{name}},
                                                     renderer_name{renderer.GetName()},
                                                     internal_SDL_texture{texture} {};


SDML::Video::Texture::Texture(const char* name,
                              SDL_Texture* texture): name{std::string{name}},
                                                     renderer_name{std::nullopt},
                                                     internal_SDL_texture{texture} {}


SDML::Video::Texture::~Texture() { SDL_DestroyTexture(this->internal_SDL_texture); }


std::string SDML::Video::Texture::GetName() const { return this->name; }


std::optional<std::string> SDML::Video::Texture::GetContextName() const { return this->renderer_name; }


std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Texture& texture)
{
    Misc::Printables printables {fmt::format("'{:s}' Texture", texture.GetName())};

    std::optional<std::string> context_name {texture.GetContextName()};
    if(context_name.has_value()) {
        printables.add_printable("Rendering Context", context_name.value());
    }

    output << printables.print();

    return output;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
