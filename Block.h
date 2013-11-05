#ifndef DEF_BLOCK
#define DEF_BLOCK

struct Block
{
	unsigned int collision;
};
typedef struct Block Block;

Block* BlockCreate(unsigned int collision);
int BlockCollision(Block* b);
void BlockFree(Block* b);

#endif