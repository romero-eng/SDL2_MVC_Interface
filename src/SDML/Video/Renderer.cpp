#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Renderer.hpp"

SDML::Video::Renderer::Renderer(Window& window,
                                uint32_t flags): internal_SDL_renderer{SDL_CreateRenderer(window.Access_SDL_Backend(),
                                                                                          -1,
                                                                                          flags)}
{
    if(this->internal_SDL_renderer == nullptr){
        throw std::runtime_error(fmt::format("Could not create a renderer from the '{:s}' Window: {:s}",
                                             window.GetTitle(),
                                             SDL_GetError()));
    }
};


SDML::Video::Renderer::Renderer(Window& window,
                                const RendererInitFlag& flag): Renderer{window, std::to_underlying(flag)} {};


SDML::Video::Renderer::Renderer(Window& window): Renderer{window, 0} {};


SDML::Video::Renderer::~Renderer() { SDL_DestroyRenderer(this->internal_SDL_renderer); }


bool SDML::Video::Renderer::CheckInitFlags(uint32_t flags) const
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return flags == (flags & tmp.flags); 
}


bool SDML::Video::Renderer::CheckInitFlags(const RendererInitFlag& flag) const { return this->CheckInitFlags(std::to_underlying(flag)); }


void SDML::Video::Renderer::ToggleVSync(bool enable_or_disable)
{
    if(SDL_RenderSetVSync(this->internal_SDL_renderer, enable_or_disable) < 0) {
        throw std::runtime_error(fmt::format("Could not toggle the VSync for the '{:s}' Renderer: {:s}",
                                 this->GetName(),
                                 SDL_GetError()));
    }
}


std::string SDML::Video::Renderer::GetName() const
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for Renderer: {:s}",
                                             SDL_GetError()));
    }

    return std::string {tmp.name};
}


std::array<int, 2> SDML::Video::Renderer::GetArea() const
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


std::array<uint8_t, 4> SDML::Video::Renderer::GetDrawingColor() const
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


SDML::Video::BlendMode SDML::Video::Renderer::GetBlendMode() const
{
    SDL_BlendMode tmp;

    if(SDL_GetRenderDrawBlendMode(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not get the Blend Mode for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return SDL_to_SDML(tmp);
}


void SDML::Video::Renderer::SetBlendMode(const BlendMode& mode)
{
    if(SDL_SetRenderDrawBlendMode(this->internal_SDL_renderer, SDML_to_SDL(mode)) < 0) {
        throw std::runtime_error(fmt::format("Could not set the Blend Mode for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


std::pair<std::array<int, 2>, std::array<int, 2>> SDML::Video::Renderer::GetViewPort() const
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


std::optional<std::pair<std::array<int, 2>, std::array<int, 2>>> SDML::Video::Renderer::GetClippingRectangle() const
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


bool SDML::Video::Renderer::CheckClippingEnabled() const { return SDL_RenderIsClipEnabled(this->internal_SDL_renderer); }


std::array<float, 2> SDML::Video::Renderer::GetScale() const
{
    float scaleX;
    float scaleY;
    SDL_RenderGetScale(this->internal_SDL_renderer, &scaleX, &scaleY);

    return std::array<float, 2> {scaleX, scaleY};
}


void SDML::Video::Renderer::SetScale(const std::array<float, 2>& scale)
{
    const auto& [scaleX, scaleY] = scale;

    if(SDL_RenderSetScale(this->internal_SDL_renderer, scaleX, scaleY) < 0) {
        throw std::runtime_error(fmt::format("Could not set the scale for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


bool SDML::Video::Renderer::CheckIntegerScale() const { return SDL_RenderGetIntegerScale(this->internal_SDL_renderer); }


void SDML::Video::Renderer::ToggleIntegerScale(bool enable_or_disable)
{
    if(SDL_RenderSetIntegerScale(this->internal_SDL_renderer, enable_or_disable ? SDL_TRUE : SDL_FALSE) < 0) {
        throw std::runtime_error(fmt::format("Could not toggle the integer scale for the '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


std::optional<std::array<int, 2>> SDML::Video::Renderer::GetLogicalArea() const
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


std::array<int, 2> SDML::Video::Renderer::ConvertLogicalPointToRealPoint(std::array<float, 2> logical_point)
{
    const auto& [logical_x, logical_y] = logical_point;
    int real_x;
    int real_y;

    SDL_RenderLogicalToWindow(this->internal_SDL_renderer,
                              logical_x, logical_y,
                              &real_x, &real_y);

    return std::array<int, 2> {real_x, real_y};
}


std::array<float, 2> SDML::Video::Renderer::ConvertRealPointToLogicalPoint(std::array<int, 2> real_point)
{

    const auto& [real_x, real_y] = real_point;
    float logical_x;
    float logical_y;

    SDL_RenderWindowToLogical(this->internal_SDL_renderer,
                              real_x, real_y, 
                              &logical_x, &logical_y);

    return std::array<float, 2> {logical_x, logical_y};
}


std::array<int, 2> SDML::Video::Renderer::GetMaxTextureArea() const
{
    SDL_RendererInfo tmp {};
    if(SDL_GetRendererInfo(this->internal_SDL_renderer, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not retrieve information for '{:s}' Renderer: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return std::array<int, 2> {tmp.max_texture_width, tmp.max_texture_height};
}


std::vector<std::string> SDML::Video::Renderer::GetTextureFormats() const
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


SDML::Video::Texture SDML::Video::Renderer::GetTarget() { return Texture("Render Target", SDL_GetRenderTarget(this->internal_SDL_renderer)); }


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


void SDML::Video::Renderer::Copy(Texture& texture)
{
    if(SDL_RenderCopy(this->internal_SDL_renderer, texture.Access_SDL_Backend(), nullptr, nullptr) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& destination_rect_info)
{
    const auto& [top_left_point, area] = destination_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect dst_rect {top_left_x, top_left_y, width, height};

    if(SDL_RenderCopy(this->internal_SDL_renderer, texture.Access_SDL_Backend(), nullptr, &dst_rect) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& destination_rect_info,
                                 double angle,
                                 const FlipAction& flip_action)
{
    const auto& [top_left_point, area] = destination_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect dst_rect {top_left_x, top_left_y, width, height};

    SDL_RendererFlip tmp_flip;
    switch(flip_action){
        case FlipAction::NONE:
            tmp_flip = SDL_FLIP_NONE;
            break;
        case FlipAction::HORIZONTAL:
            tmp_flip = SDL_FLIP_HORIZONTAL;
            break;
        case FlipAction::VERTICAL:
            tmp_flip = SDL_FLIP_VERTICAL;
            break;
    }

    if(SDL_RenderCopyEx(this->internal_SDL_renderer,
                        texture.Access_SDL_Backend(),
                        nullptr, &dst_rect, angle, nullptr,
                        tmp_flip) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& source_rect_info,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& destination_rect_info,
                                 double angle,
                                 const FlipAction& flip_action)
{
    const auto& [src_top_left_point, src_area] = source_rect_info;
    const auto& [src_top_left_x, src_top_left_y] = src_top_left_point;
    const auto& [src_width, src_height] = src_area;

    SDL_Rect src_rect {src_top_left_x, src_top_left_y, src_width, src_height};

    const auto& [dst_top_left_point, dst_area] = destination_rect_info;
    const auto& [dst_top_left_x, dst_top_left_y] = dst_top_left_point;
    const auto& [dst_width, dst_height] = dst_area;

    SDL_Rect dst_rect {dst_top_left_x, dst_top_left_y, dst_width, dst_height};

    SDL_RendererFlip tmp_flip;
    switch(flip_action){
        case FlipAction::NONE:
            tmp_flip = SDL_FLIP_NONE;
            break;
        case FlipAction::HORIZONTAL:
            tmp_flip = SDL_FLIP_HORIZONTAL;
            break;
        case FlipAction::VERTICAL:
            tmp_flip = SDL_FLIP_VERTICAL;
            break;
    }

    if(SDL_RenderCopyEx(this->internal_SDL_renderer,
                        texture.Access_SDL_Backend(),
                        &src_rect, &dst_rect,
                        angle, nullptr,
                        tmp_flip) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& destination_rect_info,
                                 double angle,
                                 const std::array<int, 2>& center,
                                 const FlipAction& flip_action)
{
    const auto& [top_left_point, area] = destination_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect dst_rect {top_left_x, top_left_y, width, height};

    const auto& [center_x, center_y] = center;
    SDL_Point tmp_center {center_x, center_y};

    SDL_RendererFlip tmp_flip;
    switch(flip_action){
        case FlipAction::NONE:
            tmp_flip = SDL_FLIP_NONE;
            break;
        case FlipAction::HORIZONTAL:
            tmp_flip = SDL_FLIP_HORIZONTAL;
            break;
        case FlipAction::VERTICAL:
            tmp_flip = SDL_FLIP_VERTICAL;
            break;
    }

    if(SDL_RenderCopyEx(this->internal_SDL_renderer,
                        texture.Access_SDL_Backend(),
                        nullptr, &dst_rect, angle, &tmp_center,
                        tmp_flip) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& source_rect_info,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& destination_rect_info,
                                 double angle,
                                 const std::array<int, 2>& center,
                                 const FlipAction& flip_action)
{
    const auto& [src_top_left_point, src_area] = source_rect_info;
    const auto& [src_top_left_x, src_top_left_y] = src_top_left_point;
    const auto& [src_width, src_height] = src_area;

    SDL_Rect src_rect {src_top_left_x, src_top_left_y, src_width, src_height};

    const auto& [dst_top_left_point, dst_area] = destination_rect_info;
    const auto& [dst_top_left_x, dst_top_left_y] = dst_top_left_point;
    const auto& [dst_width, dst_height] = dst_area;

    SDL_Rect dst_rect {dst_top_left_x, dst_top_left_y, dst_width, dst_height};

    const auto& [center_x, center_y] = center;
    SDL_Point tmp_center {center_x, center_y};

    SDL_RendererFlip tmp_flip;
    switch(flip_action){
        case FlipAction::NONE:
            tmp_flip = SDL_FLIP_NONE;
            break;
        case FlipAction::HORIZONTAL:
            tmp_flip = SDL_FLIP_HORIZONTAL;
            break;
        case FlipAction::VERTICAL:
            tmp_flip = SDL_FLIP_VERTICAL;
            break;
    }

    if(SDL_RenderCopyEx(this->internal_SDL_renderer,
                        texture.Access_SDL_Backend(),
                        &src_rect, &dst_rect,
                        angle, &tmp_center,
                        tmp_flip) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& source_rect_info,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& destination_rect_info)
{
    const auto& [dst_top_left_point, dst_area] = destination_rect_info;
    const auto& [dst_top_left_x, dst_top_left_y] = dst_top_left_point;
    const auto& [dst_width, dst_height] = dst_area;

    SDL_Rect dst_rect {dst_top_left_x, dst_top_left_y, dst_width, dst_height};

    const auto& [src_top_left_point, src_area] = source_rect_info;
    const auto& [src_top_left_x, src_top_left_y] = src_top_left_point;
    const auto& [src_width, src_height] = src_area;

    SDL_Rect src_rect {src_top_left_x, src_top_left_y, src_width, src_height};

    if(SDL_RenderCopy(this->internal_SDL_renderer, texture.Access_SDL_Backend(), &src_rect, &dst_rect) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<float, 2>, std::array<float, 2>>& destination_rect_info)
{
    const auto& [top_left_point, area] = destination_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_FRect dst_rect {top_left_x, top_left_y, width, height};

    if(SDL_RenderCopyF(this->internal_SDL_renderer, texture.Access_SDL_Backend(), nullptr, &dst_rect) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& source_rect_info,
                                 const std::pair<std::array<float, 2>, std::array<float, 2>>& destination_rect_info)
{
    const auto& [dst_top_left_point, dst_area] = destination_rect_info;
    const auto& [dst_top_left_x, dst_top_left_y] = dst_top_left_point;
    const auto& [dst_width, dst_height] = dst_area;

    SDL_FRect dst_rect {dst_top_left_x, dst_top_left_y, dst_width, dst_height};

    const auto& [src_top_left_point, src_area] = source_rect_info;
    const auto& [src_top_left_x, src_top_left_y] = src_top_left_point;
    const auto& [src_width, src_height] = src_area;

    SDL_Rect src_rect {src_top_left_x, src_top_left_y, src_width, src_height};

    if(SDL_RenderCopyF(this->internal_SDL_renderer, texture.Access_SDL_Backend(), &src_rect, &dst_rect) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<float, 2>, std::array<float, 2>>& destination_rect_info,
                                 double angle,
                                 const FlipAction& flip_action)
{
    const auto& [top_left_point, area] = destination_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_FRect dst_rect {top_left_x, top_left_y, width, height};

    SDL_RendererFlip tmp_flip;
    switch(flip_action){
        case FlipAction::NONE:
            tmp_flip = SDL_FLIP_NONE;
            break;
        case FlipAction::HORIZONTAL:
            tmp_flip = SDL_FLIP_HORIZONTAL;
            break;
        case FlipAction::VERTICAL:
            tmp_flip = SDL_FLIP_VERTICAL;
            break;
    }

    if(SDL_RenderCopyExF(this->internal_SDL_renderer,
                         texture.Access_SDL_Backend(),
                         nullptr, &dst_rect, angle, nullptr,
                         tmp_flip) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& source_rect_info,
                                 const std::pair<std::array<float, 2>, std::array<float, 2>>& destination_rect_info,
                                 double angle,
                                 const FlipAction& flip_action)
{
    const auto& [src_top_left_point, src_area] = source_rect_info;
    const auto& [src_top_left_x, src_top_left_y] = src_top_left_point;
    const auto& [src_width, src_height] = src_area;

    SDL_Rect src_rect {src_top_left_x, src_top_left_y, src_width, src_height};

    const auto& [dst_top_left_point, dst_area] = destination_rect_info;
    const auto& [dst_top_left_x, dst_top_left_y] = dst_top_left_point;
    const auto& [dst_width, dst_height] = dst_area;

    SDL_FRect dst_rect {dst_top_left_x, dst_top_left_y, dst_width, dst_height};

    SDL_RendererFlip tmp_flip;
    switch(flip_action){
        case FlipAction::NONE:
            tmp_flip = SDL_FLIP_NONE;
            break;
        case FlipAction::HORIZONTAL:
            tmp_flip = SDL_FLIP_HORIZONTAL;
            break;
        case FlipAction::VERTICAL:
            tmp_flip = SDL_FLIP_VERTICAL;
            break;
    }

    if(SDL_RenderCopyExF(this->internal_SDL_renderer,
                         texture.Access_SDL_Backend(),
                         &src_rect, &dst_rect,
                         angle, nullptr,
                         tmp_flip) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<float, 2>, std::array<float, 2>>& destination_rect_info,
                                 double angle,
                                 const std::array<float, 2>& center,
                                 const FlipAction& flip_action)
{
    const auto& [top_left_point, area] = destination_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_FRect dst_rect {top_left_x, top_left_y, width, height};

    const auto& [center_x, center_y] = center;
    SDL_FPoint tmp_center {center_x, center_y};

    SDL_RendererFlip tmp_flip;
    switch(flip_action){
        case FlipAction::NONE:
            tmp_flip = SDL_FLIP_NONE;
            break;
        case FlipAction::HORIZONTAL:
            tmp_flip = SDL_FLIP_HORIZONTAL;
            break;
        case FlipAction::VERTICAL:
            tmp_flip = SDL_FLIP_VERTICAL;
            break;
    }

    if(SDL_RenderCopyExF(this->internal_SDL_renderer,
                         texture.Access_SDL_Backend(),
                         nullptr, &dst_rect, angle, &tmp_center,
                         tmp_flip) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Renderer::Copy(Texture& texture,
                                 const std::pair<std::array<int, 2>, std::array<int, 2>>& source_rect_info,
                                 const std::pair<std::array<float, 2>, std::array<float, 2>>& destination_rect_info,
                                 double angle,
                                 const std::array<float, 2>& center,
                                 const FlipAction& flip_action)
{
    const auto& [src_top_left_point, src_area] = source_rect_info;
    const auto& [src_top_left_x, src_top_left_y] = src_top_left_point;
    const auto& [src_width, src_height] = src_area;

    SDL_Rect src_rect {src_top_left_x, src_top_left_y, src_width, src_height};

    const auto& [dst_top_left_point, dst_area] = destination_rect_info;
    const auto& [dst_top_left_x, dst_top_left_y] = dst_top_left_point;
    const auto& [dst_width, dst_height] = dst_area;

    SDL_FRect dst_rect {dst_top_left_x, dst_top_left_y, dst_width, dst_height};

    const auto& [center_x, center_y] = center;
    SDL_FPoint tmp_center {center_x, center_y};

    SDL_RendererFlip tmp_flip;
    switch(flip_action){
        case FlipAction::NONE:
            tmp_flip = SDL_FLIP_NONE;
            break;
        case FlipAction::HORIZONTAL:
            tmp_flip = SDL_FLIP_HORIZONTAL;
            break;
        case FlipAction::VERTICAL:
            tmp_flip = SDL_FLIP_VERTICAL;
            break;
    }

    if(SDL_RenderCopyExF(this->internal_SDL_renderer,
                         texture.Access_SDL_Backend(),
                         &src_rect, &dst_rect,
                         angle, &tmp_center,
                         tmp_flip) < 0) {
        throw std::runtime_error(fmt::format("Could not copy the '{:s}' Texture using the '{:s}' Renderer: {:s}",
                                             texture.GetName(),
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


SDL_Renderer* SDML::Video::Renderer::Access_SDL_Backend() { return this->internal_SDL_renderer; }


uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, const SDML::Video::RendererInitFlag& second_flag) { return std::to_underlying(first_flag) | std::to_underlying(second_flag); }


uint32_t operator|(uint32_t first_flag, const SDML::Video::RendererInitFlag& second_flag) { return first_flag | std::to_underlying(second_flag); }


uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, uint32_t second_flag) { return std::to_underlying(first_flag) | second_flag; }


std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Renderer& renderer)
{
    Misc::Printables printables {fmt::format("'{:s}' Renderer", renderer.GetName())};
    printables.add_printable(          "Is Software Fallback", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::SOFTWARE));
    printables.add_printable("Supports Hardware Acceleration", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::ACCELERATED));
    printables.add_printable(                "Supports VSync", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::PRESENTVSYNC));
    printables.add_printable( "Supports rendering to texture", renderer.CheckInitFlags(SDML::Video::RendererInitFlag::TARGETTEXTURE));
    printables.add_printable(           "Clipping is Enabled", renderer.CheckClippingEnabled());
    printables.add_printable(          "Integer Scale is set", renderer.CheckIntegerScale());

    const auto& [width, height] {renderer.GetArea()};
    printables.add_printable("Area", fmt::format("[Width: {:d}, Height: {:d}]", width, height));

    const auto& [red, green, blue, alpha] {renderer.GetDrawingColor()};
    printables.add_printable("Drawing Color", fmt::format("[Red: {:d}, Green: {:d}, Blue: {:d}, Alpha: {:d}]", red, green, blue, alpha));

    printables.add_printable("Blend Mode", to_string(renderer.GetBlendMode()));

    const auto& [viewport_top_left_point, viewport_area] {renderer.GetViewPort()};
    const auto& [viewPort_top_left_x, viewport_top_left_y] = viewport_top_left_point;
    const auto& [viewport_width, viewport_height] = viewport_area;
    printables.add_printable("Viewport", fmt::format("Area [Width: {:d}, Height: {:d}] from Top Left Point [X: {:d}, Y: {:d}]",
                             viewPort_top_left_x,
                             viewport_top_left_y,
                             viewport_width,
                             viewport_height));

    std::optional<std::pair<std::array<int, 2>, std::array<int, 2>>> clip_rect_info {renderer.GetClippingRectangle()};
    if (clip_rect_info.has_value()){
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
    if(logical_area.has_value()) {
        const auto& [logical_width, logical_height] = *logical_area;
        printables.add_printable("Logical Area", fmt::format("[Width: {:d}, Height: {:d}]", logical_width, logical_height));
    }

    const auto& [scaleX, scaleY] {renderer.GetScale()};
    printables.add_printable("Scale", fmt::format("[X-scale: {:f}, Y-scale: {:f}]", scaleX, scaleY));

    const auto& [max_texture_width, max_texture_height] {renderer.GetMaxTextureArea()};
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
