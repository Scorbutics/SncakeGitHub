#include <stdlib.h>
#include <stdio.h>

#include "Log.h"
#include "SDLTools.h"
#include "defines.h"
#include "String.h"
#include "AnimatedSprite.h"
#include "Body.h"
#include "Body_prot.h"
#include "World.h"
#include "World_prot.h"

Body* BodyCreate(SDL_Renderer* renderer, String* spriteName, float speed, unsigned int size)
{
	Body* bp;
	unsigned int i;

	//Sécurité
	if(size == 0)
		return NULL;

	bp = (Body*) malloc(sizeof(Body));

	//Création d'un corps uniforme (tous les blocs seront identiques)
	if(bp != NULL)
		bp->sprite = AnimatedSpriteCreate(renderer, spriteName, FRAMES_X_BODY, FRAMES_Y_BODY, ANIM_HORIZONTAL, 150, 255);
	else
		return NULL;

	bp->size = size;
	bp->direction = DIRECTION_UP;
	bp->nextDirection = DIRECTION_UP;

	//Création de la position des différentes parties du corps
	bp->position = (SDL_Rect*) malloc(size * sizeof(SDL_Rect));
	if(bp->position != NULL)
	{
		for(i = 0; i < bp->size; i++)
		{
			bp->position[i].x = 0;
			bp->position[i].y = 0;

			if(bp->sprite != NULL)
			{
				bp->position[i].w = bp->sprite->texture->w;
				bp->position[i].h = bp->sprite->texture->h;
			}
		}
	}

	bp->indexHeadPosition = 0;
	bp->indexQueuePosition = bp->size-1;
	bp->speed = speed;
	bp->pixelMovement = 0;

	return bp;
}

void BodyPlace(Body* b, World* world)
{
	unsigned int i;
	
	do 
	{
		b->position[0].x = (rand()%(world->w/BLOCK_SIZE - 2 + 1) + 1) * BLOCK_SIZE;
		b->position[0].y = (rand()%(world->h/BLOCK_SIZE - 5 + 1) + 3) * BLOCK_SIZE;
	} while (!IsValidPosition(world, b->position[0], b));
	

	for(i = 1; i < b->size; i++)
		BodyPlacePart(b, world, b->position[i-1], i, DIRECTION_DOWN);
	
	b->t0 = SDL_GetTicks();
	
}

void BodyRender(SDL_Renderer* renderer, Body* b)
{
	unsigned int i;
	for(i = 0; i < b->size; i++)
		AnimatedSpriteRender(renderer, b->sprite, b->position[i].x, b->position[i].y);
}

void BodyPlacePart(Body* b, World* w, SDL_Rect pos, unsigned int indexBody, unsigned int direction)
{
	SDL_Rect lastPos = pos;

	switch(direction)
	{
		case DIRECTION_UP:
			pos.y -= BLOCK_SIZE;
			break;

		case DIRECTION_DOWN:
			pos.y += BLOCK_SIZE;
			break;

		case DIRECTION_RIGHT:
			pos.x += BLOCK_SIZE;
			break;

		case DIRECTION_LEFT:
			pos.x -= BLOCK_SIZE;
			break;

		default:
			break;
	}

	if(WorldCollision(w, pos) || BodyCollision(b, &pos, b->indexHeadPosition))
	{
		if(direction >= 0 && direction <= 3)
			BodyPlacePart(b, w, lastPos, indexBody, ++direction);
	}
	else
		b->position[indexBody] = pos;
	
}

int BodyMove(Body* b, World* w)
{
	b->pixelMovement = b->speed*BLOCK_SIZE*(SDL_GetTicks() - b->t0)/1000;
	if(b->pixelMovement >= BLOCK_SIZE)
	{
		b->pixelMovement -= b->pixelMovement%BLOCK_SIZE;
		b->t0 = SDL_GetTicks();
		b->direction = b->nextDirection;
		switch(b->nextDirection)
		{
			case DIRECTION_UP:
				b->position[b->indexQueuePosition].y = b->position[b->indexHeadPosition].y - b->pixelMovement;
				b->position[b->indexQueuePosition].x = b->position[b->indexHeadPosition].x;
				break;

			case DIRECTION_DOWN:
				b->position[b->indexQueuePosition].y = b->position[b->indexHeadPosition].y + b->pixelMovement;
				b->position[b->indexQueuePosition].x = b->position[b->indexHeadPosition].x;
				break;

			case DIRECTION_RIGHT:
				b->position[b->indexQueuePosition].x = b->position[b->indexHeadPosition].x + b->pixelMovement;
				b->position[b->indexQueuePosition].y = b->position[b->indexHeadPosition].y;
				break;

			case DIRECTION_LEFT:
				b->position[b->indexQueuePosition].x = b->position[b->indexHeadPosition].x - b->pixelMovement;
				b->position[b->indexQueuePosition].y = b->position[b->indexHeadPosition].y;
				break;

			default:
				break;
		}
		b->pixelMovement = 0;

		b->indexHeadPosition = b->indexQueuePosition;
	
		if((int)(b->indexQueuePosition - 1) == -1)
			b->indexQueuePosition = b->size - 1;
		else
			b->indexQueuePosition--;
	
	

		if(WorldCollision(w, b->position[b->indexHeadPosition]) || BodyCollision(b, &b->position[b->indexHeadPosition], b->indexHeadPosition))
			return 0;
		
	}

	return 1;
}

int BodyCollision(Body* b, SDL_Rect* rect, int indexBody)
{
	unsigned int i;
	int collision = 0;
	char buffer[256];

	for(i = 0; i < b->size; i++)
		if(indexBody != i && b->position[i].x == rect->x && b->position[i].y == rect->y)
			collision = 1;
	
	if(collision)
	{
		sprintf(buffer, "Collision avec le corps, position de la tete :%i", b->indexHeadPosition);
		LogPrint(buffer);
	}

	return collision;
}

void BodyAdd(Body* b, World* w)
{
	b->size++;
	realloc_s(&b->position, b->size*sizeof(SDL_Rect));
	b->position[b->size - 1].x = b->position[b->indexHeadPosition].x;
	b->position[b->size - 1].y = b->position[b->indexHeadPosition].y;
}

void BodyFree(Body* bp)
{
	free(bp->position);
	AnimatedSpriteFree(bp->sprite);
	free(bp);
}
