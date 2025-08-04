#include "Display.h"
#include "Common.h"



Display::Display(int ScreenWidth, int ScreenHeight)
	: m_ScreenWidth {ScreenWidth} , m_ScreenHeight {ScreenHeight}
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		m_isInitialized = false;
	}
	else
	{
		if (!SDL_CreateWindowAndRenderer("CHIP-8 Interpreter", m_ScreenWidth, m_ScreenHeight, 0, &g_Window, &g_Renderer))
		{
			SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			m_isInitialized = false;
		}
		else
		{
			SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
}


Display::~Display()
{
	SDL_DestroyRenderer(g_Renderer);
	SDL_DestroyWindow(g_Window);

	g_Renderer = nullptr;
	g_Window = nullptr;

	SDL_Quit();
}
