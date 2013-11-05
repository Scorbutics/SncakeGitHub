#include <stdlib.h>
#include <stdio.h>
#include "SDLTools.h"

unsigned int DistanceSquared(const SDL_Rect* pos1, const SDL_Rect* pos2)
{
	return (((pos1->x - pos2->x) * (pos1->x - pos2->x)) + ((pos1->y - pos2->y) * (pos1->y - pos2->y)));
}

int IsPositionInBox(const SDL_Rect *pos, const SDL_Rect *box)
{
	return((pos->x >= box->x) && (pos->x <= box->x + box->w) && (pos->y >= box->y) && (pos->y <= box->y + box->h));
}

int CollisionBoxABoxB(SDL_Rect rectA, SDL_Rect rectB)
{

	if(rectA.x > rectB.x + rectB.w || rectA.x + rectA.w < rectB.x)
		return 0;
	if(rectA.y > rectB.y + rectB.h || rectA.y + rectA.h < rectB.y)
		return 0;

	return 1;

}


int GetDirectionFromPos(SDL_Rect *posHero, SDL_Rect *mousePos) //divise l'écran en 8 directions possibles en fonction de la position de la souris
{
	double pente;
	int direction;
	double penteDiago1 = 1./3; //taux d'accroissement entre (TAILLEECRAN;TAILLEECRAN/3) et (0; TAILLEECRAN*2/3)
	double penteDiago2 = 3.; //taux d'accroissement entre (TAILLEECRAN*2/3; 0) et (TAILLEECRAN/3;TAILLEECRAN)
	//SDL_Rect posH = *posHero, posM = *mousePos;

	if(mousePos->x != posHero->x)
		pente = (double)abs((mousePos->y - posHero->y)/((double)mousePos->x - posHero->x));
	else
	{
		if(mousePos->y > posHero->y)
			return 0;
		else if(mousePos->y < posHero->y)
			return 2;
		else
			return -1;
	}

	if(pente < 0.0)
		pente *= -1;


	if(pente > penteDiago2)
	{
		if(mousePos->y > posHero->y)
			direction = 0;
		else
			direction = 2;
	}
	else if(pente > penteDiago1)
	{
		if(mousePos->x > posHero->x && mousePos->y > posHero->y)
			direction = 4;
		else if(mousePos->x > posHero->x && mousePos->y < posHero->y)
			direction = 5;
		else if(mousePos->x < posHero->x && mousePos->y < posHero->y)
			direction = 6;
		else
			direction = 7;

	}
	else
	{
		if(mousePos->x > posHero->x )
			direction = 1;
		else
			direction = 3;
	}

	return direction;
}

SDL_Rect PosToCenterPicture(const SDL_Rect *imageToCenter, const SDL_Rect *imageBackground)
{
	SDL_Rect posCenter;
	if(imageToCenter == NULL || imageBackground == NULL)
		printf( "Erreur (Fonction PosToCenterPicture) : une des deux dimension d'image est nulle.\n");
	else
	{
		posCenter.x = imageBackground->x + imageBackground->w/2 - imageToCenter->w/2;
		posCenter.y = imageBackground->y + imageBackground->h/2 - imageToCenter->h/2;
		posCenter.h = imageToCenter->h;
		posCenter.w = imageToCenter->w;
	}

	return posCenter;
}


SDL_Color translate_color(Uint32 int_color)     //Change from an "int color" to an SDL_Color
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	SDL_Color color;
	color.r = (int_color & 0x00ff0000)/0x10000;
	color.g = (int_color & 0x0000ff00)/0x100;
	color.b = (int_color & 0x000000ff);
	color.a = 255;
#else
	SDL_Color color;
	color.r = (int_color & 0x000000ff);
	color.g = (int_color & 0x0000ff00)/0x100;
	color.b = (int_color & 0x00ff0000)/0x10000;
	color.a = 255;
#endif
	return color;
}


SDL_Rect LocateColorInCorr(SDL_Surface* corr, SDL_Color c)
{
	SDL_Rect buf;
	SDL_Color cCmp;
	int x, y;

	for(x = 0; x < corr->w; x++)
		for(y = 0; y < corr->h; y++)
		{
			SDL_GetRGB(GetPixel32(corr, x, y), corr->format,&cCmp.r, &cCmp.g, &cCmp.b);
			if(c.r == cCmp.r && c.g == cCmp.g && c.b == cCmp.b)
			{

				buf.x = x;
				buf.y = y;
				return buf;
			}
		}

		buf.x = -1;
		buf.y = -1;
		return buf;
}


Uint32 GetPixel32(SDL_Surface* image, int x, int y)
{
	if (x<0 || x>image->w-1 || y<0 || y>image->h-1)
		return 0;
	return ((Uint32*)(image->pixels))[y*(image->pitch/4)+x];   // lecture directe des pixels
}


SDL_Surface* LoadImage32(const char *fichier_image, int vram)
{
	SDL_Surface *image_result, *image_ram;
	image_ram = IMG_Load(fichier_image);

	if (image_ram == NULL)
	{
		//cerr << "Erreur (fonction LoadImage32) : Impossible de charger le monde " << *fichier_image << endl;
		printf( "IMG_Load : %s\n", IMG_GetError());
		SDL_Quit();
		exit(-1);
	}

	image_result = NULL;
	if (vram)
		image_result=SDL_CreateRGBSurface(0, image_ram->w, image_ram->h, 32, 0, 0, 0, 0);  // cree une imageen VRAM
	if (image_result==NULL)
		vram = 0;
	if (!vram)
		image_result=SDL_CreateRGBSurface(0, image_ram->w, image_ram->h, 32, 0, 0, 0, 0);  // cree une image en RAM


	SDL_UpperBlit(image_ram,NULL,image_result,NULL);	// copie l'image image_ram de moins de 32 bits vers image_result qui fait 32 bits
	SDL_FreeSurface(image_ram);      // supprime la surface image_ram : inutile maintenant --> libere la mémoire
	return image_result;
}

