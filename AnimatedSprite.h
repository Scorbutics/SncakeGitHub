#ifndef DEF_ANIMATEDSPRITE
#define DEF_ANIMATEDSPRITE

#include <SDL2/SDL.h>
#include "Texture.h"
#include "String.h"

struct AnimatedSprite
{
	Texture* texture;
	SDL_Rect rectAnimation;
	unsigned int currentPos, animMode, autom, duration, t0;
	int direction;
};
typedef struct AnimatedSprite AnimatedSprite;

AnimatedSprite* AnimatedSpriteCreate(SDL_Renderer* renderer, String* str, unsigned int numberx, unsigned int numbery, unsigned int animMode, unsigned int duration, int alpha);
void AnimatedSpriteFree(AnimatedSprite* aSprite);
void AnimatedSpriteRender(SDL_Renderer* renderer, AnimatedSprite* aSprite, int x, int y);
#endif