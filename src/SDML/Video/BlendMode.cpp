#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "BlendMode.hpp"


SDML::Video::BlendMode SDML::Video::SDL_to_SDML(const SDL_BlendMode& input_mode)
{
    BlendMode return_mode;

    switch(input_mode) {
        case SDL_BlendMode::SDL_BLENDMODE_NONE:
            return_mode = BlendMode::REPLACE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_BLEND:
            return_mode = BlendMode::ALPHA;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_ADD:
            return_mode = BlendMode::ADDITIVE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_MOD:
            return_mode = BlendMode::MODULATE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_MUL:
            return_mode = BlendMode::MODULATE;
            break;
        case SDL_BlendMode::SDL_BLENDMODE_INVALID:
            return_mode = BlendMode::INVALID;
            break;
    }

    return return_mode;
}


SDL_BlendMode SDML::Video::SDML_to_SDL(const BlendMode& input_mode)
{
    SDL_BlendMode return_mode;

    switch(input_mode) {
        case BlendMode::REPLACE:
            return_mode = SDL_BLENDMODE_NONE;
            break;
        case BlendMode::ALPHA:
            return_mode = SDL_BLENDMODE_BLEND;
            break;
        case BlendMode::ADDITIVE:
            return_mode = SDL_BLENDMODE_ADD;
            break;
        case BlendMode::MODULATE:
            return_mode = SDL_BLENDMODE_MOD;
            break;
        case BlendMode::MULTIPLY:
            return_mode = SDL_BLENDMODE_MUL;
            break;
        case BlendMode::INVALID:
            return_mode = SDL_BLENDMODE_INVALID;
            break;
    }

    return return_mode;
}


std::string SDML::Video::to_string(const BlendMode& mode)
{
    std::string blend_mode_string; 
    switch(mode)
    {
        case BlendMode::REPLACE:
            blend_mode_string = "Replace";
            break;
        case BlendMode::ALPHA:
            blend_mode_string = "Alpha";
            break;
        case BlendMode::ADDITIVE:
            blend_mode_string = "Additive";
            break;
        case BlendMode::MODULATE:
            blend_mode_string = "Modulate";
            break;
        case BlendMode::MULTIPLY:
            blend_mode_string = "Multiply";
            break;
        case BlendMode::INVALID:
            blend_mode_string = "Invalid";
            break;
    }

    return blend_mode_string;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
