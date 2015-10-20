#include "effects.h"
#include <cmath>

#include "Console.h"
//#include "windows.h"
#include <time.h>
#include <stdlib.h>
#define frameDelay 40

void EFFECTS::init(){
FirstEffect_cod = new Effect;
LastEffect_cod  = new Effect;
FirstEffect_cod ->next = LastEffect_cod;
FirstEffect_cod ->prev = NULL;
LastEffect_cod  ->next = NULL;
LastEffect_cod  ->prev = FirstEffect_cod;

FirstStar = new EFFECT_STAR;
LastStar  = new EFFECT_STAR;
FirstStar->next = LastStar;
LastStar ->next = NULL;

timeSpawnStars = SDL_GetTicks() + 10000;
timeMoveStars  = SDL_GetTicks();

srand( SDL_GetTicks() );

texEFFECTS[0] = LoadTex( "Data//Textures//Bullets//a1.png" );
}
void EFFECTS::addAnim( int x,int y,int nr ){
Effect *newef = new Effect;
int aux,aux2;

//LINK
newef ->next = LastEffect_cod;
newef ->prev = LastEffect_cod->prev;
LastEffect_cod->prev = newef;

//ASSIGN
newef ->x  = x;
newef ->y  = y;
newef ->nr = nr;
newef ->display   = true;
newef ->frame     = 0;
newef ->frameend  = 0;
newef ->timeFrame = SDL_GetTicks();
newef ->timeMove  = SDL_GetTicks();

//Tex
newef->tex = texEFFECTS[nr-1];
SDL_QueryTexture( newef->tex, 0,0, &aux,&aux2 );
newef ->frameend = ceil( (double)aux2/aux );

newef ->w = aux;

}
void EFFECTS::handleAndDrawStars(){
EFFECT_STAR *i,*delaux;
SDL_Rect StarBody;

//Add
if( SDL_GetTicks() - timeSpawnStars > 2000 )
{
    for( int j = 0; j < 25; j ++ )
    {
        EFFECT_STAR *newstar = new EFFECT_STAR;

        //Lista
        newstar   -> next = FirstStar->next;
        FirstStar -> next = newstar;

        //Info
        newstar->timeSpawn = SDL_GetTicks();
        newstar->x = rand() % SCREEN_WIDTH;
        newstar->y = rand() % SCREEN_HEIGHT;
    }

    timeSpawnStars = SDL_GetTicks();
}

///Display
StarBody.w = 2;
StarBody.h = 2;


for( i = FirstStar;
     i->next != LastStar && i != LastStar && i != NULL ;
      )
{
    //Move
    if( SDL_GetTicks() - timeMoveStars > 40 )
    {
        i->next->y += 4;
    }


    //Draw
    #define max_r 220
    #define max_g 190
    #define max_b 250

    #define dif (SDL_GetTicks() - i->next->timeSpawn)
    #define dif_per dif/1000
    #define dif_per2 (dif-3000)/1000

    if( dif < 1000 )
        SDL_SetRenderDrawColor( RENDER_MAIN,
                                30 + (max_r-30)*dif_per ,30 + (max_g-30)*dif_per,30 + (max_b-30)*dif_per,
                                255 );
    else
    if( dif > 3000 )
        SDL_SetRenderDrawColor( RENDER_MAIN,
                                max_r - (max_r-30)*dif_per2 ,max_g - (max_g-30)*dif_per2,max_b - (max_b-30)*dif_per2,
                                255 );
    else
    SDL_SetRenderDrawColor( RENDER_MAIN,max_r ,max_g ,max_b,255 );


    StarBody.x = i->next->x;
    StarBody.y = i->next->y;


    SDL_RenderDrawRect( RENDER_MAIN, &StarBody );

    //Check if Expired
    if( SDL_GetTicks() - i->next->timeSpawn > 4000 )
    {
        //Delete
        delaux = i->next;
        i->next = i->next->next;

        delete delaux;
    }
    else
    i = i->next;
}

if( SDL_GetTicks() - timeMoveStars > 40 )
    timeMoveStars = SDL_GetTicks();

}
void EFFECTS::draw(){//AND HANDLE
Effect *ief;
SDL_Rect rBody;

rBody.x = 0;


for( ief = LastEffect_cod->prev; ief->prev != NULL; ief = ief->prev )
if( ief->display ){

//Next Frame
if( ief->timeFrame + frameDelay <= SDL_GetTicks() && ief->frame < ief->frameend )
{
    ief->frame ++;
    ief->timeFrame = SDL_GetTicks();

    if( ief->frame == ief->frameend )
    {
        ief->display = false;
    }
}

//Bullet spread
if( ief->nr == 1 )
{
    #define vely 3

    //Body
    rBody.w = ief->w;
    rBody.h = rBody.w;

    rBody.y = rBody.h *( ief->frameend -1 - ief->frame );

    //Time move
    if( SDL_GetTicks() - ief->timeMove > 10 )
    {
        ief->y -= 2;
        ief->timeMove = SDL_GetTicks();
    }


    //Show
    ApplyTex( ief->x, ief->y, ief->tex, &rBody );
}
else
{
    #define vely 3

    //Body
    rBody.w = ief->w;
    rBody.h = rBody.w;

    rBody.y = rBody.h *( ief->frameend -1 - ief->frame );

    //Time move
    if( SDL_GetTicks() - ief->timeMove > 10 )
    {
        ief->y += 1;
    }

    //Show
    ApplyTex( ief->x, ief->y, ief->tex, &rBody );
}



}

}


