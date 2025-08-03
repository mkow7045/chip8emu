#ifndef DISPLAY_H
#define DISPLAY_H

#include "Common.h"

class Display
{
public:
	Display(int ScreenWidth, int ScreenHeight);

	~Display();

	bool isInitialized(){ return m_isInitialized; }
private:
	int m_ScreenWidth{ 640 };
	int m_ScreenHeight{ 480 };

	bool m_isInitialized{ true };
};

#endif