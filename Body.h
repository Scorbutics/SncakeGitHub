#ifndef DEF_BODY
#define DEF_BODY

#include "AnimatedSprite.h"

struct Body
{
	AnimatedSprite* sprite;
	unsigned int indexHeadPosition, indexQueuePosition;
	SDL_Rect* position;
	unsigned int size;
	unsigned int direction, nextDirection, pixelMovement, t0;
	float speed;
};
typedef struct Body Body;


#endif