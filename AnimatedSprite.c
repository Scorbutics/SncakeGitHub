#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "SDLTools.h"
#include "AnimatedSprite.h"

AnimatedSprite* AnimatedSpriteCreate(SDL_Renderer* renderer, String* str, unsigned int numberx, unsigned int numbery, unsigned int animMode, unsigned int duration, int alpha)
{
	AnimatedSprite* spr;

	if(numberx == 0)
		numberx = 1;

	if(numbery == 0)
		numbery = 1;

	spr = (AnimatedSprite*) malloc(sizeof(AnimatedSprite));
	if(spr == NULL)
		printf( "Erreur (Fonction AnimatedSpriteCreate) : impossible d'allouer la memoire pour l'image animee \"%s\".\n", str->data);

	spr->texture = TextureCreate(renderer, str, T_RED, T_GREEN, T_BLUE, alpha);
	spr->currentPos = 0;
	spr->rectAnimation.x = 0;
	spr->rectAnimation.y = 0;
	spr->rectAnimation.w = spr->texture->w/numberx;
	spr->rectAnimation.h = spr->texture->h/numbery;
	spr->animMode = animMode;
	spr->autom = duration > 0 ? 1:0;
	spr->duration = duration;
	spr->direction = 1;

	if(numbery == 1 && numberx == 1)
		spr->autom = 0;
	spr->t0 = SDL_GetTicks();

	return spr;
}

void AnimatedSpriteRender(SDL_Renderer* renderer, AnimatedSprite* aSprite, int x, int y)
{
	int nextPos;

	if(aSprite->autom && SDL_GetTicks() - aSprite->t0 >= aSprite->duration)
	{
		switch(aSprite->animMode)
		{
			case ANIM_VERTICAL:
				nextPos = aSprite->currentPos + aSprite->rectAnimation.h*aSprite->direction;
				if(nextPos >= (int)aSprite->texture->h || nextPos < 0)
				{
					aSprite->direction *= -1;
					nextPos = aSprite->currentPos + aSprite->rectAnimation.h*aSprite->direction;
				}
				aSprite->currentPos = nextPos;
				aSprite->rectAnimation.y = aSprite->currentPos;
				break;
		
			case ANIM_HORIZONTAL:
				nextPos = aSprite->currentPos + aSprite->rectAnimation.w*aSprite->direction;
				if(nextPos >= (int)aSprite->texture->w || nextPos < 0)
				{
					aSprite->direction *= -1;
					nextPos = aSprite->currentPos + aSprite->rectAnimation.w*aSprite->direction;
				}
				aSprite->currentPos = nextPos;
				aSprite->rectAnimation.x = aSprite->currentPos;
				break;

			default:
				break;
		}

		aSprite->t0 = SDL_GetTicks();
	}

	TextureRender(renderer, aSprite->texture, x, y, &aSprite->rectAnimation);
}

void AnimatedSpriteFree(AnimatedSprite* aSprite)
{
	TextureFree(aSprite->texture);
	free(aSprite);
}

