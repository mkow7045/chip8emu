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
	std::string ibm{ "space_invaders.ch8" };
	Interpreter interpreter{ibm};
	if (!interpreter.readFromFile())
	{
		return 0;
	}

	Display d{ 640,480 };
	Texture texture{};
	bool quit{ false };
	SDL_Event e;

	LTim

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}

			else if (e.type == SDL_EVENT_KEY_DOWN)
			{
				switch (e.key.key)
				{
				case SDLK_1:
					interpreter.setKey(0x0);
					break;
				case SDLK_2:
					interpreter.setKey(0x1);
					break;
				case SDLK_3:
					interpreter.setKey(0x2);
					break;
				case SDLK_4:
					interpreter.setKey(0x3);
					break;
				case SDLK_Q:
					interpreter.setKey(0x4);
					break;
				case SDLK_W:
					interpreter.setKey(0x5);
					break;
				case SDLK_E:
					interpreter.setKey(0x6);
					break;
				case SDLK_R:
					interpreter.setKey(0x7);
					break;
				case SDLK_A:
					interpreter.setKey(0x8);
					break;
				case SDLK_S:
					interpreter.setKey(0x9);
					break;
				case SDLK_D:
					interpreter.setKey(0xA);
					break;
				case SDLK_F:
					interpreter.setKey(0xB);
					break;
				case SDLK_Z:
					interpreter.setKey(0xC);
					break;
				case SDLK_X:
					interpreter.setKey(0xD);
					break;
				case SDLK_C:
					interpreter.setKey(0xE);
					break;
				case SDLK_V:
					interpreter.setKey(0xF);
					break;
				}
			}

			else if (e.type == SDL_EVENT_KEY_UP)
			{
				switch (e.key.key)
				{
				case SDLK_1:
					interpreter.setKey(0x0);
					break;
				case SDLK_2:
					interpreter.setKey(0x1);
					break;
				case SDLK_3:
					interpreter.setKey(0x2);
					break;
				case SDLK_4:
					interpreter.setKey(0x3);
					break;
				case SDLK_Q:
					interpreter.setKey(0x4);
					break;
				case SDLK_W:
					interpreter.setKey(0x5);
					break;
				case SDLK_E:
					interpreter.setKey(0x6);
					break;
				case SDLK_R:
					interpreter.setKey(0x7);
					break;
				case SDLK_A:
					interpreter.setKey(0x8);
					break;
				case SDLK_S:
					interpreter.setKey(0x9);
					break;
				case SDLK_D:
					interpreter.setKey(0xA);
					break;
				case SDLK_F:
					interpreter.setKey(0xB);
					break;
				case SDLK_Z:
					interpreter.setKey(0xC);
					break;
				case SDLK_X:
					interpreter.setKey(0xD);
					break;
				case SDLK_C:
					interpreter.setKey(0xE);
					break;
				case SDLK_V:
					interpreter.setKey(0xF);
					break;
				}
			}
		}


		SDL_SetRenderDrawColor(g_Renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(g_Renderer);

		interpreter.executeCycles(500);
		interpreter.decreaseDT();
		interpreter.decreaseST();
		texture.updateTexture();
		texture.render(0, 0);

		SDL_RenderPresent(g_Renderer);

	}
	return 0;
}