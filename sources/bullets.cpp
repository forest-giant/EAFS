#include "headers.h"
#include "bullets.h"
#include "enemy.h"
#include "Player.h"
//#include "Console.h"
#include "effects.h"
#include <cmath>
#include <iostream>

#define bullet_maxspeed 20
#define bullet_timejump 16


void BULLET::init(){

/**
    --- INIT BULLETS --

    *Init List
    *Load ALL textures

**/
//Init List
FirstBullet = new Entity_bullet;
LastBullet  = new Entity_bullet;
FirstBullet->next = LastBullet;
LastBullet ->next = NULL;

timer = SDL_GetTicks();

//Init Bullet TEXTURES
texBullet[0] = LoadTex( "Data//Textures//Bullets//1.png" );
texBullet[1] = LoadTex( "Data//Textures//Bullets//2.png" );
texBullet[2] = LoadTex( "Data//Textures//Bullets//3.png" );
texBullet[3] = LoadTex( "Data//Textures//Bullets//4.png" );
}

void BULLET::shoot_to( bool faction,int prefab,int from_x,int from_y,int to_x,int to_y ){
Entity_bullet *newbullet = new Entity_bullet;

//Init
newbullet->faction = faction;
newbullet->x = from_x;
newbullet->y = from_y;
newbullet->w = 21;
newbullet->h = 21;
newbullet->tex = texBullet[prefab-1];
//Trajectory

if( from_x == to_x ) newbullet->velx =0;
///Traiectorie Pe X
else
{

newbullet->velx=((to_x-from_x)/sqrt((to_x-from_x)*(to_x-from_x)+(to_y-from_y)*(to_y-from_y)))*bullet_maxspeed;

}

if( from_y == to_y ) newbullet->vely =0;
///traiectorie Pe Y
else
{newbullet->vely=((to_y-from_y)/sqrt((to_x-from_x)*(to_x-from_x)+(to_y-from_y)*(to_y-from_y)))*bullet_maxspeed;;



}

//Add To List
newbullet->next = FirstBullet->next;
FirstBullet->next = newbullet;
}
void BULLET::shoot_unghi( bool faction,int prefab,int from_x,int from_y,double unghi ){
Entity_bullet *newbullet = new Entity_bullet;

//Init
newbullet->faction = faction;
newbullet->x = from_x;
newbullet->y = from_y;
newbullet->w = 21;
newbullet->h = 21;
newbullet->tex = texBullet[prefab-1];

///----CALC VELOCITY----
newbullet->velx=cos(unghi-pi/2)*bullet_maxspeed;
newbullet->vely=-sin(unghi-pi/2)*bullet_maxspeed;

//Add To List
newbullet->next = FirstBullet->next;
FirstBullet->next = newbullet;
}

void BULLET::handle(void){
bool increment = false;
Entity_bullet *auxbull;

if( timer + bullet_timejump < SDL_GetTicks() )
{
    timer = SDL_GetTicks();
    increment = true;
}

for( Entity_bullet *ibull = FirstBullet; !( ibull == LastBullet || ibull->next == LastBullet ||
                                            ibull == NULL || ibull->next == NULL ) ;  )
{
    bool checkCollison = true;

    //Check Advance
    if( increment )
    {
        ibull->next->x += ibull->next->velx;
        ibull->next->y += ibull->next->vely;

        if( ibull->next->x < -100 || ibull->next->x > SCREEN_WIDTH  + 100 ||
            ibull->next->y < -100 || ibull->next->y > SCREEN_HEIGHT + 100  )
        {
            //Sterge
            auxbull = ibull->next;
            ibull->next = ibull->next->next;
            delete auxbull;

            //Bullet Curent Nu trebuie verif
            //Motiv: trebuie trecut prin FOR neincrementat
            checkCollison = false;

            //Inchide Verif Gloante
            if( ibull == LastBullet || ibull->next == LastBullet ||
                 ibull == NULL || ibull->next == NULL )
            break;

        }
    }

//Check Collision
if( checkCollison )
{
    bool increment_bullet = true;

    ///Check Collision
    #define bx ibull->next->x
    #define by ibull->next->y
    #define bw ibull->next->w
    #define bh ibull->next->h

    //Attack Enemy
    if( ibull->next->faction == FACTION_PLAYER )
    {
        for( Enemy *ie = GAME_Enemies.getEnemyArray()->next;ie->next != NULL && ie != NULL ;ie = ie->next )
        if( ie->dying == false )
        {

            #define ex ie->rCenter.x + ie->x
            #define ey ie->rCenter.y + ie->y
            #define ew ie->rCenter.w
            #define eh ie->rCenter.h

            //Collision
            if( bx + bw > ex && bx < ex + ew &&
                by + bh > ey && by < ey + eh )
            {
                //Score
                PLAYER.addScore( 10 );

                //Damage enemy
                GAME_Enemies.attack( ie,20 );

                //Render Explosion
                GAME_EFFECTS.addAnim( bx ,by ,1 );

                //Delete Bulles

                auxbull = ibull->next;
                ibull->next = ibull->next->next;
                delete auxbull;

                increment_bullet = false;

                break;
            }

        }
    }
    else
    if( ibull->next->faction == FACTION_ENEMY )
    {
        //Attack Player
        #define px PLAYER.getCenter()->x + PLAYER.getBody()->x
        #define py PLAYER.getCenter()->y + PLAYER.getBody()->y
        #define pw PLAYER.getCenter()->w
        #define ph PLAYER.getCenter()->h

        //Collision
        if( bx + bw > px && bx < px + pw &&
            by + bh > py && by < py + ph )
        {
            //Damage
            PLAYER.damage();

            //Render Explosion

            //Delete Bullet
            auxbull = ibull->next;
            ibull->next = ibull->next->next;
            delete auxbull;

            increment_bullet = false;
        }
    }

    if( increment_bullet )
    ibull = ibull->next;
}



}

}
void BULLET::draw(){

for( Entity_bullet *ibull = FirstBullet->next;ibull != LastBullet; ibull = ibull->next )
{
    ApplyTex( ibull->x,ibull->y,ibull->tex );
}
}
void BULLET::cleanup(){
Entity_bullet *auxbull = NULL;
while( FirstBullet->next != LastBullet )
{
    auxbull = FirstBullet->next;
    FirstBullet->next = FirstBullet->next->next;
    delete auxbull;
}
}


