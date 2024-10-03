#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H


// Third-party Libraries
#include <fmt/format.h>

// C++ Standard Libraries
#include <string>
#include <string_view>
#include <variant>
#include <vector>
#include <ranges>


namespace Misc
{
    class Printables
    {
        private:
            std::string title;
            std::vector<std::variant<Printables, std::pair<std::string, std::string>>> printables;
        
        public:
            Printables(const std::string& title): title{title}, printables{std::vector<std::variant<Printables, std::pair<std::string, std::string>>> {}} {}

            void add_printable(const char* key, bool value);

            void add_printable(const char* key, uint32_t value);

            void add_printable(const char* key, int value);

            void add_printable(const char* key, float value);

            void add_printable(const char* key, const char* value);

            void add_printable(const char* key, const std::string& value);

            void add_printable(const char* key, const std::vector<std::string>& value);

            void add_printable(Printables& printables);

            std::string print(std::size_t prior_level = 0);
    };
}

std::ostream& operator<<(std::ostream& output, Misc::Printables& printables);

#endif
