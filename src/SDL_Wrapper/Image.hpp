#ifndef IMAGE_WRAPPER_h
#define IMAGE_WRAPPER_h

#include <filesystem>
#include "Surface.hpp"

#include "Canvases/Texture.hpp"
#include "Canvases/Renderer.hpp"

#include "Rectangle.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>
namespace fs = std::filesystem;

namespace SDL
{

using PixelFormat = SDL_PixelFormat;

Uint32 MapRGB(const PixelFormat* format, Uint8 r, Uint8 g, Uint8 b);

Surface* Load_BMP(fs::path&& bitmap_path);

Surface* Load_BMP(fs::path& bitmap_path);

void BlitSurfaceOntoWindow(Window* window, Surface* src, const Rect* srcrect, Rect* dstrect);

void BlitSurface(Surface* src, const Rect* srcrect, Surface* dst, Rect* dstrect);

}

namespace IMG
{

enum class InitFlags : std::uint32_t
{
    JPG  = IMG_INIT_JPG,
    PNG  = IMG_INIT_PNG,
    TIF  = IMG_INIT_TIF,
    WEBP = IMG_INIT_WEBP,
    JXL  = IMG_INIT_JXL,
    AVIF = IMG_INIT_AVIF
};

void Init(InitFlags flag);

void Init(Uint32 flags);

SDL::Surface* LoadSurface(fs::path&& bitmap_path);

SDL::Surface* LoadSurface(fs::path& bitmap_path);

SDL::Textures::Texture* LoadTexture(fs::path&& bitmap_path, SDL::Rendering::Renderer* render);

SDL::Textures::Texture* LoadTexture(fs::path& bitmap_path, SDL::Rendering::Renderer* render);

void Quit(void);

}

Uint32 operator|(IMG::InitFlags first_flag, IMG::InitFlags second_flag);
Uint32 operator|(        Uint32 first_flag, IMG::InitFlags second_flag);
Uint32 operator|(IMG::InitFlags first_flag,         Uint32 second_flag);

#endif
