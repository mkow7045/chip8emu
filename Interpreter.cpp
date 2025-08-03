#include "Common.h"
#include "Interpreter.h"
#include <fstream>
#include <string>

Interpreter::Interpreter(std::string& path)
{
	std::ifstream inf{ path.c_str()};
	
	if (!inf)
	{

	}
}