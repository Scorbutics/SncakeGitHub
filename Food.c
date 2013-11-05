#include <stdlib.h>
#include "defines.h"
#include "Body.h"
#include "Body_prot.h"
#include "Food.h"
#include "Food_prot.h"
#include "World.h"
#include "World_prot.h"
#include "Screen.h"

Food* FoodCreate(Screen* screen, String* spriteName, unsigned int id, unsigned int effect)
{
	Food* f = (Food*) malloc(sizeof(Food));
	f->sprite = AnimatedSpriteCreate(screen->renderer, spriteName, FRAMES_X_BODY, FRAMES_Y_BODY, ANIM_HORIZONTAL, 200, 255);
	f->id = id;
	f->effect = effect;

	return f;
}

void FoodRender(SDL_Renderer* renderer, Food* f)
{
	AnimatedSpriteRender(renderer, f->sprite, f->position.x, f->position.y);
}

void FoodEat(Food* f, Body* b, World* w)
{
	switch(f->effect)
	{
		case FOOD_EFFECT_ADD:
			BodyAdd(b, w);
			break;

		default:
			break;
	}

	FoodPlace(f, b, w);

}

void FoodPlace(Food* f, Body* b, World* world)
{
	do 
	{
		f->position.x = (rand()%(world->w + 1))/BLOCK_SIZE * BLOCK_SIZE;
		f->position.y = (rand()%(world->h + 1))/BLOCK_SIZE * BLOCK_SIZE;
	} while (BodyCollision(b, &f->position, -1) || WorldCollision(world, f->position));
}

int FoodCollision(Food* f, Body* b, World* w)
{
	
	if(f->position.x == b->position[b->indexHeadPosition].x && f->position.y == b->position[b->indexHeadPosition].y)
	{
		FoodEat(f, b, w);
		return 1;
	}
	
	

	return 0;
}

void FoodFree(Food* b)
{
	AnimatedSpriteFree(b->sprite);
	free(b);
}

