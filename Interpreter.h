#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Common.h"
#include <array>
#include <string>
#include <string_view>


class Interpreter
{
public:
	Interpreter(std::string& path);

	bool readFromFile();

	void dumpMem();

	uint16_t fetchOpcode(uint8_t highByte, uint8_t lowByte);

	void executeCycles(int cycles);

	uint8_t randomNumber();

	void setKey(uint8_t key);

	void decreaseDT()
	{
		if (m_DT > 0)
		{
			--m_DT;
		}
	}

	void decreaseST()
	{
		if (m_ST > 0)
		{
			--m_ST;
		}
	}

	uint8_t getST() const{ return m_ST; }

private:
	std::string m_Path{};
	std::array<uint8_t, 4096> m_Mem{};
	uint16_t m_PC{0x200};
	uint8_t m_SP{};
	std::array<uint16_t, 16> m_Stack{};
	std::array<uint8_t, 16> m_Sprite{};
	std::array<uint8_t, 16> m_V{};
	uint16_t m_I{};
	uint8_t m_DT{};
	uint8_t m_ST{};
	std::array<bool, 16> m_Keyboard{};
};


#endif