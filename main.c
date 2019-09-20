#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
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


int LIZARDCODE = -1;
bool LIZARDBOOL = false;

int clientSocket, ret;
struct sockaddr_in serverAddr;
char buffer[1024] = "Test";
char bufferR[1024];
int msg = 0;
int barrelCode = 0;
ALLEGRO_THREAD      *thread_1    = NULL;
ALLEGRO_THREAD      *thread_2    = NULL;


static void *Func_Thread1(ALLEGRO_THREAD *thr, void *arg);
static void *Func_Thread2(ALLEGRO_THREAD *thr, void *arg);
#define SA struct sockaddr
#define PORT 4444


int vidas = 3;
int points = 0;


//Main game function
void newGame();



void func(int sockfd) 
{ 
    char buff[MAX]; 
    int n; 
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        n = 0; 
        write(sockfd, buff, sizeof(buff)); 
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 

        char delim[] = "&";

        char *ptr1 = strtok(buff, delim);

        char *ptr2 = strtok(NULL,ptr1);


        if((strncmp(ptr1, "A", 1)) == 0){
            if(strncmp(ptr2, "01", 2) == 0){
                
                LIZARDCODE = 0;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "02", 2) == 0){
                
                LIZARDCODE = 1;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "03", 2) == 0){
                
                LIZARDCODE = 2;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "04", 2) == 0){
                
                LIZARDCODE = 3;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "05", 2) == 0){
                
                LIZARDCODE = 4;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "06", 2) == 0){
                
                LIZARDCODE = 5;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "07", 2) == 0){
                
                LIZARDCODE = 6;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "08", 2) == 0){
                
                LIZARDCODE = 7;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "09", 2) == 0){
                
                LIZARDCODE = 8;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "10", 2) == 0){
                
                LIZARDCODE = 9;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "11", 2) == 0){
                
                LIZARDCODE = 10;
                LIZARDBOOL = false;

            }
            else if(strncmp(ptr2, "12", 2) == 0){
                
                LIZARDCODE = 11;
                LIZARDBOOL = false;

            }
        }
         
        else if((strncmp(ptr1, "R", 1)) == 0){
            if(strncmp(ptr2, "01", 2) == 0){
                
                LIZARDCODE = 0;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "02", 2) == 0){
                
                LIZARDCODE = 1;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "03", 2) == 0){
                
                LIZARDCODE = 2;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "04", 2) == 0){
                
                LIZARDCODE = 3;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "05", 2) == 0){
                
                LIZARDCODE = 4;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "06", 2) == 0){
                
                LIZARDCODE = 5;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "07", 2) == 0){
                
                LIZARDCODE = 6;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "08", 2) == 0){
                
                LIZARDCODE = 7;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "09", 2) == 0){
                
                LIZARDCODE = 8;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "10", 2) == 0){
                
                LIZARDCODE = 9;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "11", 2) == 0){
                
                LIZARDCODE = 10;
                LIZARDBOOL = true;

            }
            else if(strncmp(ptr2, "12", 2) == 0){
                
                LIZARDCODE = 11;
                LIZARDBOOL = true;

            }
        }
    } 
}




int main() {

//-------------------------------------------------Threads--------------------------------------------------------------

    int data =0;

    thread_1 = al_create_thread(Func_Thread1, &data);
    al_start_thread(thread_1);
    thread_2 = al_create_thread(Func_Thread2, &data);
    al_start_thread(thread_2);
//----------------------------------------------------------------------------------------------------------------------
    printf("Done\n");

    //Loop to keep the program running
    while(vidas != 0){}

    return 0;
}


static void *Func_Thread1(ALLEGRO_THREAD *thr, void *arg) {

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    while (!al_get_thread_should_stop(thr)) {


        func(sockfd);

    }
        return NULL;

}

static void *Func_Thread2(ALLEGRO_THREAD *thr, void *arg) {

    while (!al_get_thread_should_stop(thr)) {

        newGame();
    }
    
    return NULL;

}

void newGame(){

    al_init();
    al_init_image_addon();
    al_init_primitives_addon();


    if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return;
   }
    if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return;
    }
	
    ALLEGRO_SAMPLE *sample=NULL;

    sample = al_load_sample( "Sprites/A Thousand Miles [8 Bit Tribute to Vanessa Carlton] - 8 Bit Universe.wav" );


    ALLEGRO_BITMAP *background;
    background = al_load_bitmap("Sprites/map.png");

    assert(background != NULL);
   


    unsigned width = 255;
    unsigned height = 239;

    ALLEGRO_DISPLAY *display = al_create_display(width*multSize,height*multSize);


    ALLEGRO_BITMAP * pointSheet = al_load_bitmap("Sprites/NES - Donkey Kong Jr - Fields.png");


    ALLEGRO_EVENT_QUEUE * queue;
    ALLEGRO_TIMER * timer;

    struct Node *platList = NULL;
    struct Node *fruitList = NULL;
    struct Node *lianasList = NULL;
    struct Node *lizardList = NULL;
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

    player.x= 1*multSize;
    player.y = 184*multSize;
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

    int lianaind = 0;

    al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
 

    while(running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

//----------------------- Event Detection ---------------------------------------------------------------------------------
        

        //Platform collition
        if(player.x < 96*multSize && player.y < 64*multSize){

            vidas++;
            running = false;

        }

        if(player.x < 0 - player.w || player.x > width*multSize){

            vidas--;
            running = false;
        }

        if(player.y > height*multSize){

            vidas--;
            running = false;

        }


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

            points += 1;

        }

        if(allFruitCollide(&player, lizardList)){

            vidas--;
            running = false;

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
                    createLizard(&lizardList, lianaind, true);
                    break;
                case ALLEGRO_KEY_K:
                    break;
                case ALLEGRO_KEY_L:
                    break;
            }
        }

        

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
            vidas = 0;
        }

        if(LIZARDCODE != -1){
            createLizard(&lizardList, LIZARDCODE, LIZARDBOOL);
            LIZARDCODE = -1;
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
        updateAllLizards(lizardList);

        if (event.type == ALLEGRO_EVENT_TIMER) {

            count++;
            fruitCounter++; 

            //Drawing sprites, background and enemies
            al_clear_to_color(al_map_rgb_f(255,0,0));
            al_draw_scaled_bitmap(background,0,0,width,height,0,0,width*multSize,height*multSize,0);
            

            drawPlayer(&player);
            drawAllLizards(lizardList);
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
                fruitCounter = 0;
            }
            drawPoints(points, width, height, pointSheet);
            drawLives(vidas, width, height, pointSheet);
            al_flip_display();
        }
    }
    al_destroy_display(display);
    al_uninstall_keyboard();
    al_destroy_timer(timer);

}
