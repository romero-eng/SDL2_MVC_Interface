#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Logfile.hpp"


Misc::Logfile::Logfile(std::filesystem::path logfile_dir,
              		   std::string_view logfile_name): output{std::make_shared<std::ofstream>(logfile_dir/fmt::format("{:s}.log", logfile_name))} {}


void Misc::Logfile::WriteLine(const char* line) { this->output->write(fmt::format("{:s}\n", line).c_str(), static_cast<std::streamsize>(std::strlen(line) + 1)); }


void Misc::Logfile::WriteLine(const std::string& line) { this->WriteLine(line.c_str()); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
