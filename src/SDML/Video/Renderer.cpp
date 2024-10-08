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
    int width;
    int height;

    if(SDL_GetRendererOutputSize(this->internal_SDL_renderer, &width, &height) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve the area for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return std::array<int, 2> {width, height};
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


void SDML::Video::Renderer::SetDrawingColor(const std::array<uint8_t, 4>& color)
{
    if(SDL_SetRenderDrawColor(this->internal_SDL_renderer, color[0], color[1], color[2], color[3]) < 0) {
        throw std::runtime_error(fmt::format("Could not set the color for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
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


std::pair<std::array<int, 2>, std::array<int, 2>> SDML::Video::Renderer::GetViewPort()
{
    SDL_Rect tmp {};
    SDL_RenderGetViewport(this->internal_SDL_renderer, &tmp);

    return std::pair<std::array<int, 2>, std::array<int, 2>> {{tmp.x, tmp.y}, {tmp.w, tmp.h}};
}


void SDML::Video::Renderer::SetViewPort(const std::pair<std::array<int, 2>, std::array<int, 2>>& rect_info)
{
    const auto& [top_left_point, area] = rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect tmp {top_left_x, top_left_y, width, height};

    if(SDL_RenderSetViewport(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not set the viewport for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


std::optional<std::pair<std::array<int, 2>, std::array<int, 2>>> SDML::Video::Renderer::GetClippingRectangle()
{
    if(this->CheckClippingEnabled()) {

        SDL_Rect tmp;
        SDL_RenderGetClipRect(this->internal_SDL_renderer, &tmp);
        return std::pair<std::array<int, 2>, std::array<int, 2>> {{tmp.x, tmp.y}, {tmp.w, tmp.h}};

    } else {
        return std::nullopt;
    }
}


void SDML::Video::Renderer::SetClippingRectangle(const std::pair<std::array<int, 2>, std::array<int, 2>>& clip_rect_info)
{
    const auto& [top_left_point, area] = clip_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect tmp {top_left_x, top_left_y, width, height};

    if(SDL_RenderSetClipRect(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not set a clipping rectangle for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DisableClipping()
{
    if(SDL_RenderSetClipRect(this->internal_SDL_renderer, nullptr) < 0) {
        throw std::runtime_error(fmt::format("Could not disable clipping for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


std::optional<std::array<int, 2>> SDML::Video::Renderer::GetLogicalArea()
{
    int width {};
    int height {};

    SDL_RenderGetLogicalSize(this->internal_SDL_renderer, &width, &height);

    if (width != 0 || height != 0) {
        return std::array<int, 2> {width, height};
    } else {
        return std::nullopt;
    }
}


void SDML::Video::Renderer::SetLogicalArea(const std::array<int, 2>& area)
{
    const auto& [width, height] = area;

    if(SDL_RenderSetLogicalSize(this->internal_SDL_renderer, width, height) < 0) {
        throw std::runtime_error(fmt::format("Could not set the logical area size for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
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


bool SDML::Video::Renderer::CheckClippingEnabled() { return SDL_RenderIsClipEnabled(this->internal_SDL_renderer); }


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

    try {

        for(std::size_t i = 0; i < num_points; i++){
            const auto [x, y] = points[i];
            tmp[i] = SDL_Point{x, y};
        }

        if(SDL_RenderDrawPoints(this->internal_SDL_renderer, tmp, static_cast<int>(num_points)) < 0) {
            throw std::runtime_error(fmt::format("Could not draw points for the '{:s}' Renderer: {:s}",
                                                 this->GetName(),
                                                 SDL_GetError()));
        }
        

        delete [] tmp;

    } catch(...) {

        delete [] tmp;
        throw;

    }
}


void SDML::Video::Renderer::DrawPoints(const std::vector<std::array<float, 2>>& points)
{
    std::size_t num_points {points.size()};

    SDL_FPoint* tmp = new SDL_FPoint[num_points]; // The try-catch clause down below was put in to absolutely make sure there's no memory leak with this C-style array

    try {

        for(std::size_t i = 0; i < num_points; i++){
            const auto& [x, y] = points[i];
            tmp[i] = SDL_FPoint{x, y};
        }

        if(SDL_RenderDrawPointsF(this->internal_SDL_renderer, tmp, static_cast<int>(num_points)) < 0) {
            throw std::runtime_error(fmt::format("Could not draw points for the '{:s}' Renderer: {:s}",
                                                 this->GetName(),
                                                 SDL_GetError()));
        }

        delete [] tmp;

    } catch(...) {

        delete [] tmp;
        throw;

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

    try{

        for(std::size_t i = 0; i < num_points; i++) {
            const auto& [x, y] = line_points[i];
            tmp[i] = SDL_Point{x, y};
        }

        if(SDL_RenderDrawLines(this->internal_SDL_renderer, tmp, static_cast<int>(num_points)) < 0) {
            throw std::runtime_error(fmt::format("Could not draw lines for the '{:s}' Renderer: {:s}",
                                                 this->GetName(),
                                                 SDL_GetError()));
        }

    } catch (...) {

        delete [] tmp;
        throw;

    }

    delete [] tmp;
}


void SDML::Video::Renderer::DrawConnectedLines(const std::vector<std::array<float, 2>>& line_points)
{
    std::size_t num_points {line_points.size()};

    SDL_FPoint* tmp = new SDL_FPoint[num_points];

    try{

        for(std::size_t i = 0; i < num_points; i++) {
            const auto& [x, y] = line_points[i];
            tmp[i] = SDL_FPoint{x, y};
        }

        if(SDL_RenderDrawLinesF(this->internal_SDL_renderer, tmp, static_cast<int>(num_points)) < 0) {
            throw std::runtime_error(fmt::format("Could not draw lines for the '{:s}' Renderer: {:s}",
                                                 this->GetName(),
                                                 SDL_GetError()));
        }

    } catch (...) {

        delete [] tmp;
        throw;

    }

    delete [] tmp;
}


void SDML::Video::Renderer::DrawRectangleOutline(const std::pair<std::array<int, 2>, std::array<int, 2>>& rect_info)
{
    const auto& [top_left_point, area] = rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect tmp {top_left_x, top_left_y, width, height};

    if(SDL_RenderDrawRect(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not draw a rectangle for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawRectangleOutline(const std::pair<std::array<float, 2>, std::array<float, 2>>& rect_info)
{
    const auto& [top_left_point, area] = rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_FRect tmp {top_left_x, top_left_y, width, height};

    if(SDL_RenderDrawRectF(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not draw a rectangle for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawRectangleOutlines(const std::vector<std::pair<std::array<int, 2>, std::array<int, 2>>>& rects_info)
{
    std::size_t num_rects {rects_info.size()};

    SDL_Rect* tmp = new SDL_Rect[num_rects];

    try{

        for(std::size_t i = 0; i < num_rects; i++) {
            const auto& [top_left_point, area] = rects_info[i];
            const auto& [top_left_x, top_left_y] = top_left_point;
            const auto& [width, height] = area;

            tmp[i] = SDL_Rect{top_left_x, top_left_y, width, height};
        }

        if(SDL_RenderDrawRects(this->internal_SDL_renderer, tmp, static_cast<int>(num_rects)) < 0) {
            throw std::runtime_error(fmt::format("Could not draw rectangles for the '{:s}' Renderer: {:s}",
                                                 this->GetName(),
                                                 SDL_GetError()));
        }

    } catch (...) {

        delete [] tmp;
        throw;

    }

    delete [] tmp;
}


void SDML::Video::Renderer::DrawRectangleOutlines(const std::vector<std::pair<std::array<float, 2>, std::array<float, 2>>>& rects_info)
{
    std::size_t num_rects {rects_info.size()};

    SDL_FRect* tmp = new SDL_FRect[num_rects];

    try{

        for(std::size_t i = 0; i < num_rects; i++) {
            const auto& [top_left_point, area] = rects_info[i];
            const auto& [top_left_x, top_left_y] = top_left_point;
            const auto& [width, height] = area;

            tmp[i] = SDL_FRect{top_left_x, top_left_y, width, height};
        }

        if(SDL_RenderDrawRectsF(this->internal_SDL_renderer, tmp, static_cast<int>(num_rects)) < 0) {
            throw std::runtime_error(fmt::format("Could not draw rectangles for the '{:s}' Renderer: {:s}",
                                                 this->GetName(),
                                                 SDL_GetError()));
        }

    } catch (...) {

        delete [] tmp;
        throw;

    }

    delete [] tmp;
}


void SDML::Video::Renderer::DrawRectangle(const std::pair<std::array<int, 2>, std::array<int, 2>>& rect_info)
{
    const auto& [top_left_point, area] = rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect tmp {top_left_x, top_left_y, width, height};

    if(SDL_RenderFillRect(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not draw a rectangle for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawRectangle(const std::pair<std::array<float, 2>, std::array<float, 2>>& rect_info)
{
    const auto& [top_left_point, area] = rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_FRect tmp {top_left_x, top_left_y, width, height};

    if(SDL_RenderFillRectF(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not draw a rectangle for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::DrawRectangles(const std::vector<std::pair<std::array<int, 2>, std::array<int, 2>>>& rects_info)
{
    std::size_t num_rects {rects_info.size()};

    SDL_Rect* tmp = new SDL_Rect[num_rects];

    try{

        for(std::size_t i = 0; i < num_rects; i++) {
            const auto& [top_left_point, area] = rects_info[i];
            const auto& [top_left_x, top_left_y] = top_left_point;
            const auto& [width, height] = area;

            tmp[i] = SDL_Rect{top_left_x, top_left_y, width, height};
        }

        if(SDL_RenderFillRects(this->internal_SDL_renderer, tmp, static_cast<int>(num_rects)) < 0) {
            throw std::runtime_error(fmt::format("Could not draw rectangles for the '{:s}' Renderer: {:s}",
                                                 this->GetName(),
                                                 SDL_GetError()));
        }

    } catch (...) {

        delete [] tmp;
        throw;

    }

    delete [] tmp;
}


void SDML::Video::Renderer::DrawRectangles(const std::vector<std::pair<std::array<float, 2>, std::array<float, 2>>>& rects_info)
{
    std::size_t num_rects {rects_info.size()};

    SDL_FRect* tmp = new SDL_FRect[num_rects];

    try{

        for(std::size_t i = 0; i < num_rects; i++) {
            const auto& [top_left_point, area] = rects_info[i];
            const auto& [top_left_x, top_left_y] = top_left_point;
            const auto& [width, height] = area;

            tmp[i] = SDL_FRect{top_left_x, top_left_y, width, height};
        }

        if(SDL_RenderFillRectsF(this->internal_SDL_renderer, tmp, static_cast<int>(num_rects)) < 0) {
            throw std::runtime_error(fmt::format("Could not draw rectangles for the '{:s}' Renderer: {:s}",
                                                 this->GetName(),
                                                 SDL_GetError()));
        }

    } catch (...) {

        delete [] tmp;
        throw;

    }

    delete [] tmp;
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

    Misc::Printables printables {fmt::format("'{:s}' Renderer", renderer.GetName())};
    printables.add_printable(          "Is Software Fallback", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::SOFTWARE));
    printables.add_printable("Supports Hardware Acceleration", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::ACCELERATED));
    printables.add_printable(                "Supports VSync", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::PRESENTVSYNC));
    printables.add_printable( "Supports rendering to texture", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::TARGETTEXTURE));
    printables.add_printable(           "Clipping is Enabled", renderer.CheckClippingEnabled());

    std::array<int, 2> area {renderer.GetArea()};
    const auto& [width, height] = area;
    printables.add_printable("Area", fmt::format("[Width: {:d}, Height: {:d}]", width, height));

    std::array<uint8_t, 4> drawing_color {renderer.GetDrawingColor()};
    const auto& [red, green, blue, alpha] = drawing_color;
    printables.add_printable("Drawing Color", fmt::format("[Red: {:d}, Green: {:d}, Blue: {:d}, Alpha: {:d}]", red, green, blue, alpha));

    printables.add_printable("Blend Mode", blend_mode_string);

    std::pair<std::array<int, 2>, std::array<int, 2>> viewport {renderer.GetViewPort()};
    const auto& [viewport_top_left_point, viewport_area] = viewport;
    const auto& [viewPort_top_left_x, viewport_top_left_y] = viewport_top_left_point;
    const auto& [viewport_width, viewport_height] = viewport_area;
    printables.add_printable("Viewport", fmt::format("Area [Width: {:d}, Height: {:d}] from Top Left Point [X: {:d}, Y: {:d}]",
                             viewPort_top_left_x,
                             viewport_top_left_y,
                             viewport_width,
                             viewport_height));

    std::optional<std::pair<std::array<int, 2>, std::array<int, 2>>> clip_rect_info {renderer.GetClippingRectangle()};
    if (clip_rect_info){
        const auto& [clip_rect_top_left_point, clip_rect_area] = *clip_rect_info;
        const auto& [clip_rect_top_left_x, clip_rect_top_left_y] = clip_rect_top_left_point;
        const auto& [clip_rect_width, clip_rect_height] = clip_rect_area;
        printables.add_printable("Clipping Rectangle", fmt::format("Area [Width: {:d}, Height: {:d}] from Top Left Point [X: {:d}, Y: {:d}]",
                                                                   clip_rect_top_left_x,
                                                                   clip_rect_top_left_y,
                                                                   clip_rect_width,
                                                                   clip_rect_height));
    }

    std::optional<std::array<int, 2>> logical_area {renderer.GetLogicalArea()};
    if(logical_area) {
        const auto& [logical_width, logical_height] = *logical_area;
        printables.add_printable("Logical Area", fmt::format("[Width: {:d}, Height: {:d}]", logical_width, logical_height));
    }

    std::array<int, 2> max_texture_area {renderer.GetMaxTextureArea()};
    const auto& [max_texture_width, max_texture_height] = max_texture_area;
    printables.add_printable("Maximum Texture Area", fmt::format("[Width: {:d}, Height: {:d}]", max_texture_width, max_texture_height));

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
