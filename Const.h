#ifndef UNTITLED_CONST_H
#define UNTITLED_CONST_H

const double FPS = 1.0/60;
const int multSize = 3.5;
float GRAV = 1.5;
const float ACC = 0.25;
float JUMP = 35;
const float FRICC = -0.2;
bool running = true;
enum KEYS {KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT,KEY_SPACE};


const int screenX[2] = {0,255};
const int screenY[2] = {0,239};

const int platX1[10] = {0,96,136,168,208,192,48,48,144,0};
const int platY1[10] = {216,200,208,200,192,136,112,152,72,64};
const int platX2[10] = {71,127,159,199,239,255,79,95,207,151};
const int platY2[10] = {223,207,215,207,199,143,119,159,79,71};

const int lianaX1[12] = {19,43,67,67,107,139,163,187,211,235,211,235};
const int lianaY1[12] = {72,72,120,160,72,72,80,80,0,0,144,144};
const int lianaX2[12] = {20,44,68,68,108,140,164,188,212,236,212,236};
const int lianaY2[12] = {199,191,151,199,175,143,175,159,135,135,175,175};

#endif //UNTITLED_CONST_H
