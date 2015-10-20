#ifndef BULLETS_INCLUDED
#define BULLETS_INCLUDED

#include "headers.h"
#include "Basics.h"

#define pi 3.1415

extern class BULLET{
private:
//Bullet Strict
struct Entity_bullet{
double x,y,velx,vely;
int w,h;
bool faction;
SDL_Texture *tex;
Entity_bullet *next;
}*FirstBullet,*LastBullet;

//Variables
SDL_Texture *texBullet[10];
Uint32 timer;

public:
void init(void);
void shoot_to   ( bool faction,int prefab,int from_x,int from_y,int to_x,int to_y );
void shoot_unghi( bool faction,int prefab,int from_x,int from_y,double unghi );
void handle(void);
void draw(void);
void cleanup(void);
}GAME_BULLETS;



#endif // BULLETS_INCLUDED
