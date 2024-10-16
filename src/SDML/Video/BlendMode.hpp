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
        namespace Blending
        {
            enum class Mode
            {
                REPLACE,
                ALPHA,
                ADDITIVE,
                MODULATE,
                MULTIPLY,
                INVALID
            };

            Mode SDL_to_SDML(const SDL_BlendMode& input_mode);

            SDL_BlendMode SDML_to_SDL(const Mode& input_mode);

            std::string to_string(const Mode& mode);
        }
    }
}

#endif
