#include <stdio.h>
#include "defines.h"
#include "Screen.h"


Screen* ScreenCreate(unsigned int w, unsigned int h)
{
	Screen* screen;
	screen = (Screen*) malloc(sizeof(Screen));

	if(screen != NULL)
	{
		screen->w = w/BLOCK_SIZE * BLOCK_SIZE;
		screen->h = h/BLOCK_SIZE * BLOCK_SIZE;
		screen->window = SDL_CreateWindow("Sncake",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			screen->w , screen->h,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

		if(screen->window == NULL)
			printf( "Erreur lors de la création de la fenêtre SDL : %s\n", SDL_GetError());

		screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);

		if(screen->renderer == NULL)
			printf( "Erreur lors de la création du renderer de la fenêtre SDL : %s\n", SDL_GetError());

		SDL_SetRenderDrawColor(screen->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
			printf( "Attention : Linear texture filtering non activé !");
		
		SDL_RenderSetLogicalSize(screen->renderer, screen->w, screen->h);

	}

	return screen;
}

void ScreenFlip(Screen* screen)
{
	SDL_RenderPresent(screen->renderer);
}

void ScreenFree(Screen* screen)
{
	SDL_DestroyRenderer(screen->renderer);
	SDL_DestroyWindow(screen->window);
	free(screen);
}
