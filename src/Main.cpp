#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

// Custom Code from this project
#include "SDML/Subsystem.hpp"
#include "SDML/Video/Window.hpp"
#include "SDML/Video/Renderer.hpp"
#include "SDML/Video/Texture.hpp"

// Third-party Libraries
#include <SDL2/SDL.h>
#include <fmt/core.h>
#include <fmt/ranges.h>

// C++ Standard Libraries
#include <filesystem>
#include <iostream>


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);
	SDML::Image::Initialize(0);

	try
	{

		constexpr std::array<uint8_t, 4> white {0xFF, 0xFF, 0xFF, 0xFF};
		constexpr std::array<uint8_t, 4>   red {0xFF, 0x0,  0x0,  0xFF};
		constexpr std::array<uint8_t, 4> green {0x0,  0xFF, 0x0,  0xFF};
		constexpr std::array<uint8_t, 4>  blue {0x0,  0x0,  0xFF, 0xFF};

		SDML::Video::Window windowTest {"Test", 
										std::array<int, 2> {640, 480},
										SDML::Video::WindowInitFlag::RESIZABLE};

		SDML::Video::Renderer rendererTest {windowTest,
											SDML::Video::RendererInitFlag::ACCELERATED};

		SDML::Video::Texture example_texture {rendererTest,
											  std::filesystem::current_path().parent_path().parent_path()/"res"/"stretch.bmp"};

		constexpr std::pair<std::array<float, 2>, std::array<float, 2>> example_texture_copy_info {{0.0, 0.0},
																							   	   {320.0, 240.0}};

		rendererTest.Copy(example_texture, example_texture_copy_info);
		rendererTest.Update();

		std::cout << example_texture << std::endl;

		SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

	}
	catch(const std::exception& error_message)
	{
		std::cerr << error_message.what() << std::endl;
	}

	SDML::Image::Quit();
	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
