#include "Common.h"
#include "Display.h"
#include "Texture.h"
#include "Timer.h"
#include "Interpreter.h"
#include <array>
#include <iostream>


SDL_Window* g_Window = nullptr;
SDL_Renderer* g_Renderer = nullptr;
std::array<std::array<bool, 32>, 64> g_Display{};




int main(int argc, char* argv[])
{
	std::string programPath{ argv[1] };
	Interpreter interpreter{ programPath };
	if (!interpreter.readFromFile())
	{
		return 0;
	}

	Display d{ 640,480 };
	Texture texture{};
	bool quit{ false };
	SDL_Event e;

	Timer fpsTimer{};

	Timer capTimer{};

	constexpr int framerate = 60;
	constexpr int ticksPerFrame = 1000 / framerate;
	Uint64 lastTimerUpdate{ 0 };

	Mix_Music* music{ nullptr };
	music = Mix_LoadMUS("beep.wav");
	if (music == NULL)
	{
		SDL_Log("Failed to load beat music! SDL_mixer Error: %s\n", SDL_GetError());
	}

	bool pause{ false };
	int countedFrames{ 0 };
	double cpuTimeAccumulated{};
	double cpuHz{ 500 };
	if (argc > 2)
	{
		Uint32 cpuHz = static_cast<double>(std::stoi(argv[2]));
	}
	else
	{
		cpuHz = 500;
	}

	double cpuDelta{ 1000 / cpuHz };
	fpsTimer.start();
	
	while (!quit)
	{
		capTimer.start();
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
					interpreter.setKey(0x0,true);
					break;
				case SDLK_2:
					interpreter.setKey(0x1,true);
					break;
				case SDLK_3:
					interpreter.setKey(0x2,true);
					break;
				case SDLK_4:
					interpreter.setKey(0x3,true);
					break;
				case SDLK_Q:
					interpreter.setKey(0x4,true);
					break;
				case SDLK_W:
					interpreter.setKey(0x5,true);
					break;
				case SDLK_E:
					interpreter.setKey(0x6,true);
					break;
				case SDLK_R:
					interpreter.setKey(0x7,true);
					break;
				case SDLK_A:
					interpreter.setKey(0x8,true);
					break;
				case SDLK_S:
					interpreter.setKey(0x9,true);
					break;
				case SDLK_D:
					interpreter.setKey(0xA,true);
					break;
				case SDLK_F:
					interpreter.setKey(0xB,true);
					break;
				case SDLK_Z:
					interpreter.setKey(0xC,true);
					break;
				case SDLK_X:
					interpreter.setKey(0xD,true);
					break;
				case SDLK_C:
					interpreter.setKey(0xE,true);
					break;
				case SDLK_V:
					interpreter.setKey(0xF,true);
					break;
				case SDLK_P:
					pause = !pause;
					break;
				}
			}

			else if (e.type == SDL_EVENT_KEY_UP)
			{
				switch (e.key.key)
				{
				case SDLK_1:
					interpreter.setKey(0x0,false);
					break;
				case SDLK_2:
					interpreter.setKey(0x1,false);
					break;
				case SDLK_3:
					interpreter.setKey(0x2,false);
					break;
				case SDLK_4:
					interpreter.setKey(0x3,false);
					break;
				case SDLK_Q:
					interpreter.setKey(0x4,false);
					break;
				case SDLK_W:
					interpreter.setKey(0x5,false);
					break;
				case SDLK_E:
					interpreter.setKey(0x6,false);
					break;
				case SDLK_R:
					interpreter.setKey(0x7,false);
					break;
				case SDLK_A:
					interpreter.setKey(0x8,false);
					break;
				case SDLK_S:
					interpreter.setKey(0x9,false);
					break;
				case SDLK_D:
					interpreter.setKey(0xA,false);
					break;
				case SDLK_F:
					interpreter.setKey(0xB,false);
					break;
				case SDLK_Z:
					interpreter.setKey(0xC,false);
					break;
				case SDLK_X:
					interpreter.setKey(0xD,false);
					break;
				case SDLK_C:
					interpreter.setKey(0xE,false);
					break;
				case SDLK_V:
					interpreter.setKey(0xF,false);
					break;
				}
			}
		}
		if (!pause)
		{
			
			Uint32 now = fpsTimer.getTicks();
			static Uint32 prevTime = now;
			Uint32 frameTime = now - prevTime;
			prevTime = now;
			
			
			while (now - lastTimerUpdate >= 1000 / 60)
			{
				interpreter.decreaseDT();
				interpreter.decreaseST();
				if (interpreter.getST() > 0)
				{
					Mix_PlayMusic(music, -1);
				}
				else
				{
					Mix_HaltMusic();
				}
				lastTimerUpdate += 1000 / 60;
			}

			SDL_SetRenderDrawColor(g_Renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(g_Renderer);

			cpuTimeAccumulated += frameTime;
			Uint32 cyclesToExecute{};
			while (cpuTimeAccumulated >= cpuDelta)
			{
				++cyclesToExecute;
				cpuTimeAccumulated -= cpuDelta;
			}

			interpreter.executeCycles(cyclesToExecute);

			texture.updateTexture();
			texture.render(0, 0);

			SDL_RenderPresent(g_Renderer);
			++countedFrames;

			int frameTicks = capTimer.getTicks();
			if (frameTicks < ticksPerFrame)
			{
				SDL_Delay(ticksPerFrame - frameTicks);
			}
		}
	}
	return 0;
}