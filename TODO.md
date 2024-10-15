# Potential API Improvements:

**General**
1. Split 4-int "Color" array int 3-int "Color" array and "Alpha" value \
&nbsp;&nbsp;- std::array<uint8_t, 4> SDML::Video::Renderer::GetDrawingColor const \
&nbsp;&nbsp;- void SDML::Video::Renderer::SetDrawingColor(std::array<uint8_t, 4>& color) \
&nbsp;&nbsp;- std::array<uint8_t, 4> SDML::Video::Surface::GetColor const \
&nbsp;&nbsp;- void SDML::Video::Surface::GetColor(std::array<uint8_t, 4>& color) \
&nbsp;&nbsp;- std::array<uint8_t, 4> SDML::Video::Texture::GetColor const \
&nbsp;&nbsp;- void SDML::Video::Texture::SetColor(std::array<uint8_t, 4>& color)

2. Add Stack Traces to customly thrown errors

**Renderer Class**:
1. Implement Rendering of Geometry (i.e., [SDL_RenderGeometry()](https://wiki.libsdl.org/SDL2/SDL_RenderGeometry) and [SDL_RenderGeometryRaw()](https://wiki.libsdl.org/SDL2/SDL_RenderGeometryRaw))
