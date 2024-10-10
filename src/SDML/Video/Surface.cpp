#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Surface.hpp"


SDML::Video::Surface::Surface(Window& window,
                              const std::filesystem::path& image_file): name{image_file.stem()},
                                                                        internal_SDL_surface{SDL_ConvertSurface(IMG_Load(image_file.string().c_str()),
                                                                                                                SDL_GetWindowSurface(window.Access_SDL_Backend())->format,
                                                                                                                0)} {}


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


std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Surface& surface)
{
    Misc::Printables settings {fmt::format("'{:s}' Surface", surface.GetName())};

    const auto& [red, green, blue, alpha] = surface.GetColor();
    settings.add_printable("Color", fmt::format("[Red: {:d}, Green: {:d}, Blue: {:d}, Alpha {:d}]", red, green, blue, alpha));

    output << settings.print();

    return output;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
