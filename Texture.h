#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "String.h"

struct Texture
{
	SDL_Texture* handle;
	unsigned int w;
	unsigned int h;
};
typedef struct Texture Texture;

Texture* TextureCreate(SDL_Renderer* renderer, String* spriteName, int r, int g, int b, int a);
int TextureRender(SDL_Renderer* renderer, Texture* tex, int x, int y, SDL_Rect* clip);
Texture* TextureCopy(SDL_Renderer* renderer, Texture* tex);
void TextureFree(Texture* tex);

#endif