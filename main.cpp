#include "Common.h"
#include "Display.h"
#include "Texture.h"
#include <array>


SDL_Window* g_Window = nullptr;
SDL_Renderer* g_Renderer = nullptr;
bool g_Display[64][32] {};




int main(int argc, char* args[])
{
	g_display[10][20] = true;
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

			SDL_SetRenderDrawColor(g_Renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(g_Renderer);

			texture.updateTexture();
			texture.render(0, 0);

			SDL_RenderPresent(g_Renderer);

		}
	}
	
	return 0;
}