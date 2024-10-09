#ifndef BLENDMODE_H
#define BLENDMODE_H

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
    }
}

#endif
