#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H


// Third-party Libraries
#include <SDL2/SDL.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <string>
#include <string_view>
#include <variant>
#include <vector>
#include <ranges>


namespace Misc
{
    using allowed_value_types = \
        std::variant<bool,
                     Uint32,
                     int,
                     float,
                     const char*,
                     std::string,
                     std::string_view,
                     std::vector<std::string>>;

    std::string FormatKeyValuePairsForPrinting(const std::vector<std::pair<std::string, allowed_value_types>>& key_value_pairs);

    std::string FormatKeyValuePairsForPrinting(const std::vector<std::pair<std::string, allowed_value_types>>& key_value_pairs,
                                               const std::string& title);
}


#endif
