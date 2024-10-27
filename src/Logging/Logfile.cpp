#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Logfile.hpp"


Logging::Logfile Logging::MainLogFile;

std::chrono::time_point<std::chrono::system_clock> Logging::init_time_point;


Logging::Logfile::Logfile(std::filesystem::path logfile_dir,
              		      std::string_view logfile_name): output{std::make_shared<std::ofstream>(logfile_dir/fmt::format("{:s}.log", logfile_name))} {}


Logging::Logfile::Logfile(): output{nullptr} {}


void Logging::Logfile::Write(const char* text) { this->output->write(fmt::format("{:s}\n", text).c_str(), static_cast<std::streamsize>(std::strlen(text) + 1)); }


void Logging::Logfile::Write(const std::string& text) { this->Write(text.c_str()); }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
