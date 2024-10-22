#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Logfile.hpp"


Misc::Logfile::Logfile(std::filesystem::path logfile_dir,
              		   std::string_view logfile_name): output{std::make_shared<std::ofstream>(logfile_dir/fmt::format("{:s}.log", logfile_name))} {}


void Misc::Logfile::Write(const char* text) { this->output->write(fmt::format("{:s}\n", text).c_str(), static_cast<std::streamsize>(std::strlen(text) + 1)); }


void Misc::Logfile::Write(const std::string& text) { this->Write(text.c_str()); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
