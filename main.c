#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_primitives.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "Sprites.c"
#include "Const.h"
#define MAX 80



//Main game function
void newGame();



int main(){

    newGame();

}

//Game over display
void newGame(){

    al_init();
    al_init_image_addon();
    al_init_primitives_addon();


    ALLEGRO_BITMAP *background;
    background = al_load_bitmap("Sprites/map.png");

    assert(background != NULL);
   


    unsigned width = 255;
    unsigned height = 239;

    ALLEGRO_DISPLAY *display = al_create_display(width*multSize,height*multSize);


    ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_TIMER * timer;

    struct Node *platList = NULL;
    struct Node *fruitList = NULL;
    struct Node *lianasList = NULL;
    unsigned spriteSize = sizeof(struct Sprite);

    //Creacion de plataformas

    genAllPlats(&platList, spriteSize);
    genAllLianas(&lianasList, spriteSize);


    queue = al_create_event_queue();
    timer = al_create_timer(FPS);


    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));



    al_set_window_title(display, "DonCEy-Kong Jr.!");

    //Game mechanics variables
    bool key[5] = {false, false, false, false, false};

    bool showingHitboxes = false;
    bool colliding = false;
    bool falling = true;


    struct Sprite player = allocateSprite();

    player.spriteSheet = al_load_bitmap("Sprites/NES - Donkey Kong Jr - General Sprites.png");

    assert(player.spriteSheet != NULL);

    player.x= width*multSize/2;
    player.y = height*multSize/2;
    player.w = (playerImageX2[player.imageInd] - playerImageX1[player.imageInd])*multSize;
    player.h = (playerImageY2[player.imageInd] - playerImageY1[player.imageInd])*multSize;
    player.velX = 0;
    player.velY = GRAV;
    player.accX = 0;
    
    player.bx = player.w/2;
    player.by = player.h/2;

    player.movingR = false;
    player.movingL = false;
    player.lastR = true;
    player.climbingUp = false;
    player.climbing = false;

    bool topColliding = false;

    bool running = true;
    al_start_timer(timer);

    int count = 0;
    int fruitCounter = 0;
    int points = 0;

    while(running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

//----------------------- Event Detection ---------------------------------------------------------------------------------
        

       //Platform collition
        if(isCollidingWithAny(&player,platList)){

            colliding = true;
            falling = false;

        } 
        else {
            colliding = false; falling = true;
        };

        if(allLadderCollide(&player,lianasList)){

            player.climbing = true;
            falling = true;

        }
        else player.climbing = false;
        
        if(isTopCollidingWithAny(&player, platList)){

            topColliding = true;

        }
        else topColliding = false;

        if(allFruitCollide(&player, fruitList)){

            points += 500;

        }

        //Keyboard detection
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {

            switch(event.keyboard.keycode) {

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE] = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    running = false;
                    break;
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP) {

            switch(event.keyboard.keycode) {

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    running = false;

                    break;
                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE] = false;
                    break;
                //P,K and L are used for debugging
                case ALLEGRO_KEY_P:
                    break;
                case ALLEGRO_KEY_K:
                    break;
                case ALLEGRO_KEY_L:
                    break;
            }
        }

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
        }
        
//----------------------- Updates ------------------------------------------------------------------------------
        if(key[KEY_SPACE]){
            if(player.climbing){
                player.w = (playerImageX2[player.imageInd] - playerImageX1[player.imageInd])*multSize;
                corregirPosicionLianaFinal(&player, lianasList);
            }
            if(!falling){
                player.y -= JUMP;
            }


        }
        if(key[KEY_UP] && player.climbing && !topColliding){
            player.climbingUp = true;
            player.y -= 1;
        }
        else player.climbingUp = false;

        if(key[KEY_DOWN] && player.climbing){
            player.climbingUp = true;
            player.y +=1;

        }
        else player.climbingUp = false;

        if(key[KEY_RIGHT] ){

            if(player.climbing){
                player.lastR = true;            

                corregirPosicionLianaFinal(&player, lianasList);

                player.x-=29;
            }
            else{
                player.movingR = true;
                player.accX = ACC;
                player.movingL = false;
                player.lastR = true;            
            }
        }
        if(key[KEY_LEFT]){
            if(player.climbing){
                player.lastR = false;            
                corregirPosicionLianaFinal(&player, lianasList);

                player.x+=6;
            }
            else{
            player.accX = -ACC;
            player.movingL = true;
            player.movingR = false;
            player.lastR = false;
            }
        }


        if(colliding){

            player.velY = 0;

        }
        else player.velY = GRAV;

        if(topColliding && !player.climbing){

            player.velY = 0;
            player.jumping = false;

        }

        //Actualizar jugador antesde dibujarlo en pantalla
        updatePlayer(&player);

        if (event.type == ALLEGRO_EVENT_TIMER) {

            count++;
            fruitCounter++; 

            //Drawing sprites, background and enemies
            al_clear_to_color(al_map_rgb_f(255,0,0));
            al_draw_scaled_bitmap(background,0,0,width,height,0,0,width*multSize,height*multSize,0);
            drawPlatRects(platList);
            drawPlatRects(lianasList);
            drawPlatRects(fruitList);

            al_draw_rectangle(player.x, player.y, player.x + player.w, player.y + player.h,
                al_map_rgb_f(255,0,0), 2.0);

            drawPlayer(&player);
            drawFruits(fruitList);
            if(count > 15){
                if(player.velX != 0 && (player.movingR || player.movingL)) {
                    (&player)->imageInd += 1;
                    (&player)->imageInd = (&player)->imageInd % 3;
                }
                //If the player isnt moving
                if(!(player.movingR || player.movingL)){

                    player.imageInd = 0;

                }

                count = 0;
            }
            if(fruitCounter > 300){

                createFruit(&fruitList, spriteSize);
                printf("Fruta\n");
                fruitCounter = 10;
            }
            char text = points;
            drawPoints(points, width, height);
            al_flip_display();
        }
    }
    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);

}

/*
int start(int level){
    printf("Initializing!\n");



//----------------------- Declarations ---------------------------------------------------------------------------------

    al_init();
    al_init_image_addon();
    al_init_primitives_addon();

    unsigned width = WIDTH;
    unsigned height = HEIGHT;


    ALLEGRO_DISPLAY *display = al_create_display(WIDTH,HEIGHT);

    al_set_window_title(display, "DonCE-Kong!");

    ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_TIMER * timer;

    bool key[5] = {false, false, false, false, false};


    queue = al_create_event_queue();
    timer = al_create_timer(1.0/FPS);




    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    //Timer and game states
    al_start_timer(timer);

    bool showingHitboxes = false;
    bool colliding = false;
    bool falling = true;

//----------------------- Game Loop ---------------------------------------------------------------------------------

    while(running){

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);


        //----------------------- Event Detection ---------------------------------------------------------------------------------
        
        //Keyboard detection
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {

            switch(event.keyboard.keycode) {

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE] = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    running = false;
                    break;
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP) {

            switch(event.keyboard.keycode) {

                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    running = false;

                    break;
                case ALLEGRO_KEY_SPACE:
                    key[KEY_SPACE] = false;
                    break;
                //P,K and L are used for debugging
                case ALLEGRO_KEY_P:
                    break;
                case ALLEGRO_KEY_K:
                    break;
                case ALLEGRO_KEY_L:
                    break;
            }
        }*/
        //Enemy creation from server-----------------------------------------------------------------------------------
        //Example
        /*
        if(barrelCode == 1){

            createBarrel(173,173,1,&barrelList,barrelSize);
            barrelCode = 0;

        }
        */
    //------------------------------------------------------------------------------------------------------------------
/*
        //If the window is closed
        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
        }

        //----------------------- Updates ------------------------------------------------------------------------------
        if(key[KEY_SPACE]){
            
        }

        //If the player falls off the map
        /*
        if(player.y > height*1.15){
            al_destroy_display(display);
            al_uninstall_keyboard();
            al_destroy_timer(timer);

            return -1;

        }
        */

        //Level win condition (reaching the princess)
        //PENDING
        
        //Stop the player if colliding with a platform
        /*
        if(colliding){

            player.accY = 0;

        }
        else player.accY = GRAV;
        */
 /*       
        //-------------------------------------------Movement-----------------------------------------------------------
        if (key[KEY_RIGHT]) {
            //Agregar estado si se esta escalando o si esta en la plataforma
        }
        /*
        if(key[KEY_UP] && player.climbing){

            player.y -= 1;
        }
        */
        /*
        if(key[KEY_DOWN] && player.climbing){

            player.y +=1;

        }
        */
/*
        if (key[KEY_LEFT]) {
        }
/*      
        //Adecuar la colision de arriba para el juego
        if(isTopCollidingWithAny(&player, spriteList) && !player.climbing){

            player.velY = 0;
            player.jumping = false;

        }
*/
        //--------------------------------------------------------------------------------------------------------------


        //updatePlayer(&player); what is this, dude


/*
   //----------------------- Rendering ----------------------------------------------------------------------------
        //lo que toque
        if(event.type == ALLEGRO_EVENT_TIMER){

            //Drawing sprites, background and enemies
            al_clear_to_color(al_map_rgb_f(255,0,0));

            //FUNCION IMPORTANTE
            //al_draw_scaled_bitmap(background,0,0,width,height,0,0,width*1.15,height*1.15,0);

/*              IMPORTANTE PARA LAS ANIMACIONES

                //imageInd is used in the animation of the player and other sprites
                if(player.velX != 0 && (player.movingR || player.movingL)) {
                    (&player)->imageInd += 1;
                    (&player)->imageInd = (&player)->imageInd % 2;
                    (&player)->hammerInd += 1;
                    (&player)->hammerInd = (&player)->hammerInd%3;
                }
                //If the player isnt moving
                if(!(player.movingR || player.movingL)){

                    player.imageInd = 0;

                }
*/

            

            //updates and draws
            /*
            updateAllBarrels(barrelList,spriteList,level);
            drawHammers(hammerList);

            drawPlayer(&player);
            drawFireBalls(fireList);
            
            al_flip_display();
        }

    }
//------------Finalization----------------------------------------------------------------------------------------------
/*
    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);

    return 0;
}
*/

