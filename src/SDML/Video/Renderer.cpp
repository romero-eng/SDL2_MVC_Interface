#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Renderer.hpp"

SDML::Video::Renderer::Renderer(Window& window,
                                uint32_t flags): internal_SDL_renderer{SDL_CreateRenderer(window.Access_SDL_Backend(),
                                                                                          -1,
                                                                                          flags)} {};


SDML::Video::Renderer::Renderer(Window& window,
                                RendererInitFlag flag): Renderer{window, std::to_underlying(flag)} {};


SDML::Video::Renderer::Renderer(Window& window): Renderer{window, 0} {};


SDML::Video::Renderer::~Renderer() { SDL_DestroyRenderer(this->internal_SDL_renderer); }


std::string SDML::Video::Renderer::GetName()
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for Renderer: {:s}",
                                             SDL_GetError()));
    }

    return std::string {tmp.name};
}


int SDML::Video::Renderer::GetMaxTextureWidth()
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for Renderer: {:s}",
                                             SDL_GetError()));
    }

    return tmp.max_texture_width;
}


int SDML::Video::Renderer::GetMaxTextureHeight()
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for Renderer: {:s}",
                                             SDL_GetError()));
    }

    return tmp.max_texture_height;
}





uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, const SDML::Video::RendererInitFlag& second_flag) { return std::to_underlying(first_flag) | std::to_underlying(second_flag); }


uint32_t operator|(uint32_t first_flag, const SDML::Video::RendererInitFlag& second_flag) { return first_flag | std::to_underlying(second_flag); }


uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, uint32_t second_flag) { return std::to_underlying(first_flag) | second_flag; }


std::ostream& operator<<(std::ostream& output,
                         SDML::Video::Renderer& renderer)
{
    Misc::Printables printable {fmt::format("'{:s}' Renderer", renderer.GetName())};
    printable.add_printable( "Maximum Texture Width", renderer.GetMaxTextureWidth());
    printable.add_printable("Maximum Texture Height", renderer.GetMaxTextureHeight());

    output << printable;

    return output;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
