
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "AcceleratedPaintbrush.hpp"


SDL::Painting::Equipment::AcceleratedPaintbrush::AcceleratedPaintbrush(Canvas& canvas,
                                                                       int index,
                                                                       AcceleratedPaintbrushFlags flag,
                                                                       Uint8 r,
                                                                       Uint8 g,
                                                                       Uint8 b,
                                                                       Uint8 a): AcceleratedPaintbrush::AcceleratedPaintbrush(canvas,
                                                                                                                              index,
                                                                                                                              std::to_underlying(flag),
                                                                                                                              r, g, b, a) {}


SDL::Painting::Equipment::AcceleratedPaintbrush::AcceleratedPaintbrush(Canvas& canvas,
                                                                       int index,
                                                                       Uint32 flags,
                                                                       Uint8 r,
                                                                       Uint8 g,
                                                                       Uint8 b,
                                                                       Uint8 a): paintbrush_renderer{SDL_CreateRenderer(canvas.Access_SDL_Implementation(), index, flags)}
{   
    if (this->paintbrush_renderer == nullptr)
    {
        throw fmt::format("Renderer could not be created for the '{:s}' Window:\n\n{:s}\n", canvas.GetTitle(), SDL_GetError());
    }

    this->SetPaintingColor(r, g, b, a);
    this->Clear();

    canvas.setAcceleratedPaintbrush(*this);
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::Clear()
{
    if (SDL_RenderClear(this->paintbrush_renderer) < 0)
    {
        throw fmt::format("Could not clear the Renderer: {:s}", SDL_GetError());
    }
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::PaintImageOverArea(Image::AcceleratedImage& image,
                                                                         const Rect* imageArea,
                          		        	    	                     const Rect* canvasArea)
{
    if (SDL_RenderCopy(this->paintbrush_renderer, image.Access_SDL_Implementation(), imageArea, canvasArea) < 0)
    {
        throw fmt::format("Could not copy the Accelerated Picture with the Paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::PaintImage(Image::AcceleratedImage& image) { this->PaintImageOverArea(image, nullptr, nullptr); }


void SDL::Painting::Equipment::AcceleratedPaintbrush::PaintImageOverArea(Image::AcceleratedImage& image, const Rect& imageArea, const Rect& canvasArea) { this->PaintImageOverArea(image, &imageArea, &canvasArea); }


void SDL::Painting::Equipment::AcceleratedPaintbrush::SetPaintingColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    if(SDL_SetRenderDrawColor(this->paintbrush_renderer, r, g, b, a) < 0)
    {
        throw fmt::format("Could not set colors for Paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::PaintPoint(int x1, int y1)
{
    if(SDL_RenderDrawPoint(this->paintbrush_renderer, x1, y1) < 0)
    {
        throw fmt::format("Could not draw point with accelerated paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::PaintLine(int x1, int y1, int x2, int y2)
{
    if(SDL_RenderDrawLine(this->paintbrush_renderer, x1, y1, x2, y2) < 0)
    {
        throw fmt::format("Could not draw line with accelerated paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::PaintEmptyRectangle(const Rect& area)
{
    if(SDL_RenderDrawRect(this->paintbrush_renderer, &area) < 0)
    {
        throw fmt::format("Could not fill in rectangular area with accelerated paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::PaintRectangle(const Rect& area)
{
    if(SDL_RenderFillRect(this->paintbrush_renderer, &area) < 0)
    {
        throw fmt::format("Could not fill in rectangular area with accelerated paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::ReservePaintingArea(const Rect& area)
{
    if(SDL_RenderSetViewport(this->paintbrush_renderer, &area) < 0)
    {
        throw fmt::format("Could not set view port with accelerated paintbrush: {:s}", SDL_GetError());
    }
}


void SDL::Painting::Equipment::AcceleratedPaintbrush::Fill()
{
    if(SDL_RenderFillRect(this->paintbrush_renderer, nullptr) < 0)
    {
        throw fmt::format("Could not fill in entire canvas with accelerated paintbrush: {:s}", SDL_GetError());
    }
}


SDL_Renderer* SDL::Painting::Equipment::AcceleratedPaintbrush::Access_SDL_Implementation() { return this->paintbrush_renderer; }


SDL::Painting::Equipment::AcceleratedPaintbrush::~AcceleratedPaintbrush()
{
    SDL_DestroyRenderer(this->paintbrush_renderer);
    this->paintbrush_renderer = nullptr;
}


Uint32 operator|(SDL::Painting::Equipment::AcceleratedPaintbrushFlags first_flag,
                 SDL::Painting::Equipment::AcceleratedPaintbrushFlags second_flag)
{
    return std::to_underlying(first_flag) | std::to_underlying(second_flag);
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
