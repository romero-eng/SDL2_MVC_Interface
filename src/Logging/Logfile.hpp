#ifndef LOGFILE_H
#define LOGFILE_H


// Third-Party APIs
#include <fmt/format.h>

// C++ Standard Libraries
#include <fstream>
#include <filesystem>
#include <string_view>
#include <cstring>


namespace Logging
{
    class Logfile
    {
    private:

        std::shared_ptr<std::ofstream> output;

    public:

        Logfile(std::filesystem::path logfile_dir,
                std::string_view logfile_name);

        Logfile();

        void Write(const char* text);

        void Write(const std::string& text);

    };

    extern Logfile MainLogFile;
}



#endif
