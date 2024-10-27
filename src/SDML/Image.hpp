#ifndef IMAGE_H
#define IMAGE_H

// Third-party Libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fmt/format.h>

// C++ Standard Libraries
#include <utility>
#include <array>
#include <string>
#include <string_view>

namespace SDML
{
	namespace Image
	{
		enum class FileType: uint32_t
		{
			JPG  = IMG_INIT_JPG,
			PNG  = IMG_INIT_PNG,
			TIF  = IMG_INIT_TIF,
			WEBP = IMG_INIT_WEBP,
			JXL  = IMG_INIT_JXL,
			AVIF = IMG_INIT_AVIF
		};

		void Initialize(uint32_t file_types);

		void Initialize(FileType file_type);

		bool IsInitialized(uint32_t file_types);

		bool IsInitialized(FileType file_type);

		void Quit();
	}
}

uint32_t operator|(const SDML::Image::FileType& first_file_type,
				   const SDML::Image::FileType& second_file_type);

uint32_t operator|(uint32_t first_file_type,
				   const SDML::Image::FileType& second_file_type);

uint32_t operator|(const SDML::Image::FileType& first_file_type,
				   uint32_t second_file_type);

#endif
