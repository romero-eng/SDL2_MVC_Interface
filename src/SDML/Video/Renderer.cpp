#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Renderer.hpp"

SDML::Video::Renderer::Renderer(Window& window,
                                uint32_t flags): internal_SDL_renderer{SDL_CreateRenderer(window.Access_SDL_Backend(),
                                                                                          -1,
                                                                                          flags)} {};


SDML::Video::Renderer::Renderer(Window& window,
                                const RendererInitFlag& flag): Renderer{window, std::to_underlying(flag)} {};


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


std::array<int, 2> SDML::Video::Renderer::GetArea()
{
    std::array<int, 2> area;

    if(SDL_GetRendererOutputSize(this->internal_SDL_renderer, &area[0], &area[1]) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve the area for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return area;
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


std::array<int, 2> SDML::Video::Renderer::GetMaxTextureArea()
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return std::array<int, 2> {tmp.max_texture_width, tmp.max_texture_height};
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


bool SDML::Video::Renderer::CheckInitFlags(const RendererInitFlag& flag) { return this->CheckInitFlags(std::to_underlying(flag)); } 


void SDML::Video::Renderer::SetBlendMode(const BlendMode& mode)
{
    SDL_BlendMode tmp;

    switch(mode)
    {
        case BlendMode::REPLACE:
            tmp = SDL_BLENDMODE_NONE;
            break;
        case BlendMode::ALPHA:
            tmp = SDL_BLENDMODE_BLEND;
            break;
        case BlendMode::ADDITIVE:
            tmp = SDL_BLENDMODE_ADD;
            break;
        case BlendMode::MODULATE:
            tmp = SDL_BLENDMODE_MOD;
            break;
        case BlendMode::MULTIPLY:
            tmp = SDL_BLENDMODE_MUL;
            break;
        case BlendMode::INVALID:
            tmp = SDL_BLENDMODE_INVALID;
            break;
    }

    if(SDL_SetRenderDrawBlendMode(this->internal_SDL_renderer, tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not set the Blend Mode for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::SetDrawingColor(const std::array<uint8_t, 4>& color)
{
    if(SDL_SetRenderDrawColor(this->internal_SDL_renderer, color[0], color[1], color[2], color[3]) < 0) {
        throw std::runtime_error(fmt::format("Could not set the color for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawPoint(const std::array<int, 2>& point)
{
    const auto& [x, y] = point;

    if(SDL_RenderDrawPoint(this->internal_SDL_renderer, x, y) < 0) {
        throw std::runtime_error(fmt::format("Could not draw a point ([X: {:d}, Y: {:d}]) for the '{:s}' Renderer: {:s}",
                                             point[0],
                                             point[1],
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawPoint(const std::array<float, 2>& point)
{
    const auto& [x, y] = point;

    if(SDL_RenderDrawPointF(this->internal_SDL_renderer, x, y) < 0) {
        throw std::runtime_error(fmt::format("Could not draw a point for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawPoints(const std::vector<std::array<int, 2>>& points)
{
    std::size_t num_points {points.size()};

    SDL_Point* tmp = new SDL_Point[num_points]; // The try-catch clause down below was put in to absolutely make sure there's no memory leak with this C-style array
    bool error;

    try {

        for(std::size_t i = 0; i < num_points; i++){
            const auto [x, y] = points[i];
            tmp[i] = SDL_Point{x, y};
        }

        error = SDL_RenderDrawPoints(this->internal_SDL_renderer, tmp, static_cast<int>(num_points)) < 0;

        delete [] tmp;

    } catch(...) {

        delete [] tmp;
        error = true;
        throw;

    }

    if(error) {
        throw std::runtime_error(fmt::format("Could not draw points for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawPoints(const std::vector<std::array<float, 2>>& points)
{
    std::size_t num_points {points.size()};

    SDL_FPoint* tmp = new SDL_FPoint[num_points]; // The try-catch clause down below was put in to absolutely make sure there's no memory leak with this C-style array
    bool error;

    try {

        for(std::size_t i = 0; i < num_points; i++){
            const auto& [x, y] = points[i];
            tmp[i] = SDL_FPoint{x, y};
        }

        error = SDL_RenderDrawPointsF(this->internal_SDL_renderer, tmp, static_cast<int>(num_points)) < 0;

        delete [] tmp;

    } catch(...) {

        delete [] tmp;
        error = true;
        throw;

    }

    if(error) {
        throw std::runtime_error(fmt::format("Could not draw points for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawLine(const std::array<std::array<int, 2>, 2>& line)
{
    const auto& [begin_point, end_point] = line;
    const auto& [    begin_x,   begin_y] = begin_point;
    const auto& [      end_x,     end_y] = end_point;

    if(SDL_RenderDrawLine(this->internal_SDL_renderer, begin_x, begin_y, end_x, end_y) < 0) {
        throw std::runtime_error(fmt::format("Could not draw a line for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawLine(const std::array<std::array<float, 2>, 2>& line)
{
    const auto& [begin_point, end_point] = line;
    const auto& [    begin_x,   begin_y] = begin_point;
    const auto& [      end_x,     end_y] = end_point;

    if(SDL_RenderDrawLineF(this->internal_SDL_renderer, begin_x, begin_y, end_x, end_y) < 0) {
        throw std::runtime_error(fmt::format("Could not draw a line for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawConnectedLines(const std::vector<std::array<int, 2>>& line_points)
{
    std::size_t num_points {line_points.size()};

    SDL_Point* tmp = new SDL_Point[num_points];
    bool error;

    try{

        for(std::size_t i = 0; i < num_points; i++) {
            const auto& [x, y] = line_points[i];
            tmp[i] = SDL_Point{x, y};
        }

        error = SDL_RenderDrawLines(this->internal_SDL_renderer, tmp, static_cast<int>(num_points)) < 0;

    } catch (...) {

        delete [] tmp;
        error = true;
        throw;

    }

    delete [] tmp;

    if(error) {
        throw std::runtime_error(fmt::format("Could not draw lines for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawConnectedLines(const std::vector<std::array<float, 2>>& line_points)
{
    std::size_t num_points {line_points.size()};

    SDL_FPoint* tmp = new SDL_FPoint[num_points];
    bool error;

    try{

        for(std::size_t i = 0; i < num_points; i++) {
            const auto& [x, y] = line_points[i];
            tmp[i] = SDL_FPoint{x, y};
        }

        error = SDL_RenderDrawLinesF(this->internal_SDL_renderer, tmp, static_cast<int>(num_points)) < 0;

    } catch (...) {

        delete [] tmp;
        error = true;
        throw;

    }

    delete [] tmp;

    if(error) {
        throw std::runtime_error(fmt::format("Could not draw lines for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawEntireTarget()
{
    if(SDL_RenderFillRect(this->internal_SDL_renderer, nullptr) < 0) {
        throw std::runtime_error(fmt::format("Could not fill the entire target for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Update()
{
    SDL_RenderPresent(this->internal_SDL_renderer);
    if(SDL_RenderClear(this->internal_SDL_renderer) < 0) {
        throw std::runtime_error(fmt::format("Could not clear the current target for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


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

    std::array<int, 2> area {renderer.GetArea()};
    std::array<uint8_t, 4> drawing_color {renderer.GetDrawingColor()};
    std::array<int, 2> max_texture_area {renderer.GetMaxTextureArea()};

    Misc::Printables printables {fmt::format("'{:s}' Renderer", renderer.GetName())};
    printables.add_printable(          "Is Software Fallback", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::SOFTWARE));
    printables.add_printable("Supports Hardware Acceleration", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::ACCELERATED));
    printables.add_printable(                "Supports VSync", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::PRESENTVSYNC));
    printables.add_printable( "Supports rendering to texture", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::TARGETTEXTURE));
    printables.add_printable(                          "Area", fmt::format("[Width: {width:d}, Height: {height:d}]",
                                                                           fmt::arg( "width", area[0]),
                                                                           fmt::arg("height", area[1])));
    printables.add_printable(                 "Drawing Color", fmt::format("[Red: {red:d}, Green: {green:d}, Blue: {blue:d}, Alpha: {alpha:d}]",
                                                                           fmt::arg(  "red", drawing_color[0]),
                                                                           fmt::arg("green", drawing_color[1]),
                                                                           fmt::arg( "blue", drawing_color[2]),
                                                                           fmt::arg("alpha", drawing_color[3])));
    printables.add_printable(                    "Blend Mode", blend_mode_string);
    printables.add_printable(        "Maximum Texture Height", fmt::format("[Width: {width:d}, Height: {height:d}]",
                                                                           fmt::arg( "width", max_texture_area[0]),
                                                                           fmt::arg("height", max_texture_area[1])));

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
