

#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "Sprites.h"


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
void drawPlayer(struct Sprite *player);
void corregirPosicionLianaFinal(struct Sprite* player, struct Node *node);
bool corregirPosicionLiana(struct Sprite *player, struct Sprite *ladder);

void createFruit(struct Node **node, int spriteSize);
void updateLizard(struct Sprite *lizard);
bool inEnd(struct Sprite *lizard );
bool inTop(struct Sprite *lizard );
void drawFruits(struct Node* node);
void createLizard(struct Node** node, int liana, bool isRoja);
void updateAllLizards(struct Node* node);
void drawAllLizards(struct Node* node);
void drawLives(int points, int screenWidth, int screenHeight, ALLEGRO_BITMAP * spriteSheet);

