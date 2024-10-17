# Potential API Improvements:

**General**
1. Split 4-int "Color" array int 3-int "Color" array and "Alpha" value, with "Alpha" value and "Blending Mode" having default parameters \
&nbsp;&nbsp;- std::array<uint8_t, 4> SDML::Video::Renderer::GetDrawingColor const \
&nbsp;&nbsp;- void SDML::Video::Renderer::SetDrawingColor(std::array<uint8_t, 4>& color) \
&nbsp;&nbsp;- std::array<uint8_t, 4> SDML::Video::Surface::GetColor const \
&nbsp;&nbsp;- void SDML::Video::Surface::GetColor(std::array<uint8_t, 4>& color) \
&nbsp;&nbsp;- std::array<uint8_t, 4> SDML::Video::Texture::GetColor const \
&nbsp;&nbsp;- void SDML::Video::Texture::SetColor(std::array<uint8_t, 4>& color)

2. Add Stack Traces to customly thrown errors

3. Change name of SDML::Image::InitFlag scoped enumeration to reflect its true nature as initialization of libraries which load image file types

4. Change various scoped enumerations within Window class to act more like SDML::Video::Blending::Mode enumeration instead

**Renderer Class**:
1. Implement Rendering of Geometry (i.e., [SDL_RenderGeometry()](https://wiki.libsdl.org/SDL2/SDL_RenderGeometry) and [SDL_RenderGeometryRaw()](https://wiki.libsdl.org/SDL2/SDL_RenderGeometryRaw))
