#ifndef DEF_FOOD
#define DEF_FOOD

#include <SDL2/SDL.h>

#include "String.h"
#include "AnimatedSprite.h"
//#include "World.h"
//#include "Body.h"
struct Screen;
struct Body;
struct World;

struct Food
{
	unsigned int id, effect;
	AnimatedSprite* sprite;
	SDL_Rect position;
};
typedef struct Food Food;


#endif