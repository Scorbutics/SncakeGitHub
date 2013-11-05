#include "String.h"
#include "World.h"

Body* BodyCreate(SDL_Renderer* renderer, String* spriteName, float speed, unsigned int size);
void BodyFree(Body* body);
void BodyPlace(Body* b, World* world);
void BodyRender(SDL_Renderer* renderer, Body* b);
void BodyPlacePart(Body* b, World* w, SDL_Rect pos, unsigned int indexBody, unsigned int direction);
int BodyMove(Body* b, World* w);
int BodyCollision(Body* b, SDL_Rect* pos, int body);
void BodyAdd(Body* b, World* w);