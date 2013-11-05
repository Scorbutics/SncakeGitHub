#include "Food.h"
#include "Screen.h"
#include "Body.h"
#include "World.h"

Food* FoodCreate(Screen* s, String* spriteName, unsigned int id, unsigned int effect);
void FoodFree(Food* b);
int FoodCollision(Food* f, Body* b, World* world);
void FoodEat(Food* f, Body* b, World* world);
void FoodRender(SDL_Renderer* renderer, Food* f);
void FoodPlace(Food* f, Body* b, World* world);
