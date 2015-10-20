#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "headers.h"
#include "Basics.h"
#include <cmath>

struct Enemy{
double x,y;
int w,h,health,prefab,phase;
SDL_Rect rCenter;
Uint32 timer,timer2,timer3,timedie;
bool dead,show,dying;
unsigned char behavior;
SDL_Texture *tex;
Enemy *next;
};

///Class
class Enemies{
private:
SDL_Texture *texEnemySkins[10];
//Enemy Type
Enemy *FirstEnemy,*LastEnemy;
//Variables
SDL_Texture *texEnemy1;
SDL_Rect rBody[10],rFlame_1[10],rFlame_2[10];
Uint32 timeAnimFlame,timePhaseDie;
bool bCFlame,bPhaseDie;

public:
void init(void);
void spawn( int x,int y,int prefab,int behavior );
void attack( Enemy *enemy,int damage );
void behave(void);
void reset_list(void);
void draw(void);
Enemy *getEnemyArray(void);
};
extern Enemies GAME_Enemies;

#endif // ENEMY_H_INCLUDED
