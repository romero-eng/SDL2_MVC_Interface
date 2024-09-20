
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "AcceleratedPaintbrush.hpp"


SDL::Painting::AcceleratedPaintbrush::AcceleratedPaintbrush(Canvas& canvas,
                                                            int index,
                                                            AcceleratedPaintbrushFlags flag,
                                                            Uint8 r,
                                                            Uint8 g,
                                                            Uint8 b,
                                                            Uint8 a): AcceleratedPaintbrush::AcceleratedPaintbrush(canvas,
                                                                                                                   index,
                                                                                                                   std::to_underlying(flag),
                                                                                                                   r, g, b, a) {}


SDL::Painting::AcceleratedPaintbrush::AcceleratedPaintbrush(Canvas& canvas,
                                                            int index,
                                                            Uint32 flags,
                                                            Uint8 r,
                                                            Uint8 g,
                                                            Uint8 b,
                                                            Uint8 a): picture_renderer{SDL_CreateRenderer(canvas.Access_SDL_Implementation(), index, flags)}
{   
    if (this->picture_renderer == nullptr)
    {
        throw fmt::format("Renderer could not be created for the '{:s}' Window:\n\n{:s}\n", canvas.GetTitle(), SDL_GetError());
    }
    else
    {
        this->SetDrawColor(r, g, b, a);
    }
}


void SDL::Painting::AcceleratedPaintbrush::SetDrawColor(Uint8 r,
                                                        Uint8 g,
                                                        Uint8 b,
                                                        Uint8 a)
{
    if(SDL_SetRenderDrawColor(this->picture_renderer, r, g, b, a) < 0)
    {
        throw fmt::format("Could not set colors for Paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::AcceleratedPaintbrush::Clear()
{
    if (SDL_RenderClear(this->picture_renderer) < 0)
    {
        throw fmt::format("Could not clear the Renderer: {:s}", SDL_GetError());
    }
}


void SDL::Painting::AcceleratedPaintbrush::Copy(AcceleratedPicture& picture)
{
    this->Copy(picture, nullptr, nullptr);
}


void SDL::Painting::AcceleratedPaintbrush::Copy(AcceleratedPicture& picture,
                                                const Rect* srcrect,
                          				        const Rect* dstrect)
{
    if (SDL_RenderCopy(this->picture_renderer, picture.Access_SDL_Implementation(), srcrect, dstrect) < 0)
    {
        throw fmt::format("Could not copy the Accelerated Picture with the Paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::AcceleratedPaintbrush::Present()
{
    SDL_RenderPresent(this->picture_renderer);
}


SDL_Renderer* SDL::Painting::AcceleratedPaintbrush::Access_SDL_Implementation()
{
    return this->picture_renderer;
}


SDL::Painting::AcceleratedPaintbrush::~AcceleratedPaintbrush() { SDL_DestroyRenderer(this->picture_renderer); }


Uint32 operator|(SDL::Painting::AcceleratedPaintbrushFlags first_flag,
                 SDL::Painting::AcceleratedPaintbrushFlags second_flag)
{
    return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
