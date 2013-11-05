#include <stdio.h>
#include <time.h>

#include "Settings.h"
#include "defines.h"
#include "String.h"
#include "Body.h"
#include "Body_prot.h"
#include "Food.h"
#include "Food_prot.h"
#include "Screen.h"
#include "World.h"
#include "World_prot.h"
#include "PortableThread.h"
#include "Log.h"



void InputWaitKey();
void* graphicUpdate(void* data);
void* eventUpdate(void* data);
typedef struct
{
	Screen* screen;
	Food* food;
	World* world;
	Body* snake;
	Settings* settings;
	int game;

} AlphaSignal;



int main(void)
{
	SDL_Event event;
	int quit;
	unsigned int t0, t;
	String* blockSpriteName;
	String* snakeSpriteName;
	String* foodSpriteName;
	AlphaSignal sigAlpha;
	//PortableThread *graphicThread, *eventThread;

	if(!LOG_MODE_DEBUG)
		freopen("."FILE_SEPARATOR"err.txt", "w", stdout);
	
	srand((unsigned int)time(NULL));

	sigAlpha.settings = SettingsCreate();
	SettingsLoad(sigAlpha.settings, "settings.cfg");

	
	
	blockSpriteName = StringCreate("."FILE_SEPARATOR"Data"FILE_SEPARATOR"Sprites"FILE_SEPARATOR"block.png");
	snakeSpriteName = StringCreate("."FILE_SEPARATOR"Data"FILE_SEPARATOR"Sprites"FILE_SEPARATOR"bodypart.png");
	foodSpriteName = StringCreate("."FILE_SEPARATOR"Data"FILE_SEPARATOR"Sprites"FILE_SEPARATOR"food.png");
	sigAlpha.screen = ScreenCreate(sigAlpha.settings->screenW, sigAlpha.settings->screenH);
	sigAlpha.world = WorldCreate(sigAlpha.screen->renderer, blockSpriteName, sigAlpha.settings->screenW, sigAlpha.settings->screenH, sigAlpha.settings->nbrBlocks);
	sigAlpha.food = FoodCreate(sigAlpha.screen, foodSpriteName, 0, FOOD_EFFECT_ADD);
	sigAlpha.snake = BodyCreate(sigAlpha.screen->renderer, snakeSpriteName, sigAlpha.settings->speed, 3);
	
	
	quit = 0;
	while(!quit)
	{
		WorldClear(sigAlpha.world);
		WorldInitLines(sigAlpha.world, sigAlpha.settings->nbrBlocks);
		BodyFree(sigAlpha.snake);
		sigAlpha.snake = BodyCreate(sigAlpha.screen->renderer, snakeSpriteName, sigAlpha.settings->speed, 3);
		BodyPlace(sigAlpha.snake, sigAlpha.world);
		FoodPlace(sigAlpha.food, sigAlpha.snake, sigAlpha.world);
		SDL_RenderClear(sigAlpha.screen->renderer);
		WorldRender(sigAlpha.screen->renderer, sigAlpha.world);
		FoodRender(sigAlpha.screen->renderer, sigAlpha.food);
		BodyRender(sigAlpha.screen->renderer, sigAlpha.snake);
		ScreenFlip(sigAlpha.screen);
		InputWaitKey();

		t = t0 = SDL_GetTicks();
		sigAlpha.snake->t0 = t0;
		sigAlpha.game = 0;
		//graphicThread = PortableThreadCreate(graphicUpdate, &sigAlpha);
		//eventThread = PortableThreadCreate(eventUpdate, &sigAlpha);

		while(!sigAlpha.game)
		{
			t = SDL_GetTicks();

			while(SDL_PollEvent(&event))
			{
				switch (event.key.keysym.scancode)
				{
					case SDL_SCANCODE_UP:
						if(sigAlpha.snake->direction != DIRECTION_DOWN)
							sigAlpha.snake->nextDirection = DIRECTION_UP;
						break;

					case SDL_SCANCODE_RIGHT:
						if(sigAlpha.snake->direction != DIRECTION_LEFT)
							sigAlpha.snake->nextDirection = DIRECTION_RIGHT;
						break;

					case SDL_SCANCODE_DOWN:
						if(sigAlpha.snake->direction != DIRECTION_UP)
							sigAlpha.snake->nextDirection = DIRECTION_DOWN;
						break;

					case SDL_SCANCODE_LEFT:
						if(sigAlpha.snake->direction != DIRECTION_RIGHT)
							sigAlpha.snake->nextDirection = DIRECTION_LEFT;
						break;

					case SDL_SCANCODE_ESCAPE:
						quit = 1;
						sigAlpha.game = 1;
						break;

					default:
						break;
				}

			}

			if(t - t0 > sigAlpha.settings->frameSpeed)
			{
				
				//PortableThreadWait(eventThread);
				//PortableThreadWait(graphicThread);
				eventUpdate(&sigAlpha);
				graphicUpdate(&sigAlpha);

				t0 = t;

				if(sigAlpha.game)
					LogPrint("Quit !\n");
				

			}
			else
				SDL_Delay(sigAlpha.settings->frameSpeed - (t - t0));
		}
		//PortableThreadFree(eventThread);
		//PortableThreadFree(graphicThread);
		
	}

	
	//Libération mémoire avant de quitter
	SettingsFree(sigAlpha.settings);
	WorldFree(sigAlpha.world);
	BodyFree(sigAlpha.snake);
	FoodFree(sigAlpha.food);
	StringFree(snakeSpriteName);
	StringFree(blockSpriteName);
	StringFree(foodSpriteName);
	ScreenFree(sigAlpha.screen);
	
	return 0;
}


void InputWaitKey()
{
	SDL_Event event;
	int quit = 0;
	while(SDL_WaitEvent(&event) && !quit)
	{
		switch (event.key.type)
		{
			case SDL_KEYDOWN:
				quit = 1;
				break;
		}
	}
}

void* graphicUpdate(void* data)
{
	AlphaSignal* sigAlpha = (AlphaSignal*) data;

	SDL_RenderClear(sigAlpha->screen->renderer);
	WorldRender(sigAlpha->screen->renderer, sigAlpha->world);
	FoodRender(sigAlpha->screen->renderer, sigAlpha->food);
	BodyRender(sigAlpha->screen->renderer, sigAlpha->snake);
	ScreenFlip(sigAlpha->screen);

	return NULL;
}

void* eventUpdate(void* data)
{
	AlphaSignal* sigAlpha = (AlphaSignal*) data;

	FoodCollision(sigAlpha->food, sigAlpha->snake, sigAlpha->world);

	if(!BodyMove(sigAlpha->snake, sigAlpha->world))
		sigAlpha->game = 1;

	return NULL;
}
