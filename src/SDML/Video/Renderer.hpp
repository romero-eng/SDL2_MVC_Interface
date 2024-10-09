#ifndef RENDERER_H
#define RENDERER_H

// Custom Code from this project
#include "Window.hpp"
#include "Texture.hpp"
#include "BlendMode.hpp"
#include "../../Misc/PrettyPrint.hpp"

// Third-Party Libraries
#include <SDL2/SDL.h>
#include <fmt/format.h>

//C++ Standard Libraries
#include <array>
#include <vector>


namespace SDML
{
    namespace Video
    {
        enum class RendererInitFlag: uint32_t
        {
            SOFTWARE      = SDL_RENDERER_SOFTWARE,
            ACCELERATED   = SDL_RENDERER_ACCELERATED,
            PRESENTVSYNC  = SDL_RENDERER_PRESENTVSYNC,
            TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
        };

        class Texture;

        class Renderer
        {
        private:
            SDL_Renderer* internal_SDL_renderer;

        public:

            Renderer(Window& window,
                     uint32_t flags);

            Renderer(Window& window,
                     const RendererInitFlag& flag);

            Renderer(Window& window);

            Renderer(Renderer&) = delete;

            Renderer& operator=(Renderer&) = delete;

            ~Renderer();

            bool CheckInitFlags(uint32_t flags) const;

            bool CheckInitFlags(const RendererInitFlag& flag) const;
            
            void ToggleVSync(bool enable_or_disable);

            std::string GetName() const;

            std::array<int, 2> GetArea() const;

            std::array<uint8_t, 4> GetDrawingColor() const;

            void SetDrawingColor(const std::array<uint8_t, 4>& color);

            BlendMode GetBlendMode () const;

            void SetBlendMode(const BlendMode& mode);

            std::pair<std::array<int, 2>, std::array<int, 2>> GetViewPort() const;

            void SetViewPort(const std::pair<std::array<int, 2>, std::array<int, 2>>& rect_info);

            std::optional<std::pair<std::array<int, 2>, std::array<int, 2>>> GetClippingRectangle() const;

            void SetClippingRectangle(const std::pair<std::array<int, 2>, std::array<int, 2>>& clip_rect_info);

            void DisableClipping();

            bool CheckClippingEnabled() const;

            std::array<float, 2> GetScale() const;

            void SetScale(const std::array<float, 2>& scale);

            bool CheckIntegerScale() const;

            void ToggleIntegerScale(bool enable_or_disable);

            std::optional<std::array<int, 2>> GetLogicalArea() const;

            void SetLogicalArea(const std::array<int, 2>& area);

            std::array<int, 2> ConvertLogicalPointToRealPoint(std::array<float, 2> logical_point);

            std::array<float, 2> ConvertRealPointToLogicalPoint(std::array<int, 2> real_point);

            std::array<int, 2> GetMaxTextureArea() const;

            std::vector<std::string> GetTextureFormats() const;

            Texture GetTarget();

            void DrawPoint(const std::array<int, 2>& point);

            void DrawPoint(const std::array<float, 2>& point);

            void DrawPoints(const std::vector<std::array<int, 2>>& points);

            void DrawPoints(const std::vector<std::array<float, 2>>& points);

            void DrawLine(const std::array<std::array<int, 2>, 2>& line);

            void DrawLine(const std::array<std::array<float, 2>, 2>& line);

            void DrawConnectedLines(const std::vector<std::array<int, 2>>& line_points);

            void DrawConnectedLines(const std::vector<std::array<float, 2>>& line_points);

            void DrawRectangleOutline(const std::pair<std::array<int, 2>, std::array<int, 2>>& rect_info);

            void DrawRectangleOutline(const std::pair<std::array<float, 2>, std::array<float, 2>>& rect_info);

            void DrawRectangleOutlines(const std::vector<std::pair<std::array<int, 2>, std::array<int, 2>>>& rects_info);

            void DrawRectangleOutlines(const std::vector<std::pair<std::array<float, 2>, std::array<float, 2>>>& rects_info);

            void DrawRectangle(const std::pair<std::array<int, 2>, std::array<int, 2>>& rect_info);

            void DrawRectangle(const std::pair<std::array<float, 2>, std::array<float, 2>>& rect_info);

            void DrawRectangles(const std::vector<std::pair<std::array<int, 2>, std::array<int, 2>>>& rects_info);

            void DrawRectangles(const std::vector<std::pair<std::array<float, 2>, std::array<float, 2>>>& rects_info);

            void DrawEntireTarget();

            void Copy(Texture& texture);

            void Update();

            SDL_Renderer* Access_SDL_Backend();
        };
    }
}

uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, const SDML::Video::RendererInitFlag& second_flag);

uint32_t operator|(uint32_t first_flag, const SDML::Video::RendererInitFlag& second_flag);

uint32_t operator|(const SDML::Video::RendererInitFlag& first_flag, uint32_t second_flag);

std::ostream& operator<<(std::ostream& output,
                         const SDML::Video::Renderer& renderer);

#endif
