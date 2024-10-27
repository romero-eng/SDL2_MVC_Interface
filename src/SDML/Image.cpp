#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)
#include "Image.hpp"


void SDML::Image::Initialize(FileType file_type) { return Initialize(std::to_underlying(file_type)); }


void SDML::Image::Initialize(uint32_t file_types)
{
	if(file_types != static_cast<uint32_t>(IMG_Init(static_cast<int>(file_types)))) {

		constexpr std::array<std::pair<std::string_view, FileType>, 6> image_file_types {{{"JPG",  FileType::JPG},
																						  {"PNG",  FileType::PNG},
																						  {"TIF",  FileType::TIF},
																						  {"WEBP", FileType::WEBP},
																						  {"JXL",  FileType::JXL},
																						  {"AVIF", FileType::AVIF}}};

		std::string err_msg {fmt::format("Could not initialize image type: {:s}", SDL_GetError())};
		for(std::pair<std::string_view, FileType> image_file_type: image_file_types) {
			err_msg += fmt::format("{:s}: {:s}\n", image_file_type.first, IsInitialized(image_file_type.second) ? "On" : "Off");
		}

		throw err_msg;
	}
}


bool SDML::Image::IsInitialized(uint32_t file_types) { return file_types == (file_types & SDL_WasInit(file_types)); }


bool SDML::Image::IsInitialized(FileType file_type) { return IsInitialized(std::to_underlying(file_type)); }


void SDML::Image::Quit() { IMG_Quit(); }


uint32_t operator|(const SDML::Image::FileType& first_file_type,
				   const SDML::Image::FileType& second_file_type)
{ return std::to_underlying(first_file_type) | std::to_underlying(second_file_type); }


uint32_t operator|(uint32_t first_file_type,
				   const SDML::Image::FileType& second_file_type)
{ return first_file_type | std::to_underlying(second_file_type); }


uint32_t operator|(const SDML::Image::FileType& first_file_type,
				   uint32_t second_file_type)
{ return std::to_underlying(first_file_type) | second_file_type; }


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
