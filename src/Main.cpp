
#if defined(__linux__) || defined(_WIN32) || defined(__APPLE__)

#include <string>
#include <iostream>
#include <utility>


int main( int argc, char* args[] )
{

	try
	{

	}
	catch(std::string error_message)
	{
		std::cerr << error_message;
	}

	return 0;
}

#else
#error "This file is only meant to be compiled on a Windows, Macintosh, or Linux OS"
#endif
