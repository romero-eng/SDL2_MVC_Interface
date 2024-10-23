#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Surface.hpp"


SDML::Video::Surface::YUV_CONVERSION_MODE SDML::Video::Surface::SDL_to_SDML(const SDL_YUV_CONVERSION_MODE& SDL_mode)
{
    YUV_CONVERSION_MODE mode;
    switch(SDL_mode){
        case SDL_YUV_CONVERSION_JPEG:
            mode = YUV_CONVERSION_MODE::JPEG;
            break;
        case SDL_YUV_CONVERSION_BT601:
            mode = YUV_CONVERSION_MODE::BT601;
            break;
        case SDL_YUV_CONVERSION_BT709:
            mode = YUV_CONVERSION_MODE::BT709;
            break;
        case SDL_YUV_CONVERSION_AUTOMATIC:
            mode = YUV_CONVERSION_MODE::AUTOMATIC;
            break;
    }

    return mode;
}


SDL_YUV_CONVERSION_MODE SDML::Video::Surface::SDML_to_SDL(const YUV_CONVERSION_MODE& mode)
{
    SDL_YUV_CONVERSION_MODE SDL_mode;
    switch(mode) {
        case YUV_CONVERSION_MODE::JPEG:
            SDL_mode = SDL_YUV_CONVERSION_JPEG;
            break;
        case YUV_CONVERSION_MODE::BT601:
            SDL_mode = SDL_YUV_CONVERSION_BT601;
            break;
        case YUV_CONVERSION_MODE::BT709:
            SDL_mode = SDL_YUV_CONVERSION_BT709;
            break;
        case YUV_CONVERSION_MODE::AUTOMATIC:
            SDL_mode = SDL_YUV_CONVERSION_AUTOMATIC;
            break;
    }

    return SDL_mode;
}


SDML::Video::Surface::YUV_CONVERSION_MODE SDML::Video::Surface::Get_YUV_ConversionMode() { return SDL_to_SDML(SDL_GetYUVConversionMode()); }


SDML::Video::Surface::YUV_CONVERSION_MODE SDML::Video::Surface::Get_YUV_ConversionModeForResolution(Window& window)
{
    const auto& [width, height] {window.GetDisplayArea()};

    return SDL_to_SDML(SDL_GetYUVConversionModeForResolution(width, height));
}


void SDML::Video::Surface::Set_YUV_ConversionMode(YUV_CONVERSION_MODE mode) { SDL_SetYUVConversionMode(SDML_to_SDL(mode)); }


std::string SDML::Video::Surface::to_string(YUV_CONVERSION_MODE mode)
{
    std::string YUV_string;
    switch(mode) {
        case YUV_CONVERSION_MODE::JPEG:
            YUV_string = "JPG";
            break;
        case YUV_CONVERSION_MODE::BT601:
            YUV_string = "BT601";
            break;
        case YUV_CONVERSION_MODE::BT709:
            YUV_string = "BT709";
            break;
        case YUV_CONVERSION_MODE::AUTOMATIC:
            YUV_string = "Automatic";
            break;
    }

    return YUV_string;
}


SDML::Video::Surface::Surface(Window& window,
                              const std::filesystem::path& image_file): name{image_file.stem()},
                                                                        internal_SDL_surface{SDL_ConvertSurface(IMG_Load(image_file.string().c_str()),
                                                                                                                SDL_GetWindowSurface(window.Access_SDL_Backend())->format,
                                                                                                                0)},
                                                                        internal_SDL_surface_ownership{true}
{
    if(this->internal_SDL_surface == nullptr){
        throw std::runtime_error(fmt::format("Could not create the '{:s}' Texture: {:s}",
                                             this->name,
                                             SDL_GetError()));
    }

    if(!(this->Has_RLE_Acceleration())){
        this->EnableOrDisable_RLE_Acceleration(true);
    }
}


SDML::Video::Surface::Surface(): name{""},
                                 internal_SDL_surface{nullptr},
                                 internal_SDL_surface_ownership{false} {}


SDML::Video::Surface::Surface(const Surface& surfaceToCopy): name {surfaceToCopy.name},
                                                             internal_SDL_surface{surfaceToCopy.internal_SDL_surface},
                                                             internal_SDL_surface_ownership{false} {}


SDML::Video::Surface& SDML::Video::Surface::operator=(const Surface& surfaceToCopy)
{
    if(this != &surfaceToCopy) {
        this->name = surfaceToCopy.name;
        this->internal_SDL_surface = surfaceToCopy.internal_SDL_surface;
        this->internal_SDL_surface_ownership = false;
    }

    return *this;
}


SDML::Video::Surface::Surface(Surface&& surfaceToMove) noexcept: name{surfaceToMove.name},
                                                                 internal_SDL_surface{surfaceToMove.internal_SDL_surface},
                                                                 internal_SDL_surface_ownership{true}
{
    surfaceToMove.name = "";
    surfaceToMove.internal_SDL_surface = nullptr;
    surfaceToMove.internal_SDL_surface_ownership = false;
}


SDML::Video::Surface& SDML::Video::Surface::operator=(Surface&& surfaceToMove)
{
    if(this != &surfaceToMove) {
        this->name = surfaceToMove.name;
        this->internal_SDL_surface = surfaceToMove.internal_SDL_surface;
        this->internal_SDL_surface_ownership = true;
        surfaceToMove.internal_SDL_surface = nullptr;
        surfaceToMove.internal_SDL_surface_ownership = false;
    }

    return *this;
}


SDML::Video::Surface::~Surface()
{
    if(this->internal_SDL_surface != nullptr && this->internal_SDL_surface_ownership) {
        SDL_FreeSurface(this->internal_SDL_surface);
    }
}


std::string SDML::Video::Surface::to_string() const
{
    Logging::Printables settings {fmt::format("'{:s}' Surface", this->GetName())};

    const auto& [width, height] {this->GetArea()};
    settings.add_printable("Area", fmt::format("[Width: {:d}, Height: {:d}]", width, height));

    const auto& [red, green, blue, alpha] {this->GetColor()};
    settings.add_printable("Color", fmt::format("[Red: {:d}, Green: {:d}, Blue: {:d}, Alpha {:d}]", red, green, blue, alpha));
    settings.add_printable("Blend Mode", Blending::to_string(this->GetBlendMode()));
    settings.add_printable("RLE Acceleration", this->Has_RLE_Acceleration());

    
	std::optional<std::array<uint8_t, 3>> transparent_color {this->GetTransparentColor()};
	if(transparent_color.has_value()){
		const auto& [trans_red, trans_green, trans_blue] = transparent_color.value();
		settings.add_printable("Transparent Color", fmt::format("[Red {:d}, Green {:d}, Blue: {:d}]", trans_red, trans_green, trans_blue));
	}

    const auto& [clip_top_left_point, clip_area] {this->GetClipRectangle()};
    const auto& [clip_top_left_x, clip_top_left_y] = clip_top_left_point;
    const auto& [clip_width, clip_height] = clip_area;
    settings.add_printable("Clipping Rectangle", fmt::format("[Top Left X: {:d}, Top Left Y: {:d}, Width: {:d}, Height: {:d}]",
                                                             clip_top_left_x,
                                                             clip_top_left_y,
                                                             clip_width,
                                                             clip_height));

    return settings.print();
}


std::string SDML::Video::Surface::GetName() const { return this->name; }


/* This function makes me feel uneasy since the fields I'm directly accessing
   are not officially documented anywhere I can see, but I think it's important
   to be able to see the area of the loaded surface.
*/
std::array<int, 2> SDML::Video::Surface::GetArea() const { return std::array<int, 2> {this->internal_SDL_surface->w, this->internal_SDL_surface->h}; }


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


SDML::Video::Blending::Mode SDML::Video::Surface::GetBlendMode() const
{
    SDL_BlendMode tmp;

    if(SDL_GetSurfaceBlendMode(this->internal_SDL_surface, &tmp) < 0) {
        std::runtime_error(fmt::format("Could not get the blend mode for the '{:s}' Texture: {:s}",
                                       this->GetName(),
                                       SDL_GetError()));
    }

    return Blending::SDL_to_SDML(tmp);
}


void SDML::Video::Surface::SetBlendMode(const Blending::Mode& mode)
{
    if(SDL_SetSurfaceBlendMode(this->internal_SDL_surface, Blending::SDML_to_SDL(mode)) < 0) {
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


bool SDML::Video::Surface::SetClipRectangle(const std::pair<std::array<int, 2>, std::array<int, 2>>& clip_rect_info)
{
    const auto& [top_left_point, area] = clip_rect_info;
    const auto& [top_left_x, top_left_y] = top_left_point;
    const auto& [width, height] = area;

    SDL_Rect tmp {top_left_x, top_left_y, width, height};

    return SDL_SetClipRect(this->internal_SDL_surface, &tmp);
}


void SDML::Video::Surface::DisableClipping() { SDL_SetClipRect(this->internal_SDL_surface, nullptr); }


void SDML::Video::Surface::Blit(Surface& src,
								const std::pair<std::array<int, 2>, std::array<int, 2>>& dst_rect_info,
								const std::pair<std::array<int, 2>, std::array<int, 2>>& src_rect_info)
{
	const auto& [dst_top_left_point, dst_area] = dst_rect_info;
	const auto& [dst_top_left_x, dst_top_left_y] = dst_top_left_point;
	const auto& [dst_width, dst_height] = dst_area;

	SDL_Rect dst_rect {dst_top_left_x, dst_top_left_y, dst_width, dst_height};

	const auto& [src_top_left_point, src_area] = src_rect_info;
	const auto& [src_top_left_x, src_top_left_y] = src_top_left_point;
	const auto& [src_width, src_height] = src_area;

	SDL_Rect src_rect {src_top_left_x, src_top_left_y, src_width, src_height};

	if(SDL_UpperBlit(src.Access_SDL_Backend(), &src_rect, this->internal_SDL_surface, &dst_rect) < 0) {
		throw std::runtime_error(fmt::format("Could not blit '{:s}' Surface onto the '{:s}' Surface: {:s}",
                                             src.GetName(),
											 this->GetName(),
											 SDL_GetError()));
	}
}


void SDML::Video::Surface::Blit(Surface& src)
{
	const auto& [src_width, src_height] {src.GetArea()};
	const auto& [dst_width, dst_height] {this->GetArea()};

	if(src_width*src_height >= dst_width*dst_height){
		if(SDL_UpperBlit(src.Access_SDL_Backend(), nullptr, this->internal_SDL_surface, nullptr) < 0) {
			throw std::runtime_error(fmt::format("Could not blit '{:s}' Surface onto the '{:s}' Surface: {:s}",
                                                 src.GetName(),
												 this->GetName(),
												 SDL_GetError()));
		}
	} else {
		if(SDL_UpperBlitScaled(src.Access_SDL_Backend(), nullptr, this->internal_SDL_surface, nullptr) < 0) {
			throw std::runtime_error(fmt::format("Could not blit '{:s}' Surface onto the '{:s}' Window: {:s}",
                                                 src.GetName(),
												 this->GetName(),
												 SDL_GetError()));
		}
	}
}


SDL_Surface* SDML::Video::Surface::Access_SDL_Backend() { return this->internal_SDL_surface; }


std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Surface& surface)
{ return output << surface.to_string(); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
