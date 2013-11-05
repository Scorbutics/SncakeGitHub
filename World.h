#ifndef DEF_WORLD
#define DEF_WORLD

#include <SDL2/SDL.h>
#include "Block.h"
#include "AnimatedSprite.h"

struct World
{
	Block*** map;
	unsigned int w, h;
	AnimatedSprite* blockSprite;
};
typedef struct World World;



#endif