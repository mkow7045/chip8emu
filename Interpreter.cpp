#include "Common.h"
#include "Interpreter.h"
#include "Opcode.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <bitset>
#include <iomanip>
#include <random>


Interpreter::Interpreter(std::string& path)
	: m_Path {path}
{
}

void Interpreter::setKey(uint8_t key)
{
	if (m_Keyboard[key] == false)
	{
		m_Keyboard[key] = true;
	}
	else
	{
		m_Keyboard[key] = false;
	}
}

bool Interpreter::readFromFile()
{
	constexpr size_t programStart{ 0x200 };
	std::ifstream inf{ m_Path.c_str(), std::ios::binary };

	if (!inf)
	{
		std::cerr << "Error opening file!\n";
		return false;
	}

	auto startIt{ m_Mem.begin() + programStart };
	auto endIt{ m_Mem.end() };

	auto bytesCopied = std::copy(
		std::istreambuf_iterator<char>(inf),
		std::istreambuf_iterator<char>(),
		startIt);

	if (std::distance(startIt, bytesCopied) > (m_Mem.size() - 0x200))
	{
		std::cerr << "ROM is too large\n";
		return false;
	}
	return true;
}

uint16_t Interpreter::fetchOpcode(uint8_t highByte, uint8_t lowByte)
{
	return (static_cast<uint16_t>(highByte) << 8) | lowByte;
}

void Interpreter::dumpMem()
{
	for (std::size_t index{ 0x200 }; index < m_Mem.size() - 1; ++index)
	{
		std::cerr << "0x" << std::hex << std::setw(4) << std::setfill('0') << fetchOpcode(m_Mem[index], m_Mem[index + 1]) << ' ';
	}
}

uint8_t Interpreter::randomNumber()
{
	std::mt19937 mt{ std::random_device{}() };

	std::uniform_int_distribution die255{0,255};

	return die255(mt);
}

void Interpreter::executeCycles(int cycles)
{
	for (int i{ 0 }; i < cycles; ++i)
	{
		Opcode opcode{ fetchOpcode(m_Mem[m_PC], m_Mem[m_PC + 1]) };

		// std::cerr << "0x" << std::hex << std::setw(4) << std::setfill('0') << opcode.full() << " ON BYTE NUMBER " << std::dec << m_PC << '\n';

		bool incrementPC{ true };

		uint8_t temp8{};
		uint16_t temp16{};

		switch (opcode.type())
		{
		case 0x0:
			switch (opcode.nnn())
			{
			case 0x0e0:
				g_Display.fill(std::array<bool, 32>{});
				break;
			case 0x0ee:
				m_PC = m_Stack[m_SP];
				--m_SP;
				incrementPC = false;
				break;
			}
			break;
		case 0x1:
			m_PC = opcode.nnn();
			incrementPC = false;
			break;
		case 0x2:
			++m_SP;
			m_Stack[m_SP] = m_PC + 2;
			m_PC = opcode.nnn();
			incrementPC = false;
			break;
		case 0x3:
			if (m_V[opcode.x()] == opcode.nn())
			{
				m_PC += 2;
			}
			break;
		case 0x4:
			if (!(m_V[opcode.x()] == opcode.nn()))
			{
				m_PC += 2;
			}
			break;
		case 0x5:
			if (m_V[opcode.x()] == m_V[opcode.y()])
			{
				m_PC += 2;
			}
			break;
		case 0x6:
			m_V[opcode.x()] = opcode.nn();
			break;
		case 0x7:
			m_V[opcode.x()] += opcode.nn();
			break;
		case 0x8:
			// 0x8 opcodes are differentiated by the last byte
			switch (opcode.n())
			{
			case 0x0:
				m_V[opcode.x()] = m_V[opcode.y()];
				break;
			case 0x1:
				temp8 = m_V[opcode.x()] | m_V[opcode.y()];
				m_V[opcode.x()] = temp8;
				break;
			case 0x2:
				temp8 = m_V[opcode.x()] & m_V[opcode.y()];
				m_V[opcode.x()] = temp8;
				break;
			case 0x3:
				temp8 = m_V[opcode.x()] ^ m_V[opcode.y()];
				m_V[opcode.x()] = temp8;
				break;
			case 0x4:
				temp16 = m_V[opcode.x()] + m_V[opcode.y()];
				if (temp16 > 255)
				{
					m_V[0xF] = 1;
				}
				else
				{
					m_V[0xF] = 0;
				}
				m_V[opcode.x()] = static_cast<uint8_t>(temp16 & 0x00FF);
				break;
			case 0x5:
				temp16 = m_V[opcode.x()] - m_V[opcode.y()];
				if (m_V[opcode.x()] > m_V[opcode.y()])
				{
					m_V[0xF] = 1;
				}
				else
				{
					m_V[0xF] = 0;
				}
				m_V[opcode.x()] = temp16;
				break;
			case 0x6:
				if (m_V[opcode.x()] & 0x1)
				{
					m_V[0xF] = 1;
				}
				else
				{
					m_V[0xF] = 0;
				}
				m_V[opcode.x()] >>= 1;
				break;
			case 0x7:
				temp16 = m_V[opcode.y()] - m_V[opcode.x()];
				if (m_V[opcode.x()] > m_V[opcode.y()])
				{
					m_V[0xF] = 1;
				}
				else
				{
					m_V[0xF] = 0;
				}
				m_V[opcode.x()] = temp16;
				break;
			case 0xE:
				if (m_V[opcode.x()] & 0b10000000)
				{
					m_V[0xF] = 1;
				}
				else
				{
					m_V[0xF] = 0;
				}
				m_V[opcode.x()] <<= 1;
				break;
			}
			break;

		case 0x9:
			if (m_V[opcode.x()] != m_V[opcode.y()])
			{
				m_PC += 2;
			}
			break;

		case 0xA:
			m_I = opcode.nnn();
			break;

		case 0xB:
			m_PC = opcode.nnn() + m_V[0x0];
			break;

		case 0xC:
			temp8 = randomNumber();
			temp8 &= opcode.nn();
			m_V[opcode.x()] = temp8;
			break;

		case 0xD:
		{
			m_V[0xF] = 0;
			for (int index{ 0 }; index < opcode.n(); ++index)
			{
				if (m_I + index >= m_Mem.size()) break;
				m_Sprite[index] = m_Mem[m_I + index];
			}
			uint8_t yCord{ m_V[opcode.y()] };
			for (int index{ 0 }; index < opcode.n(); ++index)
			{
				uint8_t xCord{ m_V[opcode.x()] };
				for (int bit{ 7 }; bit >= 0; --bit)
				{
					bool spritePixel = (m_Sprite[index] >> bit) & 1;
					if (spritePixel)
					{
						if (g_Display[xCord][yCord])
						{
							m_V[0xF] = 1;
						}
						g_Display[xCord][yCord] ^= 1;
					}
					xCord = (xCord + 1) % 64;
				}
				yCord = (yCord + 1) % 32;
			}
		}
		break;

		case 0xE:
			switch (opcode.nn())
			{
			case(0x9E):
				if (m_Keyboard[m_V[opcode.x()]])
					m_PC += 2;
				break;
			case(0xA1):
				if (!m_Keyboard[m_V[opcode.x()]])
					m_PC += 2;
				break;
			}
			break;
		case 0xF:
			switch (opcode.nn())
			{
			case 0x07:
				m_V[opcode.x()] = m_DT;
				break;
			case 0x0A:
			{
				incrementPC = false;
				for (int index{ 0 }; index < m_Keyboard.size(); ++index)
				{
					if (m_Keyboard[index] == true)
					{
						m_V[opcode.x()] = index;
						incrementPC = true;
					}
				}
			}
			break;
			case 0x15:
				m_DT = m_V[opcode.x()];
				break;
			case 0x18:
				m_ST = m_V[opcode.x()];
				break;
			case 0x1E:
				m_I += m_V[opcode.x()];
				break;
			case 0x29:
				// add this later
				break;
			case 0x33:
				m_Mem[m_I] = (m_V[opcode.x()] / 100) % 10;
				m_Mem[m_I + 1] = (m_V[opcode.x()] / 10) % 10;
				m_Mem[m_I + 2] = m_V[opcode.x()] % 10;
				break;
			case 0x55:
				for (int index{ 0 }; index < opcode.x(); ++index)
				{
					m_Mem[m_I + index] = m_V[index];
				}
				break;
			case 0x65:
				for (int index{ 0 }; index < opcode.x(); ++index)
				{
					m_V[index] = m_Mem[m_I + index];
				}
				break;
			}
		}


		if (incrementPC)
		{
			m_PC += 2;
		}
	}
}
