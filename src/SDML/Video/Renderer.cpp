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


int SDML::Video::Renderer::GetWidth()
{
    int width {};
    if(SDL_GetRendererOutputSize(this->internal_SDL_renderer, &width, nullptr) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve the width for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return width;
}


int SDML::Video::Renderer::GetHeight()
{
    int height {};
    if(SDL_GetRendererOutputSize(this->internal_SDL_renderer, nullptr, &height) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve the width for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return height;
}


std::array<uint8_t, 4> SDML::Video::Renderer::GetDrawingColor()
{
    std::array<uint8_t, 4> color {};

    if(SDL_GetRenderDrawColor(this->internal_SDL_renderer, &color[0], &color[1], &color[2], &color[3]) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve the drawing color for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return color;
}


SDML::Video::BlendMode SDML::Video::Renderer::GetBlendMode()
{
    SDL_BlendMode internal_blend_mode;
    BlendMode visible_blend_mode;
    if(SDL_GetRenderDrawBlendMode(this->internal_SDL_renderer, &internal_blend_mode) < 0) {
        throw std::runtime_error(fmt::format("Could not get the Blend Mode for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    switch(internal_blend_mode)
    {
        case SDL_BlendMode::SDL_BLENDMODE_NONE:
            visible_blend_mode = BlendMode::REPLACE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_BLEND:
            visible_blend_mode = BlendMode::ALPHA;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_ADD:
            visible_blend_mode = BlendMode::ADDITIVE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_MOD:
            visible_blend_mode = BlendMode::MODULATE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_MUL:
            visible_blend_mode = BlendMode::MODULATE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_INVALID:
            visible_blend_mode = BlendMode::INVALID;
            break;
    }

    return visible_blend_mode;
}


int SDML::Video::Renderer::GetMaxTextureWidth()
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return tmp.max_texture_width;
}


int SDML::Video::Renderer::GetMaxTextureHeight()
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return tmp.max_texture_height;
}


std::vector<std::string> SDML::Video::Renderer::GetTextureFormats()
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
    
    std::size_t num_texture_formats {static_cast<std::size_t>(tmp.num_texture_formats)};
    std::vector<std::string> texture_formats (num_texture_formats);

    for(std::size_t index = 0; index < num_texture_formats; index++) {
        texture_formats[index] = std::string {SDL_GetPixelFormatName(tmp.texture_formats[index])};
    }

    return texture_formats;
}


bool SDML::Video::Renderer::CheckInitFlags(uint32_t flags)
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return flags == (flags & tmp.flags); 
}


bool SDML::Video::Renderer::CheckInitFlags(RendererInitFlag flag) { return this->CheckInitFlags(std::to_underlying(flag)); } 


uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, const SDML::Video::RendererInitFlag& second_flag) { return std::to_underlying(first_flag) | std::to_underlying(second_flag); }


uint32_t operator|(uint32_t first_flag, const SDML::Video::RendererInitFlag& second_flag) { return first_flag | std::to_underlying(second_flag); }


uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, uint32_t second_flag) { return std::to_underlying(first_flag) | second_flag; }


std::ostream& operator<<(std::ostream& output,
                         SDML::Video::Renderer& renderer)
{
    SDML::Video::BlendMode blend_mode {renderer.GetBlendMode()};
    std::string blend_mode_string {}; 

    switch(blend_mode)
    {
        case SDML::Video::BlendMode::REPLACE:
            blend_mode_string = "Replace";
            break;
        case SDML::Video::BlendMode::ALPHA:
            blend_mode_string = "Alpha";
            break;
        case SDML::Video::BlendMode::ADDITIVE:
            blend_mode_string = "Additive";
            break;
        case SDML::Video::BlendMode::MODULATE:
            blend_mode_string = "Modulate";
            break;
        case SDML::Video::BlendMode::MULTIPLY:
            blend_mode_string = "Multiply";
            break;
        case SDML::Video::BlendMode::INVALID:
            blend_mode_string = "Invalid";
            break;
    }

    std::array<uint8_t, 4> drawing_color {renderer.GetDrawingColor()};

    Misc::Printables printables {fmt::format("'{:s}' Renderer", renderer.GetName())};
    printables.add_printable(          "Is Software Fallback", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::SOFTWARE));
    printables.add_printable("Supports Hardware Acceleration", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::ACCELERATED));
    printables.add_printable(                "Supports VSync", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::PRESENTVSYNC));
    printables.add_printable( "Supports rendering to texture", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::TARGETTEXTURE));
    printables.add_printable(                         "Width", renderer.GetWidth());
    printables.add_printable(                        "Height", renderer.GetHeight());
    printables.add_printable(                 "Drawing Color", fmt::format("[Red: {red:d}, Green: {green:d}, Blue: {blue:d}, Alpha: {alpha:d}]",
                                                                           fmt::arg(  "red", drawing_color[0]),
                                                                           fmt::arg("green", drawing_color[1]),
                                                                           fmt::arg( "blue", drawing_color[2]),
                                                                           fmt::arg("alpha", drawing_color[3])));
    printables.add_printable(                    "Blend Mode", blend_mode_string);
    printables.add_printable(         "Maximum Texture Width", renderer.GetMaxTextureWidth());
    printables.add_printable(        "Maximum Texture Height", renderer.GetMaxTextureHeight());

    std::vector<std::string> texture_formats {renderer.GetTextureFormats()};
    for(std::size_t index = 0; index < texture_formats.size(); index++) {
        printables.add_printable(fmt::format("Texture Format #{:d}", index), texture_formats[index]);
    }

    output << printables;

    return output;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
