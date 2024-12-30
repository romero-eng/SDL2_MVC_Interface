# Potential API Improvements:

**General**

1. Add Stack Traces to customly thrown errors

2. Add std::swap() to Move semantics for Texture, Surface, Renderer, and Window classes

**Renderer Class**:
1. Implement Rendering of Geometry (i.e., [SDL_RenderGeometry()](https://wiki.libsdl.org/SDL2/SDL_RenderGeometry) and [SDL_RenderGeometryRaw()](https://wiki.libsdl.org/SDL2/SDL_RenderGeometryRaw))

**Rotated Ellipse Drawing Algorithm**

1. Use std::list (i.e., linked list) instead of std::vector (i.e., dynamic vector)

2. Created nested functions for calculating rotated ellipse to get past numerical instability

**Even-Odd Ray-casting**

1. Rewrite even-odd ray-casting to be more clear and potentially use less resources

2. Maybe rewrite circle and unrotated ellipses to automatically give spaces?
