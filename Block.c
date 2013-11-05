#include <stdlib.h>
#include "Block.h"


Block* BlockCreate(unsigned int collision)
{
	Block *b = (Block*) malloc(sizeof(Block));
	if(b != NULL)
		b->collision = collision;

	return b;
}

int BlockCollision(Block* b)
{
	return b->collision;
}

void BlockFree(Block* b)
{
	free(b);
}
