#ifndef BLENDMODE_H
#define BLENDMODE_H

// Third-Party Libraries
#include <SDL2/SDL.h>

//C++ Standard Libraries
#include <string>

namespace SDML
{
    namespace Video
    {
        enum class BlendMode
        {
            REPLACE,
            ALPHA,
            ADDITIVE,
            MODULATE,
            MULTIPLY,
            INVALID
        };

        BlendMode SDL_to_SDML(const SDL_BlendMode& input_mode);

        SDL_BlendMode SDML_to_SDL(const BlendMode& input_mode);

        std::string to_string(const BlendMode& mode);
    }
}

#endif
