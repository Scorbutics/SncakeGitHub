#ifndef DEF_SCREEN
#define DEF_SCREEN

#include <SDL2/SDL.h>

struct Screen
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	unsigned int w, h;
};
typedef struct Screen Screen;

Screen* ScreenCreate(unsigned int w, unsigned int h);
void ScreenFlip(Screen* screen);
void ScreenFree(Screen* screen);

#endif
