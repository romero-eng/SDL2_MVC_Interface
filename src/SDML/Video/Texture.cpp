#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Texture.hpp"


SDML::Video::Texture::Texture(const char* name,
                              Renderer& renderer,
                              uint32_t pixel_format,
                              const Access& access,
                              const std::array<int, 2>& area): name{std::string{name}},
                                                               internal_SDL_texture{SDL_CreateTexture(renderer.Access_SDL_Backend(),
                                                                                                      pixel_format,
                                                                                                      std::to_underlying(access),
                                                                                                      area[0],
                                                                                                      area[1])},
                                                               internal_SDL_texture_ownership{true}
{
    if(this->internal_SDL_texture == nullptr){
        throw std::runtime_error(fmt::format("Could not create the '{:s}' Texture: {:s}",
                                             name,
                                             SDL_GetError()));
    } else {
        MainLogFile.Write(this->to_string());
    }
}


/*I should watch out for this constructor in the future, it may cause trouble later
 on with potential lack of deletion of SDL_Texture object.*/
SDML::Video::Texture::Texture(const char* name,
                              SDL_Texture* texture): name{std::string{name}},
                                                     internal_SDL_texture{texture},
                                                     internal_SDL_texture_ownership{false}
{
    if(this->internal_SDL_texture == nullptr){
        throw std::runtime_error(fmt::format("Could not create the '{:s}' Texture: {:s}",
                                             name,
                                             SDL_GetError()));
    } else {
        MainLogFile.Write(this->to_string());
    }
}


SDML::Video::Texture::Texture(Renderer& renderer,
                              Surface& surface): name{surface.GetName()},
                                                 internal_SDL_texture{SDL_CreateTextureFromSurface(renderer.Access_SDL_Backend(),
                                                                                                   surface.Access_SDL_Backend())},
                                                 internal_SDL_texture_ownership{true}
{
    if(this->internal_SDL_texture == nullptr){
        throw std::runtime_error(fmt::format("Could not create the '{:s}' Texture: {:s}",
                                             this->name,
                                             SDL_GetError()));
    } else {
        MainLogFile.Write(this->to_string());
    }
}


SDML::Video::Texture::Texture(Renderer& renderer,
                              const std::filesystem::path& image_file): name{image_file.stem()},
                                                                        internal_SDL_texture{IMG_LoadTexture(renderer.Access_SDL_Backend(),
                                                                                                             image_file.string().c_str())},
                                                                        internal_SDL_texture_ownership{true}
{
    if(this->internal_SDL_texture == nullptr){
        throw std::runtime_error(fmt::format("Could not create the '{:s}' Texture: {:s}",
                                             this->name,
                                             SDL_GetError()));
    } else {
        MainLogFile.Write(this->to_string());
    }
}


SDML::Video::Texture::Texture(): name{""},
                                 internal_SDL_texture{nullptr},
                                 internal_SDL_texture_ownership{false} {}


SDML::Video::Texture::Texture(const Texture& textureToCopy): name{textureToCopy.name},
                                                             internal_SDL_texture{textureToCopy.internal_SDL_texture},
                                                             internal_SDL_texture_ownership{false} {}


SDML::Video::Texture& SDML::Video::Texture::operator=(const Texture& textureToCopy)
{
    if(this != &textureToCopy) {
        this->name = textureToCopy.name;
        this->internal_SDL_texture = textureToCopy.internal_SDL_texture;
        this->internal_SDL_texture_ownership = false;
    }

    return *this;
}


SDML::Video::Texture::Texture(Texture&& textureToMove) noexcept: name{textureToMove.name},
                                                                 internal_SDL_texture{textureToMove.internal_SDL_texture},
                                                                 internal_SDL_texture_ownership{true}
{
    textureToMove.name = "";
    textureToMove.internal_SDL_texture = nullptr;
    textureToMove.internal_SDL_texture_ownership = false;
}


SDML::Video::Texture& SDML::Video::Texture::operator=(Texture&& textureToMove)
{
    if(this != &textureToMove) {
        this->name = textureToMove.name;
        this->internal_SDL_texture = textureToMove.internal_SDL_texture;
        this->internal_SDL_texture_ownership = true;
        textureToMove.internal_SDL_texture = nullptr;
        textureToMove.internal_SDL_texture_ownership = false;
    }

    return *this;
}


SDML::Video::Texture::~Texture()
{
    if(this->internal_SDL_texture != nullptr && this->internal_SDL_texture_ownership) {
        SDL_DestroyTexture(this->internal_SDL_texture);
    }
}


std::string SDML::Video::Texture::to_string() const
{
    std::string texture_access_string;
    switch(this->GetAccess()) {
        case Access::STATIC:
            texture_access_string = "Static";
            break;
        case Access::STREAMING:
            texture_access_string = "Streaming";
            break;
        case Access::TARGET:
            texture_access_string = "Target";
            break;
    }

    std::string scale_mode_string;
    switch(this->GetScaleMode()) {
        case ScaleMode::NEAREST:
            scale_mode_string = "Nearest";
            break;
        case ScaleMode::LINEAR:
            scale_mode_string = "Linear";
            break;
        case ScaleMode::BEST:
            scale_mode_string = "Best";
            break;
    }

    Logging::Printables printables {fmt::format("'{:s}' Texture", this->GetName())};

    std::string pixel_format {this->GetPixelFormatName()};
    printables.add_printable("Pixel Format Name", pixel_format);
    printables.add_printable(   "Texture Access", texture_access_string);

    const auto& [width, height] {this->GetArea()};
    printables.add_printable("Area", fmt::format("[Width: {:d}, Height: {:d}]", width, height));

    const auto& [red, green, blue, alpha] {this->GetColor()};
    printables.add_printable("Color", fmt::format("[Red: {:d}, Green: {:d}, Blue: {:d}, Alpha: {:d}]", red, green, blue, alpha));

    printables.add_printable("Blend Mode", Blending::to_string(this->GetBlendMode()));
    printables.add_printable("Scale Mode", scale_mode_string);

    return printables.print();
}


std::string SDML::Video::Texture::GetName() const { return this->name; }


std::string SDML::Video::Texture::GetPixelFormatName() const
{
    uint32_t pixel_format_uint;

    if(SDL_QueryTexture(this->internal_SDL_texture, &pixel_format_uint, nullptr, nullptr, nullptr) < 0) {
        throw std::runtime_error(fmt::format("Could not get the pixel format for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

	std::string pixel_format {SDL_GetPixelFormatName(pixel_format_uint)};

	if(pixel_format == "SDL_PIXELFORMAT_UNKNOWN") {
		throw fmt::format("Could not get the pixel format for the '{:s}' WIndow: {:s}",
						  this->GetName(),
						  SDL_GetError());
	}

	return pixel_format;
}


SDML::Video::Texture::Access SDML::Video::Texture::GetAccess() const
{
    Access access; 
    int tmp;

    if(SDL_QueryTexture(this->internal_SDL_texture, nullptr, &tmp, nullptr, nullptr) < 0) {
        throw std::runtime_error(fmt::format("Could not get the pixel format for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    switch(tmp) {
        case SDL_TEXTUREACCESS_STATIC:
            access = Access::STATIC;
            break;
        case SDL_TEXTUREACCESS_STREAMING:
            access = Access::STREAMING;
            break;
        case SDL_TEXTUREACCESS_TARGET:
            access = Access::TARGET;
            break;
    }

    return access;
}


std::array<int, 2> SDML::Video::Texture::GetArea() const
{
    int width;
    int height;

    if(SDL_QueryTexture(this->internal_SDL_texture, nullptr, nullptr, &width, &height) < 0) {
        throw std::runtime_error(fmt::format("Could not get the pixel format for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return std::array<int, 2> {width, height};
}


std::array<uint8_t, 4> SDML::Video::Texture::GetColor() const
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    if(SDL_GetTextureColorMod(this->internal_SDL_texture, &red, &green, &blue) < 0) {
        throw std::runtime_error(fmt::format("Could not get the RGB values for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    uint8_t alpha;
    if(SDL_GetTextureAlphaMod(this->internal_SDL_texture, &alpha) < 0) {
        throw std::runtime_error(fmt::format("Could not get the alpha value for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    return std::array<uint8_t, 4> {red, green, blue, alpha};
}


void SDML::Video::Texture::SetColor(const std::array<uint8_t, 4> color)
{
    const auto& [red, green, blue, alpha] = color;

    if(SDL_SetTextureColorMod(this->internal_SDL_texture, red, green, blue) < 0) {
        throw std::runtime_error(fmt::format("Could not set the RGB values for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    if(SDL_SetTextureAlphaMod(this->internal_SDL_texture, alpha) < 0) {
        throw std::runtime_error(fmt::format("Could not set the alpha value for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


SDML::Video::Blending::Mode SDML::Video::Texture::GetBlendMode() const
{
    SDL_BlendMode tmp;

    if(SDL_GetTextureBlendMode(this->internal_SDL_texture, &tmp) < 0) {
        std::runtime_error(fmt::format("Could not get the blend mode for the '{:s}' Texture: {:s}",
                                       this->GetName(),
                                       SDL_GetError()));
    }

    return Blending::SDL_to_SDML(tmp);
}


void SDML::Video::Texture::SetBlendMode(const Blending::Mode& mode)
{
    if(SDL_SetTextureBlendMode(this->internal_SDL_texture, Blending::SDML_to_SDL(mode)) < 0) {
        throw std::runtime_error(fmt::format("Could not set the blend mode for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


SDML::Video::Texture::ScaleMode SDML::Video::Texture::GetScaleMode() const
{
    SDL_ScaleMode tmp;
    if(SDL_GetTextureScaleMode(this->internal_SDL_texture, &tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not get the scale mode for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    ScaleMode mode;
    switch(tmp) {
        case SDL_ScaleModeNearest:
            mode = ScaleMode::NEAREST;
            break;
        case SDL_ScaleModeLinear:
            mode = ScaleMode::LINEAR;
            break;
        case SDL_ScaleModeBest:
            mode = ScaleMode::BEST;
            break;
    }

    return mode;
}


void SDML::Video::Texture::SetScaleMode(const ScaleMode& mode)
{
    SDL_ScaleMode tmp;

    switch(mode) {
        case ScaleMode::NEAREST:
            tmp = SDL_ScaleModeNearest;
            break;
        case ScaleMode::LINEAR:
            tmp = SDL_ScaleModeLinear;
            break;
        case ScaleMode::BEST:
            tmp = SDL_ScaleModeBest;
            break;
    }

    if(SDL_SetTextureScaleMode(this->internal_SDL_texture, tmp) < 0) {
        throw std::runtime_error(fmt::format("Could not set the scale mode for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }
}


SDL_Texture* SDML::Video::Texture::Access_SDL_Backend() { return this->internal_SDL_texture; }


std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Texture& texture)
{ return output << texture.to_string(); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
