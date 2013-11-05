#include <stdlib.h>
#include <stdio.h>

#include "Log.h"
#include "defines.h"
#include "World.h"
#include "World_prot.h"
#include "String.h"
#include "Body_prot.h"


World* WorldCreate(SDL_Renderer* renderer, String* blockSpriteName, unsigned int w, unsigned int h, unsigned int nbrBlocks)
{
	unsigned int i, j;
	World* world = (World*) malloc(sizeof(World));

	if(world != NULL)
	{
		world->w = w;
		world->h = h;
		world->map = (Block***) malloc((world->w/BLOCK_SIZE)*sizeof(Block**));

		for(i = 0; i < (world->w/BLOCK_SIZE); i++)
			world->map[i] = (Block**) malloc((world->h/BLOCK_SIZE)*sizeof(Block*));

		for(i = 0; i < (world->w/BLOCK_SIZE); i++)
			for(j = 0; j < (world->h/BLOCK_SIZE); j++)
				world->map[i][j] = BlockCreate(BLOCK_COL_NO);

		
		world->blockSprite = AnimatedSpriteCreate(renderer, blockSpriteName, 1, 1, 1, 500, 255);

		WorldInitLines(world, nbrBlocks);
	}

	return world;
}

void WorldInitPoints(World* world, unsigned int nbrBlocks)
{
	unsigned int i, j;
	SDL_Rect buf;

	//Crée un monde rectangulaire simple
	for(j = 0; j < (world->h/BLOCK_SIZE); j++)
	{
		world->map[0][j]->collision = BLOCK_COL_YES;
		world->map[(world->w/BLOCK_SIZE)-1][j]->collision = BLOCK_COL_YES;
	}

	for(i = 0; i < (world->w/BLOCK_SIZE); i++)
	{
		world->map[i][0]->collision = BLOCK_COL_YES;
		world->map[i][(world->h/BLOCK_SIZE)-1]->collision = BLOCK_COL_YES;
	}

	for(i = 0; i < nbrBlocks; i++)
	{
		do 
		{
			buf.x = (rand()%(world->w/BLOCK_SIZE - 2 + 1) + 1) * BLOCK_SIZE;
			buf.y = (rand()%(world->h/BLOCK_SIZE - 2 + 1) + 1) * BLOCK_SIZE;
		} while (WorldCollision(world, buf));

		world->map[buf.x/BLOCK_SIZE][buf.y/BLOCK_SIZE]->collision = BLOCK_COL_YES;
	}
		
}

void WorldInitLines(World* world, unsigned int nbrBlocks)
{
	unsigned int i, j, lineLenght, sens;
	SDL_Rect buf, bufLine;

	//Crée un monde rectangulaire simple
	for(j = 0; j < (world->h/BLOCK_SIZE); j++)
	{
		world->map[0][j]->collision = BLOCK_COL_YES;
		world->map[(world->w/BLOCK_SIZE)-1][j]->collision = BLOCK_COL_YES;
	}

	for(i = 0; i < (world->w/BLOCK_SIZE); i++)
	{
		world->map[i][0]->collision = BLOCK_COL_YES;
		world->map[i][(world->h/BLOCK_SIZE)-1]->collision = BLOCK_COL_YES;
	}



	for(i = 0; i < nbrBlocks/2; i++)
	{
		
		sens = rand()%2;
		lineLenght = rand()%((sens ? (world->w/BLOCK_SIZE)-4 : (world->h/BLOCK_SIZE)-4) + 1) + 3;
		buf.x = (rand()%(world->w/BLOCK_SIZE - 2 + 1) + 1) * BLOCK_SIZE;
		buf.y = (rand()%(world->h/BLOCK_SIZE - 2 + 1) + 1) * BLOCK_SIZE;
		bufLine = buf;
	
		if(sens)
		{
			for(j = 0; j < lineLenght && bufLine.x < world->w; j++)
			{
				bufLine.x += BLOCK_SIZE;
				if(IsValidPosition(world, bufLine, NULL))
					world->map[bufLine.x/BLOCK_SIZE][bufLine.y/BLOCK_SIZE]->collision = BLOCK_COL_YES;
			}
		}
		else
		{
			for(j = 0; j < lineLenght && bufLine.y < world->h; j++)
			{
				bufLine.y += BLOCK_SIZE;
				if(IsValidPosition(world, bufLine, NULL))
					world->map[bufLine.x/BLOCK_SIZE][bufLine.y/BLOCK_SIZE]->collision = BLOCK_COL_YES;
			}
		}
		
	}
}

void WorldClear(World* world)
{
	unsigned int i, j;

	for(i = 0; i < world->w/BLOCK_SIZE; i++)
		for(j = 0; j < world->h/BLOCK_SIZE; j++)
			world->map[i][j]->collision = BLOCK_COL_NO;
}

//Empêche la création d'"impasse" dans la configuration des blocs du monde
int IsValidPosition(World* w, SDL_Rect r, Body* b)
{
	SDL_Rect rLeft = r, rUp = r, rDown = r, rRight = r;
	rLeft.x -= BLOCK_SIZE;
	rRight.x += BLOCK_SIZE;
	rDown.y += BLOCK_SIZE;
	rUp.y -= BLOCK_SIZE;

	return (!WorldCollision(w, r) && WorldBlockGetNeighboursNumber(w, rLeft) < 2 && 
		WorldBlockGetNeighboursNumber(w, rUp) < 2 &&
		WorldBlockGetNeighboursNumber(w, rRight) < 2 &&
		WorldBlockGetNeighboursNumber(w, rDown) < 2 && 
		( b == NULL || !BodyCollision(b, &r, 0))
		);
}

int WorldBlockGetNeighboursNumber(World* world, SDL_Rect pos)
{
	int neighbours = 0;
	int i = pos.x/BLOCK_SIZE, j = pos.y/BLOCK_SIZE;
	
	if(i - 1 < 0 || BlockCollision(world->map[i-1][j]))
		neighbours++;
	
	if(i + 1 >= world->w/BLOCK_SIZE || BlockCollision(world->map[i+1][j]))
		neighbours++;

	if(j - 1 < 0 || BlockCollision(world->map[i][j-1]))
		neighbours++;

	if(j + 1 >= world->h/BLOCK_SIZE || BlockCollision(world->map[i][j+1]))
		neighbours++;

	return neighbours;
}

void WorldRender(SDL_Renderer* renderer, World* world)
{
	unsigned int i, j;
	
	for(i = 0; i < (world->w/BLOCK_SIZE); i++)
		for(j = 0; j < (world->h/BLOCK_SIZE); j++)
			if(world->map[i][j]->collision)
				AnimatedSpriteRender(renderer, world->blockSprite, i * BLOCK_SIZE, j * BLOCK_SIZE);
}

void WorldPrint(World* world)
{
	unsigned int i, j;

	for(i = 0; i < (world->w/BLOCK_SIZE); i++)
	{
		for(j = 0; j < (world->h/BLOCK_SIZE); j++)
			printf("%i", world->map[i][j]->collision);

		printf("\n");
	}
}

int WorldCollision(World* world, SDL_Rect pos)
{
	char buffer[256];
	if(pos.x/BLOCK_SIZE < (int)world->w/BLOCK_SIZE && pos.x >= 0 && pos.y/BLOCK_SIZE < (int)world->h/BLOCK_SIZE && pos.y >= 0)
	{
		sprintf(buffer, "Collision avec le monde : %p en (%i;%i)", world->map[pos.x/BLOCK_SIZE][pos.y/BLOCK_SIZE], pos.x/BLOCK_SIZE, pos.y/BLOCK_SIZE);
		if(BlockCollision(world->map[pos.x/BLOCK_SIZE][pos.y/BLOCK_SIZE]))
			LogPrint(buffer);

		return BlockCollision(world->map[pos.x/BLOCK_SIZE][pos.y/BLOCK_SIZE]);
	}
	else
		return 1;
}

void WorldFree(World* world)
{
	unsigned int i, j;
	for(i = 0; i < (world->w/BLOCK_SIZE); i++)
		for(j = 0; j < (world->h/BLOCK_SIZE); j++)
			BlockFree(world->map[i][j]);

	for(i = 0; i < (world->w/BLOCK_SIZE); i++)
		world->map[i];

	free(world->map);
	AnimatedSpriteFree(world->blockSprite);
	free(world);
}
