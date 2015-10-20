#include "enemy.h"
#include "bullets.h"
#include "Player.h"
#include <cmath>


void Enemies::init(){
FirstEnemy = new Enemy;
LastEnemy  = new Enemy;
FirstEnemy->next = LastEnemy;
LastEnemy ->next = NULL;

timeAnimFlame = SDL_GetTicks();
bCFlame       = 0;

texEnemySkins[0] = LoadTex( "Data//Textures//Enemies//1.png" );
texEnemySkins[1] = LoadTex( "Data//Textures//Enemies//2.png" );
texEnemySkins[2] = LoadTex( "Data//Textures//Enemies//5_2.png" );
texEnemySkins[3] = LoadTex( "Data//Textures//Enemies//6.png" );

timePhaseDie = SDL_GetTicks();
bPhaseDie = 1;

rBody[0].x = 0;
rBody[0].y = 0;
rBody[0].w = 50;
rBody[0].h = 50;

rBody[1].x = 0;
rBody[1].y = 0;
rBody[1].w = 50;
rBody[1].h = 40;

rBody[2].x = 0;
rBody[2].y = 0;
rBody[2].w = 120;
rBody[2].h = 83;


rFlame_1[0].x = 125;
rFlame_1[0].y = 38;
rFlame_1[0].w = 22;
rFlame_1[0].h = 22;

rFlame_2[0].x = 125;
rFlame_2[0].y = 61;
rFlame_2[0].w = 22;
rFlame_2[0].h = 22;

}
void Enemies::spawn( int x,int y,int prefab,int behavior ){//prefab = set of options
Enemy *newenemy = new Enemy;

//Setup
newenemy->x = x;
newenemy->y = y;
newenemy->w = 117;
newenemy->h = 83;
newenemy->phase  = 0;
newenemy->dead   = false;
newenemy->dying  = false;
newenemy->show   = true;
newenemy->prefab = prefab;
newenemy->behavior = behavior;
newenemy->timer  = SDL_GetTicks();
newenemy->timer2 = SDL_GetTicks();
newenemy->timer3 = SDL_GetTicks();


//Meteorit 1(mediu-small)
if( prefab == 1 )
{
newenemy->health = 150;
newenemy->tex = texEnemySkins[3];
newenemy->rCenter.x = 15;
newenemy->rCenter.y = 15;
newenemy->rCenter.w = 45;
newenemy->rCenter.h = 45;
}
//Meteorit 2(mediu)
if( prefab == 2 )
{
newenemy->health = 350;
newenemy->tex = texEnemySkins[3];
newenemy->rCenter.x = 20;
newenemy->rCenter.y = 20;
newenemy->rCenter.w = 85;
newenemy->rCenter.h = 85;
}
//Meteorit 3(big)
if( prefab == 3 )
{
newenemy->health = 550;
newenemy->tex = texEnemySkins[2];
newenemy->rCenter.x = 30;
newenemy->rCenter.y = 30;
newenemy->rCenter.w = 140;
newenemy->rCenter.h = 140;
}
//Meteorit 4(planet-big)
if( prefab == 4 )
{
newenemy->health = 25000;
newenemy->tex = texEnemySkins[2];
newenemy->rCenter.x = 70;
newenemy->rCenter.y = 70;
newenemy->rCenter.w = 340;
newenemy->rCenter.h = 340;
}
//Nava 1
else if( prefab == 5 )
{
newenemy->health = 200;
newenemy->tex = texEnemySkins[0];
newenemy->rCenter.x = 16;
newenemy->rCenter.y = 18;
newenemy->rCenter.w = 84;
newenemy->rCenter.h = 20;
}
//Nava Galbena
else if( prefab == 903 )
{
newenemy->health = 100;
newenemy->tex = texEnemySkins[1];
newenemy->rCenter.x = 10;
newenemy->rCenter.y = 5;
newenemy->rCenter.w = 30;
newenemy->rCenter.h = 30;
}

//Add to list
newenemy->next = FirstEnemy->next;
FirstEnemy->next = newenemy;
}
void Enemies::reset_list(void){
Enemy *aux;

while( FirstEnemy->next != LastEnemy )
{
    aux = FirstEnemy->next;
    FirstEnemy->next = FirstEnemy->next->next;
    delete aux;
}

}
void Enemies::attack( Enemy * enemy, int damage ){
enemy->health -= damage;
if( enemy->health <= 0 )
{
    enemy->dying = true;
    enemy->timedie = SDL_GetTicks();
    PLAYER.addScore( 200 );
}

}
void Enemies::draw(void){

#define draw_lines 0

Enemy *ie,*delaux;
for( ie = FirstEnemy; ie->next != LastEnemy && ie != LastEnemy ;ie = ie->next )
{
    //Still allive , draw
    if( ie->next->dying == false || bPhaseDie == 1 )
    {
        ///Draw Enemy Ship

        if( ie->next->prefab == 1 )
        {
            //Body
            ApplyTex( ie->next->x,ie->next->y,ie->next->tex,NULL,75,75 );
        }
        else if( ie->next->prefab == 2 )
        {
            //Body
            ApplyTex( ie->next->x,ie->next->y,ie->next->tex,NULL,125,125 );
        }
        else if( ie->next->prefab == 3 )
        {
            //Body
            ApplyTex( ie->next->x,ie->next->y,ie->next->tex,NULL,200,200 );
        }
        else if( ie->next->prefab == 4 )
        {
            //Body
            ApplyTex( ie->next->x,ie->next->y,ie->next->tex,NULL,500,500 );
        }
        else if( ie->next->prefab == 5 )
        {

            //Body
            ApplyTex( ie->next->x,ie->next->y,ie->next->tex,&rBody[ 2 ] );
            //Flames
            if( bCFlame == 0 )
            {
                //Flame 1
                ApplyTex( ie->next->x + 22 ,ie->next->y ,ie->next->tex,&rFlame_1[0] );
                //Flame 2
                ApplyTex( ie->next->x + 75 ,ie->next->y ,ie->next->tex,&rFlame_2[0] );
            }
            else
            if( bCFlame == 1 )
            {
                //Flame 1
                ApplyTex( ie->next->x + 22 ,ie->next->y ,ie->next->tex,&rFlame_2[0] );
                //Flame 2
                ApplyTex( ie->next->x + 75 ,ie->next->y ,ie->next->tex,&rFlame_1[0] );
            }
        }
        else
        if( ie->next->prefab == 103 )
        {
            //Body
            ApplyTex( ie->next->x,ie->next->y,ie->next->tex,&rBody[ 1 ] );
        }



        ///Draw Center Rect
        if( draw_lines == true ){
        SDL_SetRenderDrawColor( RENDER_MAIN,255,0,0,255 );
        SDL_RenderDrawLine( RENDER_MAIN,
                            ie->next->rCenter.x + ie->next->x,
                            ie->next->rCenter.y + ie->next->y,
                            ie->next->rCenter.x + ie->next->rCenter.w + ie->next->x,
                            ie->next->rCenter.y  + ie->next->y);
        SDL_RenderDrawLine( RENDER_MAIN,
                            ie->next->rCenter.x + ie->next->rCenter.w + ie->next->x,
                            ie->next->rCenter.y + ie->next->y,
                            ie->next->rCenter.x + ie->next->rCenter.w + ie->next->x,
                            ie->next->rCenter.y + ie->next->rCenter.h + ie->next->y );
        SDL_RenderDrawLine( RENDER_MAIN,
                            ie->next->rCenter.x + ie->next->x,
                            ie->next->rCenter.y + ie->next->rCenter.h + ie->next->y,
                            ie->next->rCenter.x + ie->next->rCenter.w + ie->next->x,
                            ie->next->rCenter.y + ie->next->rCenter.h + ie->next->y );
        SDL_RenderDrawLine( RENDER_MAIN,
                            ie->next->rCenter.x + ie->next->x,
                            ie->next->rCenter.y + ie->next->y,
                            ie->next->rCenter.x + ie->next->x,
                            ie->next->rCenter.y + ie->next->rCenter.h + ie->next->y );
        }

    }

    if( ie->next->dead == true ) //enemy si Dead => DELETE
    {
        delaux = ie->next;
        ie->next = ie->next->next;
        delete delaux;
    }

}

}
Enemy *Enemies::getEnemyArray(void){
return FirstEnemy;
}


