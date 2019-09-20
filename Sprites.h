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
#include <math.h>
#include "LinkedList.h"
#include "Sprites.c"
#include "Const.h"
#include <time.h>

const float VEL = 1;

//Sprite struct
struct Sprite{

    float x, y;

    float accX, accY;

    float velX, velY;

    int dirX, dirY;

    int w, h;

    int bx, by;

    bool movingR;
    bool movingL;
    bool lastR;
    bool jumping;
    bool climbing;
    bool climbingUp;
    bool isRoja;


    int imageInd, hammerInd;

    ALLEGRO_BITMAP *spriteSheet;

};

//--------------------------------Terminado------------------------------------------

void drawPoints(int points, int screenWidth, int screenHeight, ALLEGRO_BITMAP * spriteSheet){

    int ind1, ind2, refPoints;

    refPoints = points;

    if(refPoints > 0){
    ind1 = refPoints%10;
    ind2 = ((int)floor(refPoints/10))%10;
}   
    else ind1 = 0 , ind2 = 0;

    al_draw_scaled_bitmap(spriteSheet,
                              numImageX[ind1],numImageY[ind1], 7, 7,
                              screenWidth*multSize - 20, 40,14, 14, 0);

    al_draw_scaled_bitmap(spriteSheet,
                              numImageX[ind2],numImageY[ind2], 7, 7,
                              screenWidth*multSize - 34, 40,14, 14, 0);

}

void drawLives(int points, int screenWidth, int screenHeight, ALLEGRO_BITMAP * spriteSheet){

    int ind1, ind2, refPoints;

    refPoints = points;

    if(refPoints > 0){
    ind1 = refPoints%10;
    ind2 = ((int)floor(refPoints/10))%10;
}   
    else ind1 = 0 , ind2 = 0;

    al_draw_scaled_bitmap(spriteSheet,
                              numImageX[ind1],numImageY[ind1], 7, 7,
                              screenWidth*multSize - 100, 40,14, 14, 0);

    al_draw_scaled_bitmap(spriteSheet,
                              numImageX[ind2],numImageY[ind2], 7, 7,
                              screenWidth*multSize - 114, 40,14, 14, 0);

}

struct Sprite createPlatform(float x1, float y1, float x2, float y2){

    struct Sprite plat;
    plat.x = x1;
    plat.y = y1;

    plat.h = y2-y1;
    plat.w = x2-x1;

    return plat;
}

void genAllPlats(struct Node** node, unsigned spriteSize){


    for (int i = 0; i < 10; ++i) {

        struct Sprite plat = createPlatform(platX1[i]*multSize, platY1[i]*multSize,
         platX2[i]*multSize+2, platY2[i]*multSize+2);

        push(node,&plat,spriteSize);
    }


}

void genAllLianas(struct Node** node, unsigned spriteSize){


    for (int i = 0; i < 12; ++i) {

        struct Sprite plat = createPlatform(1+lianaX1[i]*multSize, lianaY1[i]*multSize,
         lianaX2[i]*multSize+2, lianaY2[i]*multSize+2);

        push(node,&plat,spriteSize);
    }


}

void drawPlatRects(struct Node *node){

    struct Sprite * target;

    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        al_draw_rectangle(target->x, target->y, target->x + target->w, target->y+target->h,
        al_map_rgb_f(255,0,0), 2.0);

        node = node->next;
    }

}

struct Sprite allocateSprite(){

    return *((struct Sprite*) malloc(sizeof(struct Sprite)));

}


void updatePlayer(struct Sprite *player){

    if(!player->climbing) {  
        player->y += player->velY;
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

void createFruit(struct Node **node, int spriteSize){
    struct Sprite Fruit;
    srand(time(NULL));
    int newx = rand() % 12;
    int newy = (rand() % (175-72+1))+72;
    Fruit.x= lianaX1[newx]*multSize;
    Fruit.y= newy*multSize;

    Fruit.w = 14;
    Fruit.h = 10;

    Fruit.spriteSheet = al_load_bitmap("Sprites/NES - Donkey Kong Jr - General Sprites.png");

    push(node,&Fruit,spriteSize);
        
}

void drawFruits(struct Node* node){


    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        al_draw_scaled_bitmap(target->spriteSheet,
                              16,99, target->w, target->h,
                              target->x,target->y,target->w*2, target->h*2, 0);



        node = node->next;
    }


}

void createLizard(struct Node** node, int liana, bool isRoja){
    struct Sprite lizard;
    srand(time(NULL));
    int xInd = liana;
    lizard.x = lianaX1[xInd]*multSize;

    lizard.y = lianaY1[xInd]*multSize;

    lizard.w = 7;

    lizard.h = 14;
    lizard.climbing = false;

    lizard.bx = lizard.y;
    lizard.by = lianaY2[xInd]*multSize;

    lizard.isRoja = isRoja;

    lizard.spriteSheet = al_load_bitmap("Sprites/NES - Donkey Kong Jr - General Sprites.png");

    push(node,&lizard,sizeof(struct Sprite));




}

void updateLizard(struct Sprite *lizard){
   if (lizard->isRoja){

	if (lizard->climbing) lizard->y--;
	else lizard->y++;

	if (lizard->y >= lizard->by) lizard->climbing = true;
	if (lizard->y <= lizard->bx) lizard->climbing =false;
   }
   else{
        lizard->y++;
   }
}

void updateAllLizards(struct Node* node){


    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;
        
        updateLizard(target);

        node = node->next;
    }


}

void drawAllLizards(struct Node* node){

    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        if(!target->isRoja){

            if(target->climbing){
                al_draw_scaled_bitmap(target->spriteSheet,
                                    96,136, target->w, target->h,
                                    target->x,target->y,target->w*2, target->h*2, ALLEGRO_FLIP_VERTICAL);
            }
            else{
                al_draw_scaled_bitmap(target->spriteSheet,
                                    96,136, target->w, target->h,
                                    target->x,target->y,target->w*2, target->h*2, 0);
            
            }
        }
        else{
            if(target->climbing){

            al_draw_scaled_bitmap(target->spriteSheet,
                                    32,136, target->w, target->h,
                                    target->x,target->y,target->w*2, target->h*2, ALLEGRO_FLIP_VERTICAL);
            }
            else{
                al_draw_scaled_bitmap(target->spriteSheet,
                                    32,136, target->w, target->h,
                                    target->x,target->y,target->w*2, target->h*2, 0);
            }

        
        }

        node = node->next;
    }


}


bool inEnd(struct Sprite *lizard ){
   const int lianaY2[12] = {199,191,151,199,175,143,175,159,135,135,175,175};
   for(int i=0; i<12; ++i)
     {
        if(lizard->y == lianaY2[i]) return true;
     }
    return false;
}

bool inTop(struct Sprite *lizard ){
   const int lianaY1[12] = {72,72,120,160,72,72,80,80,0,0,144,144};
   for(int i=0; i<12; ++i)
     {
        if(lizard->y == lianaY1[i]) return true;
     }
    return false;
}

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

    float playerBottom = player->y ;

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

bool corregirPosicionLiana(struct Sprite *player, struct Sprite *ladder){

    float playerBottom = player->y ;

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

void corregirPosicionLianaFinal(struct Sprite* player, struct Node *node){


    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        if(corregirPosicionLiana(player,target)){
            
            if(player->lastR) player->x = target->x + target->w + 6;
            else player->x = target->x - player->w - 5;
            return;
        }

        node = node->next;
    }


    return;


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


void drawPlayer(struct Sprite *player){

    if(player->climbing){
        if (player->climbingUp){
            al_draw_scaled_bitmap(player->spriteSheet,
                34, 16, 52-34, 31-16,
                player->x, player->y, (52-34)*multSize, (31-16)*multSize, ALLEGRO_FLIP_HORIZONTAL);

            player->w = (52-34)*multSize;
        }

        else if(player->lastR) {
            al_draw_scaled_bitmap(player->spriteSheet,
                                  96, 16, 126-96, 31-16,
                                  player->x, player->y, (126-96)*multSize, (31-16)*multSize, ALLEGRO_FLIP_HORIZONTAL);
            player->w = (126-96)*multSize;
        }

        else{
            al_draw_scaled_bitmap(player->spriteSheet,
                                  96, 16, 126-96, 31-16,
                                  player->x, player->y, (126-96)*multSize, (31-16)*multSize, 0);
            player->w =(126-96)*multSize;
        }

    }

    else if(player->movingR){

        al_draw_scaled_bitmap(player->spriteSheet,
            playerImageX1[player->imageInd], 0,
            (playerImageX2[player->imageInd] - playerImageX1[player->imageInd]), 
                (playerImageY2[player->imageInd] - playerImageY1[player->imageInd]),
            player->x, player->y, 
            (playerImageX2[player->imageInd] - playerImageX1[player->imageInd]) * multSize,
                (playerImageY2[player->imageInd] - playerImageY1[player->imageInd]) * multSize,
            0);

        player->w = (playerImageX2[player->imageInd] - playerImageX1[player->imageInd]) * multSize;
        player->h = (playerImageY2[player->imageInd] - playerImageY1[player->imageInd]) * multSize;

    }
    else if(player->movingL){

        al_draw_scaled_bitmap(player->spriteSheet,
            playerImageX1[player->imageInd], 0,
            (playerImageX2[player->imageInd] - playerImageX1[player->imageInd]), 
                (playerImageY2[player->imageInd] - playerImageY1[player->imageInd]),
            player->x, player->y, 
            (playerImageX2[player->imageInd] - playerImageX1[player->imageInd]) * multSize,
                (playerImageY2[player->imageInd] - playerImageY1[player->imageInd]) * multSize,
            ALLEGRO_FLIP_HORIZONTAL);
    }
    else if(player->lastR){

        al_draw_scaled_bitmap(player->spriteSheet,
        playerImageX1[0], 0,
        (playerImageX2[0] - playerImageX1[0]), 
            (playerImageY2[0] - playerImageY1[0]),
        player->x, player->y, 
        (playerImageX2[0] - playerImageX1[0]) * multSize,
             (playerImageY2[0] - playerImageY1[0]) * multSize,
         0);

    }
    else{

       
        al_draw_scaled_bitmap(player->spriteSheet,
        playerImageX1[0], 0,
        (playerImageX2[0] - playerImageX1[0]), 
            (playerImageY2[0] - playerImageY1[0]),
        player->x, player->y, 
        (playerImageX2[0] - playerImageX1[0]) * multSize,
             (playerImageY2[0] - playerImageY1[0]) * multSize,
         ALLEGRO_FLIP_HORIZONTAL);

    }


}


bool fruitCollide(struct Sprite *sprite, struct Sprite * target){

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

bool allFruitCollide(struct Sprite* player, struct Node *node){
    struct Sprite * target;


    while (node != NULL)
    {
        target = (struct Sprite *)node->data;

        if(fruitCollide(player,target)){

            return true;

        }

        node = node->next;
    }


    return false;

}


#endif //UNTITLED_SPRITE_H
