#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Texture.hpp"


SDML::Video::Texture::Texture(const char* name,
                              Renderer& renderer,
                              uint32_t pixel_format,
                              const TextureAccess& access,
                              const std::array<int, 2>& area): name{std::string{name}},
                                                               internal_SDL_texture{SDL_CreateTexture(renderer.Access_SDL_Backend(),
                                                                                                      pixel_format,
                                                                                                      std::to_underlying(access),
                                                                                                      area[0],
                                                                                                      area[1])} {}


SDML::Video::Texture::Texture(const char* name,
                              SDL_Texture* texture): name{std::string{name}},
                                                     internal_SDL_texture{texture} {}


SDML::Video::Texture::Texture(Renderer& renderer,
                              const std::filesystem::path& image_file): name{image_file.stem()},
                                                                        internal_SDL_texture{IMG_LoadTexture(renderer.Access_SDL_Backend(),
                                                                                                             image_file.string().c_str())} {}


SDML::Video::Texture::~Texture() { SDL_DestroyTexture(this->internal_SDL_texture); }


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


SDML::Video::TextureAccess SDML::Video::Texture::GetTextureAccess() const
{
    TextureAccess access; 
    int tmp;

    if(SDL_QueryTexture(this->internal_SDL_texture, nullptr, &tmp, nullptr, nullptr) < 0) {
        throw std::runtime_error(fmt::format("Could not get the pixel format for the '{:s}' Texture: {:s}",
                                             this->GetName(),
                                             SDL_GetError()));
    }

    switch(tmp) {
        case SDL_TEXTUREACCESS_STATIC:
            access = TextureAccess::STATIC;
            break;
        case SDL_TEXTUREACCESS_STREAMING:
            access = TextureAccess::STREAMING;
            break;
        case SDL_TEXTUREACCESS_TARGET:
            access = TextureAccess::TARGET;
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


SDL_Texture* SDML::Video::Texture::Access_SDL_Backend() { return this->internal_SDL_texture; }


std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Texture& texture)
{
    std::string texture_access_string;
    switch(texture.GetTextureAccess()) {
        case SDML::Video::TextureAccess::STATIC:
            texture_access_string = "Static";
            break;
        case SDML::Video::TextureAccess::STREAMING:
            texture_access_string = "Streaming";
            break;
        case SDML::Video::TextureAccess::TARGET:
            texture_access_string = "Target";
            break;
    }

    Misc::Printables printables {fmt::format("'{:s}' Texture", texture.GetName())};

    std::string pixel_format {texture.GetPixelFormatName()};
    printables.add_printable("Pixel Format Name", pixel_format);
    printables.add_printable(   "Texture Access", texture_access_string);

    std::array<int, 2> area {texture.GetArea()};
    const auto& [width, height] = area;
    printables.add_printable("Area", fmt::format("[Width: {:d}, Height: {:d}]", width, height));

    std::array<uint8_t, 4> color {texture.GetColor()};
    const auto& [red, green, blue, alpha] = color;
    printables.add_printable("Color", fmt::format("[Red: {:d}, Green: {:d}, Blue: {:d}, Alpha: {:d}]", red, green, blue, alpha));

    output << printables.print();

    return output;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
