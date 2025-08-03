#include "Common.h"
#include "Display.h"
#include "Texture.h"
#include "Interpreter.h"
#include <array>
#include <iostream>


SDL_Window* g_Window = nullptr;
SDL_Renderer* g_Renderer = nullptr;
std::array<std::array<bool, 32>, 64> g_Display{};




int main(int argc, char* args[])
{
	std::string ibm{ "ibm.ch8" };
	Interpreter interprt{ibm};
	if (!interprt.readFromFile())
	{
		return 0;
	}

	Display d{ 640,480 };
	Texture texture{};
	bool quit{ false };
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}
		}


		SDL_SetRenderDrawColor(g_Renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(g_Renderer);

		interprt.executeCycle();
		texture.updateTexture();
		texture.render(0, 0);

		SDL_RenderPresent(g_Renderer);

	}
	return 0;
}