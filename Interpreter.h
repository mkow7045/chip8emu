#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Common.h"
#include <array>
#include <string_view>


class Interpreter
{
public:
	Interpreter(std::string& path);

	~Interpreter();

	void readFromFile();
private:
	std::array<uint8_t, 4096> m_Mem{};
};


#endif