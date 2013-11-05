#ifndef DEF_SDLTOOLSLIB
#define DEF_SDLTOOLSLIB

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "String.h"

//RECT
unsigned int DistanceSquared(const SDL_Rect* pos1, const SDL_Rect* pos2);
int IsPositionInBox(const SDL_Rect *pos, const SDL_Rect *box);
int CollisionBoxABoxB(SDL_Rect rectA, SDL_Rect rectB);
int GetDirectionFromPos(SDL_Rect *posSrc, SDL_Rect *posDst);
int CollisionBoxABoxB(SDL_Rect rectA, SDL_Rect rectB);

//IMAGES
SDL_Color translate_color(Uint32 int_color);
Uint32 GetPixel32(SDL_Surface* image, int x, int y);
SDL_Surface* LoadImage32(const char *fichier_image, int vram);
SDL_Rect LocateColorInCorr(SDL_Surface* corr, SDL_Color c);
SDL_Rect PosToCenterPicture(const SDL_Rect *imageToCenter, const SDL_Rect *imageBackground);

#endif