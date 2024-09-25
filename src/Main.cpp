
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include "SDML/Subsystem.hpp"


int main( int argc, char* args[] )
{

	SDML::Subsystems::Initialize(true);

	try
	{
		std::cout << SDML::Subsystems::QueryInitializations() << std::endl;
	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	SDML::Subsystems::Quit();

	return 0;
}


#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
