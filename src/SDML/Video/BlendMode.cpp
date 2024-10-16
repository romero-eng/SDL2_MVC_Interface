#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "BlendMode.hpp"


SDML::Video::Blending::Mode SDML::Video::Blending::SDL_to_SDML(const SDL_BlendMode& input_mode)
{
    Mode return_mode;

    switch(input_mode) {
        case SDL_BlendMode::SDL_BLENDMODE_NONE:
            return_mode = Mode::REPLACE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_BLEND:
            return_mode = Mode::ALPHA;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_ADD:
            return_mode = Mode::ADDITIVE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_MOD:
            return_mode = Mode::MODULATE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_MUL:
            return_mode = Mode::MODULATE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_INVALID:
            return_mode = Mode::INVALID;
            break;
    }

    return return_mode;
}


SDL_BlendMode SDML::Video::Blending::SDML_to_SDL(const Mode& input_mode)
{
    SDL_BlendMode return_mode;

    switch(input_mode) {
        case Mode::REPLACE:
            return_mode = SDL_BLENDMODE_NONE;
            break;
        case Mode::ALPHA:
            return_mode = SDL_BLENDMODE_BLEND;
            break;
        case Mode::ADDITIVE:
            return_mode = SDL_BLENDMODE_ADD;
            break;
        case Mode::MODULATE:
            return_mode = SDL_BLENDMODE_MOD;
            break;
        case Mode::MULTIPLY:
            return_mode = SDL_BLENDMODE_MUL;
            break;
        case Mode::INVALID:
            return_mode = SDL_BLENDMODE_INVALID;
            break;
    }

    return return_mode;
}


std::string SDML::Video::Blending::to_string(const Mode& mode)
{
    std::string blend_mode_string; 
    switch(mode)
    {
        case Mode::REPLACE:
            blend_mode_string = "Replace";
            break;
        case Mode::ALPHA:
            blend_mode_string = "Alpha";
            break;
        case Mode::ADDITIVE:
            blend_mode_string = "Additive";
            break;
        case Mode::MODULATE:
            blend_mode_string = "Modulate";
            break;
        case Mode::MULTIPLY:
            blend_mode_string = "Multiply";
            break;
        case Mode::INVALID:
            blend_mode_string = "Invalid";
            break;
    }

    return blend_mode_string;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
