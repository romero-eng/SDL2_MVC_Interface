#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Surface.hpp"


SDML::Video::Surface::Surface(Window& window,
                              const std::filesystem::path& image_file): name{image_file.stem()},
                                                                        internal_SDL_surface{SDL_ConvertSurface(IMG_Load(image_file.string().c_str()),
                                                                                                                SDL_GetWindowSurface(window.Access_SDL_Backend())->format,
                                                                                                                0)}
{
    if(!(this->Has_RLE_Acceleration())){
        this->EnableOrDisable_RLE_Acceleration(true);
    }
}


SDML::Video::Surface::~Surface() { SDL_FreeSurface(this->internal_SDL_surface); }


std::string SDML::Video::Surface::GetName() const { return this->name; }


std::array<uint8_t, 4> SDML::Video::Surface::GetColor() const
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;

    if(SDL_GetSurfaceColorMod(this->internal_SDL_surface, &red, &green, &blue) < 0) {
        throw std::runtime_error(fmt::format("Could not get the RGB values for the '{:s}' Surface: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    if(SDL_GetSurfaceAlphaMod(this->internal_SDL_surface, &alpha) < 0) {
        throw std::runtime_error(fmt::format("Could not get the alpha value for the '{:s}' Surface: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return std::array<uint8_t, 4> {red, green, blue, alpha};
}


void SDML::Video::Surface::SetColor(const std::array<uint8_t, 4>& color)
{
    const auto& [red, green, blue, alpha] = color;

    if(SDL_SetSurfaceColorMod(this->internal_SDL_surface, red, green, blue) < 0) {
        throw std::runtime_error(fmt::format("Could not set the RGB values for the '{:s}' Surface: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    if(SDL_SetSurfaceAlphaMod(this->internal_SDL_surface, alpha) < 0) {
        throw std::runtime_error(fmt::format("Could not set the alpha value for the '{:s}' Surface: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


SDML::Video::BlendMode SDML::Video::Surface::GetBlendMode() const
{
    SDL_BlendMode tmp;

    if(SDL_GetSurfaceBlendMode(this->internal_SDL_surface, &tmp) < 0) {
        std::runtime_error(fmt::format("Could not get the blend mode for the '{:s}' Texture: {:s}",
                                       this->GetName(),
                                       SDL_GetError()));
    }

    return SDL_to_SDML(tmp);
}


void SDML::Video::Surface::SetBlendMode(const BlendMode& mode)
{
    if(SDL_SetSurfaceBlendMode(this->internal_SDL_surface, SDML_to_SDL(mode)) < 0) {
        throw std::runtime_error(fmt::format("Could not set the blend mode for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


void SDML::Video::Surface::EnableOrDisable_RLE_Acceleration(bool enable)
{
    if(SDL_SetSurfaceRLE(this->internal_SDL_surface, enable ? 1 : 0) < 0) {
        throw std::runtime_error(fmt::format("Could not enable RLE Acceleration for the '{:s}' Surface: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


std::optional<std::array<uint8_t, 3>> SDML::Video::Surface::GetTransparentColor() const
{
    uint32_t color_key;

    if(SDL_GetColorKey(this->internal_SDL_surface, &color_key) < 0) {

        std::cerr << fmt::format("Could not get the transparent color for the '{:s}' Surface: {:s}",
                                             this->GetName(),
                                             SDL_GetError()) << std::endl;

        return std::nullopt;

    } else {

        uint8_t red;
        uint8_t green;
        uint8_t blue;

        SDL_GetRGB(color_key,
                   this->internal_SDL_surface->format,
                   &red, &green, &blue);
    
        return std::array<uint8_t, 3> {red, green, blue};
    }
}


void SDML::Video::Surface::EnableOrDisableTransparentColor(std::array<uint8_t, 3> color,
                                                           bool enable)
{
    const auto& [red, green, blue] = color;

    if(SDL_SetColorKey(this->internal_SDL_surface,
                       enable? SDL_TRUE : SDL_FALSE,
                       SDL_MapRGB(this->internal_SDL_surface->format, red, green, blue))) {
        throw std::runtime_error(fmt::format("Could not {:s} '{:s}' the color transparency for the Surface: {:s}",
                                             enable? "enable" : "disable",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


bool SDML::Video::Surface::Has_RLE_Acceleration() const { return SDL_HasSurfaceRLE(this->internal_SDL_surface); }


std::pair<std::array<int, 2>, std::array<int, 2>> SDML::Video::Surface::GetClipRectangle() const
{
    SDL_Rect tmp {};
    SDL_GetClipRect(this->internal_SDL_surface, &tmp);

    return std::pair<std::array<int, 2>, std::array<int, 2>> {{tmp.x, tmp.y}, {tmp.w, tmp.h}};
}


bool SDML::Video::Surface::SetClipRectangle(std::pair<std::array<int, 2>, std::array<int, 2>> clip_rect_info)
{
    const auto& [top_left_point, area] = clip_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect tmp {top_left_x, top_left_y, width, height};

    return SDL_SetClipRect(this->internal_SDL_surface, &tmp);
}


void SDML::Video::Surface::DisableClipping() { SDL_SetClipRect(this->internal_SDL_surface, nullptr); }


SDL_Surface* SDML::Video::Surface::Access_SDL_Backend() { return this->internal_SDL_surface; }


std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Surface& surface)
{
    Misc::Printables settings {fmt::format("'{:s}' Surface", surface.GetName())};

    const auto& [red, green, blue, alpha] = surface.GetColor();
    settings.add_printable("Color", fmt::format("[Red: {:d}, Green: {:d}, Blue: {:d}, Alpha {:d}]", red, green, blue, alpha));
    settings.add_printable("Blend Mode", to_string(surface.GetBlendMode()));
    settings.add_printable("RLE Acceleration", surface.Has_RLE_Acceleration());

    
	std::optional<std::array<uint8_t, 3>> transparent_color {surface.GetTransparentColor()};
	if(transparent_color.has_value()){
		const auto& [trans_red, trans_green, trans_blue] = transparent_color.value();
		settings.add_printable("Transparent Color", fmt::format("[Red {:d}, Green {:d}, Blue: {:d}]", trans_red, trans_green, trans_blue));
	}

    std::pair<std::array<int, 2>, std::array<int, 2>> clip_rect_info {surface.GetClipRectangle()};
    const auto& [clip_top_left_point, clip_area] = clip_rect_info;
    const auto& [clip_top_left_x, clip_top_left_y] = clip_top_left_point;
    const auto& [clip_width, clip_height] = clip_area;
    settings.add_printable("Clipping Rectangle", fmt::format("[Top Left X: {:d}, Top Left Y: {:d}, Width: {:d}, Height: {:d}]",
                                                             clip_top_left_x,
                                                             clip_top_left_y,
                                                             clip_width,
                                                             clip_height));

    output << settings.print();

    return output;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
