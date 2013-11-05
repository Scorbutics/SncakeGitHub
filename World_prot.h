#include "Body.h"
#include "Food.h"
#include "String.h"

World* WorldCreate(SDL_Renderer* renderer, String* blockSpriteName, unsigned int w, unsigned int h, unsigned int nbrBlocks);
int WorldCollision(World* world, SDL_Rect pos);
void WorldFree(World* world);
void WorldInitPoints(World* world, unsigned int nbrBlocks);
void WorldInitLines(World* world, unsigned int nbrBlocks);
void WorldRender(SDL_Renderer* renderer, World* world);
void WorldPrint(World* world);
int IsValidPosition(World* w, SDL_Rect r, Body* b);
void WorldClear(World* world);
int WorldBlockGetNeighboursNumber(World* world, SDL_Rect pos);
