//
// Created by eduardo on 01/06/19.
//

#ifndef UNTITLED_SPRITE_H
#define UNTITLED_SPRITE_H

#include <allegro5/bitmap.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Sprites.c"
#include "Const.h"

const float VEL = 1;

//Sprite struct
struct Sprite{

    float x, y;

    float accX, accY;

    float velX, velY;

    int dirX, dirY;

    int bx, by;

    int w, h;

    bool movingR;
    bool movingL;
    bool lastR;
    bool jumping;
    bool climbing;
    bool hammer;

    int imageInd, hammerInd;

    ALLEGRO_BITMAP *image[3];
    ALLEGRO_BITMAP *spriteSheet;

};
//Barrel struct
struct Barrel{
    float x, y;
    float velX, velY;
    int type, w, h, dir, ind, land;
    ALLEGRO_BITMAP *spriteSheet;

};

//--------------------------------Done------------------------------------------
/*
 * Description:  Creates a platform using its coordinates
 * Input: X, Y
 * Output: Sprite struct
 *
 * */
struct Sprite createPlatform(float x1, float y1, float x2, float y2){

    struct Sprite plat;
    plat.x = x1;
    plat.y = y1;

    plat.h = y2-y1;
    plat.w = x2-x1;

    return plat;
}


/*
 *  Sirve para las plataformas
 */
void genAllPlats(struct Node** node, unsigned spriteSize){


    for (int i = 0; i < 10; ++i) {

        struct Sprite plat = createPlatform(platX1[i]*multSize, platY1[i]*multSize,
         platX2[i]*multSize+2, platY2[i]*multSize+2);

        push(node,&plat,spriteSize);
    }


}

void drawPlatRects(struct Node *node){

    struct Sprite * target;

    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        al_draw_rectangle(target->x, target->y, target->x + target->w, target->y+target->h,
        al_map_rgb_f(0,255,0), 2.0);

        node = node->next;
    }

}

//-------------------------------------------------------------------------------

/*

void createBarrel(float x, float y,int type, struct Node **node, int spriteSize){

    struct Barrel barrel;

    barrel.x = x;
    barrel.y = y;
    barrel.ind = 0;
    barrel.type = type;
    barrel.spriteSheet = al_load_bitmap("Sprites/misc-2.png");
    assert(barrel.spriteSheet != NULL);



    if(type == 1){
        barrel.w = 77-66;
        barrel.h = 267-258;

        barrel.velX = 2;
        barrel.velY = barrel.velX;
        barrel.dir = 1;

    }
    else if(type == 2){

        barrel.w = 110-96;
        barrel.h = 268-259;
        barrel.velX = 0;
        barrel.velY = 3.5;

    }
    else if(type == 3){
        barrel.w = 110-96;
        barrel.h = 268-259;


        barrel.velX = 2;
        barrel.velY = barrel.velX;

        srand(time(NULL));   // Initialization, should only be called once.
        int ind = rand()%4;

        barrel.land = barrelLanding[ind];

        switch (ind){

            case 0:
                barrel.dir = 1;
                break;
            case 1:
                barrel.dir = -1;
                break;
            case 2:
                barrel.dir = 1;
                break;
            case 3:
                barrel.dir = -1;
                break;

        }
    }

    push(node,&barrel,spriteSize);
}




bool isBarrelColliding(struct Barrel *sprite, struct Sprite target){

    if(sprite->y + sprite->h*SCALE < target.y + target.h -2 &&
       sprite->x < target.x  + target.w &&
       sprite->x + sprite->w*SCALE > target.x&&
       sprite->y + sprite->h*SCALE > target.y +2){

        sprite->y = target.y + 5 - sprite->h*SCALE;
        sprite->velY = 0;
        return true;

    }
    else{

        return false;

    }


}


void updateBarrelInds(struct Node *node){

    struct Barrel * target;

    while (node != NULL)
    {
        target = (struct Barrel *)node->data;

        target->ind+=1;
        target->ind = target->ind%4;

        node = node->next;
    }

}
// Posiblemente borrable
bool isBarrelCollidingAll(struct Barrel *barrel, struct Node *node){
    struct Sprite * target;

    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        if(isBarrelColliding(barrel,*target)){
            return true;
        }
        node = node->next;
    }

    return false;

}


Modificar para lagartos
 

void updateAllBarrels(struct Node *node, struct Node *platList, int level){
    struct Barrel * target;

    while (node != NULL)
    {
        target = (struct Barrel *)node->data;

        updateBarrel(target, platList, level);

        node = node->next;
    }

}



 Modificar para lagartos
 

void updateBarrel(struct Barrel *barrel, struct Node *node, int level){

    if(barrel->type == 1){

        al_draw_scaled_bitmap(barrel->spriteSheet,
                              barrelImageX[barrel->ind], barrelImageY[barrel->ind], barrel->w+1, barrel->h+1,
                              barrel->x, barrel->y, (barrel->w)*SCALE, barrel->h*SCALE, 0);


        if(isBarrelCollidingAll(barrel,node)){
            if(barrel->y > 536*1.15){
                barrel->dir = -1;
            }
            else if(barrel->x > 530*1.15) {
                barrel->dir = -1;
            }
            else if(barrel->x < 54*1.15){
                barrel->dir = 1;
            }

            barrel->x += (barrel->velX+(barrel->velX*level)/5)*barrel->dir;

        }
        else{

            barrel->y += barrel->type + (barrel->type*level)/5;
        }
    }
    else if(barrel->type == 2){

        al_draw_scaled_bitmap(barrel->spriteSheet,
                              barrelImageX2[barrel->ind%2], barrelImageY2[barrel->ind%2], barrel->w+1, barrel->h+1,
                              barrel->x, barrel->y, (barrel->w)*SCALE, barrel->h*SCALE, 0);
        barrel->y += barrel->velY;

    }
    else if(barrel->type == 3){

        if(barrel->y < barrel->land){

            al_draw_scaled_bitmap(barrel->spriteSheet,
                                  barrelImageX2[barrel->ind%2], barrelImageY2[barrel->ind%2], barrel->w+1, barrel->h+1,
                                  barrel->x, barrel->y, (barrel->w)*SCALE, barrel->h*SCALE, 0);
            barrel->y += barrel->velY;


        }
        else{
            barrel->w = 77-66;
            barrel->h = 267-258;

            al_draw_scaled_bitmap(barrel->spriteSheet,
                                  barrelImageX[barrel->ind], barrelImageY[barrel->ind], barrel->w+1, barrel->h+1,
                                  barrel->x, barrel->y, (barrel->w)*SCALE, barrel->h*SCALE, 0);


            if(isBarrelCollidingAll(barrel,node)) {
                if (barrel->y > 536 * 1.15) {
                    barrel->dir = -1;
                } else if (barrel->x > 530 * 1.15) {
                    barrel->dir = -1;
                } else if (barrel->x < 54 * 1.15) {
                    barrel->dir = 1;
                }

                barrel->x += (barrel->velX + (barrel->velX * level) / 5) * barrel->dir;


            }
            else{

                barrel->y += barrel->type + (barrel->type*level)/5;
            }
        }

    }

}




void drawSprite(struct Sprite *sprite){

    al_draw_bitmap(sprite->image[sprite->imageInd], sprite->x, sprite->y, 0);

}




struct Sprite allocateSprite(){

    return *((struct Sprite*) malloc(sizeof(struct Sprite)));

}



void drawPlayer(struct Sprite *player){

    if(player->jumping){

        if(player->lastR) {


            al_draw_scaled_bitmap(player->spriteSheet,
                                  239, 0, 13+5, 24,
                                  player->x, player->y, (13+5)*SCALE, 24*SCALE, 0);
        }
        else{


            al_draw_scaled_bitmap(player->spriteSheet,
                                  39, 0, 13, 24,
                                  player->x, player->y, 13*SCALE, 24*SCALE, 0);

        }

    }

    else if(player->movingR){

    al_draw_scaled_bitmap(player->spriteSheet,
        playerImageX1[player->imageInd], 0, 13, 24,
        player->x, player->y, (13 + 3) * SCALE, 24 * SCALE, 0);
    }
    else if(player->movingL){

        al_draw_scaled_bitmap(player->spriteSheet,
                              playerImageX2[player->imageInd], 0, 13, 24,
                              player->x, player->y, 13*SCALE, 24*SCALE, 0);

    }
    else if(player->lastR){

        al_draw_scaled_bitmap(player->spriteSheet,
                              playerImageX1[0], 0, 13, 24,
                              player->x, player->y, 13*SCALE, 24*SCALE, 0);

    }
    else{

        al_draw_scaled_bitmap(player->spriteSheet,
                              playerImageX2[0], 0, 13, 24,
                              player->x, player->y, 13*SCALE, 24*SCALE, 0);


    }

}


void updatePlayer(struct Sprite *player){

    if(!player->climbing) {
        player->accY += player->velY * -.25;
        player->velY += player->accY;
        player->y += player->velY + player->accY;
    }

    player->accX += player->velX * FRICC;
    player->velX += player->accX;
    player->x += player->velX + player->accX * ACC;

    if(abs(round(player->velX)) < 0.01){

        player->accX = 0;
        player->movingR = false;
        player->movingL = false;

    }
}



//Creacion de lianas
struct Sprite createLadder(float x1, float y1, float x2, float y2){

    struct Sprite ladder;
    ladder.x = x1;
    ladder.y = y1;

    ladder.h = y2 - y1;
    ladder.w = x2 - x1;

    return ladder;

}

//Colliding functions
bool isTopColliding(struct Sprite * sprite, struct Sprite target){


    if(sprite->y < target.y + target.h &&
       sprite->x < target.x  + target.w &&
       sprite->x + sprite->w > target.x&&
       sprite->y > target.y){


        if(!sprite->climbing) {
            sprite->y = target.y + target.h + 1;
        }
        return true;

    }
    else {return false;}

}

// ??????????????????????????????????
bool isColliding(struct Sprite *sprite, struct Sprite target){
    if(sprite->y + sprite->h < target.y + target.h -2 &&
            sprite->x < target.x  + target.w &&
       sprite->x + sprite->w > target.x&&
       sprite->y + sprite->h > target.y +2){

        if(!sprite->climbing) {
            sprite->y = target.y + 2 - sprite->h;
        }
        sprite->jumping = false;
        return true;

    }
    else{

        return false;

    }

}

//???????????????
bool isCollidingWithAny(struct Sprite *player, struct Node *node){
    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        if(isColliding(player,*target)){

            return true;

        }

        node = node->next;
    }


    return false;

}

//Colision lagartos
bool isCollidingWithBarrel(struct Sprite * sprite, struct Barrel *target){
    if(sprite->y < target->y + target->h -2 &&
       sprite->x < target->x  + target->w &&
       sprite->x + sprite->w > target->x&&
       sprite->y + sprite->h > target->y +2){

        if(sprite->hammer){

            target->x = -500;
            target->y = -500;
            return false;

        }

        return true;

    }
    else{

        return false;

    }
}
//Colisiones con lagartos
bool isCollidingWithBarrels(struct Sprite *player, struct Node *node){
    struct Barrel * target;


    while (node != NULL)
    {
        target = (struct Barrel *)node->data;

        if(isCollidingWithBarrel(player,target)){

            return true;

        }

        node = node->next;
    }


    return false;

}

bool isTopCollidingWithAny(struct Sprite *player, struct Node *node){
    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        if(isTopColliding(player,*target)){

            return true;

        }

        node = node->next;
    }


    return false;

}

//Colision de lianas
bool ladderCollide(struct Sprite *player, struct Sprite *ladder){

    float playerBottom = player->y + player->h;

    if(playerBottom > ladder->y &&
       player->x > ladder->x-player->w &&
       player->x < ladder->x+5 + ladder->w &&
       playerBottom < ladder->y + ladder->h){


        return true;

    }
    else{

        return false;

    }


}

bool allLadderCollide(struct Sprite* player, struct Node *node){
    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        if(ladderCollide(player,target)){

            return true;

        }

        node = node->next;
    }


    return false;

}
//Colisiones para frutas
bool hammerCollide(struct Sprite *sprite, struct Sprite * target){

    if(sprite->y < target->y + target->h -2 &&
       sprite->x < target->x  + target->w &&
       sprite->x + sprite->w > target->x&&
       sprite->y + sprite->h > target->y +2){


        target->x = -500;
        target->y = -500;

        return true;

    }
    else{
        return false;

    }


}
//Colisiones para frutas
bool allHammerCollide(struct Sprite* player, struct Node *node){
    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        if(hammerCollide(player,target)){

            return true;

        }

        node = node->next;
    }


    return false;

}

//------------------------------------------------



//Sirve para las lianas

void genLadders(struct Node** node, unsigned spriteSize){

    for (int i = 0; i < ladderNum; ++i) {

        struct Sprite ladder = createLadder(ladderX1[i]*1.15, ladderY1[i]*1.15, ladderX2[i]*1.15, ladderY2[i]*1.15);
        ladder.h *= 1.15;
        ladder.w *= 1.15;

        push(node,&ladder,spriteSize);


    }

}






struct Sprite createHammer(int ind){

    struct Sprite hammer;
    hammer.x = hammerXCoords[ind]*1.15;
    hammer.y = hammerYCoords[ind]*1.15;

    hammer.h = hammerH;
    hammer.w = hammerW;

    return hammer;

}
*/

#endif //UNTITLED_SPRITE_H
