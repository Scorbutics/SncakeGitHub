#include <stdio.h>
#include "defines.h"
#include "Texture.h"

Texture* TextureCreate(SDL_Renderer* renderer, String* spriteName, int r, int g, int b, int a)
{
	Texture* tex;
	SDL_Surface* surf;

	surf = IMG_Load(spriteName->data);
	if(surf == NULL)
	{
		printf( "Erreur (Fonction TextureCreate) : impossible de charger l'image \"%s\".\n", spriteName->data);
		surf = IMG_Load(NOSUCHFILE);
		if(surf == NULL)
		{
			printf("ATTENTION. Impossible de charger l'image \"%s\" : %s \n" , NOSUCHFILE, SDL_GetError());
			return NULL;
		}
	}
	else if(r >= 0 && g >= 0 && b >= 0)
	{
		SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, r, g, b));
		if(a < 255 && a >= 0)
			SDL_SetSurfaceAlphaMod(surf, a);
	}

	tex = (Texture*) malloc(sizeof(Texture));
	if(tex != NULL)
	{
		tex->handle = SDL_CreateTextureFromSurface(renderer, surf);
		if(tex->handle == NULL)
			printf( "Erreur (fonction TextureCreate): impossible de cr�er la texture � partir de la surface (%s)\n", SDL_GetError());
		tex->w = surf->w;
		tex->h = surf->h;
	}

	SDL_FreeSurface(surf);
	return tex;
}

void TextureFree(Texture* tex)
{
	SDL_DestroyTexture(tex->handle);
	free(tex);
}

Texture* TextureCopy(SDL_Renderer* renderer, Texture* tex)
{
	Texture* texDst;
	texDst = (Texture*) malloc(sizeof(Texture));
	texDst->w = tex->w;
	texDst->h = tex->h;

	texDst->handle = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, texDst->w, texDst->h);
	SDL_SetTextureBlendMode(texDst->handle, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, texDst->handle);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, tex->handle, NULL, NULL);
	SDL_SetRenderTarget(renderer, NULL);


	//�vite les clignotements d'�cran (on utilise le m�me renderer pour copier une texture et pour afficher l'�cran, or, on doit clear ce renderer quand on copie une texture,
	//on a donc un clignotement d'�cran durant 1 frame lorsqu'on copie une texture. Pour �viter cela, lors de la copie d'une texture on emp�che le SDL_RenderPresent de la
	//frame courante).
	//Pour l'instant, je n'ai pas r�ussi � trouver de mani�re plus propre.
	//wScreen->setNextFrameFlip(false);

	return texDst;
}

int TextureRender(SDL_Renderer* renderer, Texture* tex, int x, int y, SDL_Rect* clip)
{

	SDL_Rect destBuf = { x, y, tex->w, tex->h };

	if( clip != NULL )
	{
		destBuf.w = clip->w;
		destBuf.h = clip->h;
	}


	return SDL_RenderCopy( renderer, tex->handle, clip, &destBuf );
}