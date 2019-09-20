//
// Created by Eduardo on 01/06/19.
//

#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "Sprites.h"

const float VEL;


struct Sprite;
struct Barrel;

void genAllPlats(struct Node** node, unsigned spriteSize);
void genAllLianas(struct Node** node, unsigned spriteSize);
struct Sprite createPlatform(float x1, float y1, float x2, float y2);
void drawPlatRects(struct Node *node);
struct Sprite allocateSprite();
void updatePlayer(struct Sprite *player);
bool isTopColliding(struct Sprite * player, struct Sprite target);
bool isColliding(struct Sprite *sprite, struct Sprite target);
bool isCollidingWithAny(struct Sprite* sprite, struct Node *node);
bool isTopCollidingWithAny(struct Sprite *player, struct Node *node);
bool ladderCollide(struct Sprite *player, struct Sprite *ladder);
bool allLadderCollide(struct Sprite* player, struct Node *node);




/*
void drawSprite(struct Sprite *sprite);

struct Sprite createPlayer(float x, float y);


void drawPlayer(struct Sprite * player);

void updatePlayer(struct Sprite *player);

void showHitbox(struct Sprite sprite);


bool isBottomColliding(struct Sprite * player, struct Sprite * target);

bool isTopColliding(struct Sprite * player, struct Sprite target);

bool isSideColliding(struct Sprite * player, struct Sprite target);

bool isColliding(struct Sprite *sprite, struct Sprite target);

bool isCollidingWithAny(struct Sprite* sprite, struct Node *node);

void drawAllSprites(struct Node *node);

void genPlats(struct Node** node,unsigned spriteSize, unsigned height, unsigned width);

void genFirstLine(struct Node** node, unsigned spriteSize);

void genSecondLine(struct Node** node, unsigned spriteSize);

void genThirdLine(struct Node** node, unsigned spriteSize);

void genFourthLine(struct Node** node, unsigned spriteSize);

void genFifthLine(struct Node** node, unsigned spriteSize);
    
bool isBarrelColliding(struct Barrel *sprite, struct Sprite target);

bool isBarrelCollidingAll(struct Barrel *barrel, struct Node *node);

void updateBarrel(struct Barrel *barrel, struct Node *node, int level);

void createBarrel(float x, float y, int type, struct Node **node, int spriteSize);

void genLadders(struct Node** node, unsigned spriteSize);

bool ladderCollide(struct Sprite *player, struct Sprite *ladder);

bool allLadderCollide(struct Sprite* player, struct Node *node);
*/


