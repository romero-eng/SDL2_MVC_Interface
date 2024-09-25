#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDML/Subsystem.hpp"

// C++ Standard Libraries
#include <iostream>


int main( int argc, char* args[] )
{

	SDML::Subsystem::Initialize(SDML::Subsystem::InitFlag::VIDEO);

	try
	{
		std::cout << SDML::Subsystem::IsInitialized(SDML::Subsystem::InitFlag::VIDEO) << std::endl;
		std::cout << SDML::Subsystem::IsInitialized(SDML::Subsystem::InitFlag::VIDEO | SDML::Subsystem::InitFlag::AUDIO) << std::endl;
		std::cout << SDML::Subsystem::IsInitialized(SDML::Subsystem::InitFlag::AUDIO) << std::endl;
	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	SDML::Subsystem::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
