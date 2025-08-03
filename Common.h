#ifndef COMMON_H
#define COMMON_H
#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL_mixer.h>

extern SDL_Window* g_Window;
extern SDL_Renderer* g_Renderer;
extern bool g_Display[64][32];

#endif