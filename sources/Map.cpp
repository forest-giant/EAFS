#include "headers.h"
#include "Map.h"
#include "Basics.h"
//#include "Console.h"
#include "enemy.h"
#include <cmath>
#include "settings.h"

#define mapScrollSpeed 1

void MAP::init(){

/**
    --- INIT MAPS ---

    *Init Misc
    *Load BG

**/


iMapWidth = 0;
iBgtexw = 0;
rAuxBg.x = 0;
rAuxBg.y = 0;
rAuxBg.w = 0;
rAuxBg.h = 0;
iTranslate = 0;

_complete = false;

SpawningEnemies = false;

timeBG = SDL_GetTicks();
timeTrans = SDL_GetTicks();

txBg  = LoadTex( "Data//Textures//Background.png" );
txBg2 = LoadTex( "Data//Textures//Background2.png" );
SDL_QueryTexture( txBg,0,0,&iBgtexw,&rAuxBg.h );

iBgx = 0;
iBgy = 0;
iBg2y = rAuxBg.h;
}
void MAP::connect(int iMapNr){

/**
    *Stop Enemy Spawn
    *Connect Map File to GAME for Streaming
**/

SpawningEnemies = false;

std::stringstream ssaux;
std::string saux;

//Close old
if( fileMap.is_open() ) fileMap.close();

ssaux<<"Data//Maps//"<<GAME_SETTINGS.getCMap();
//Open new
fileMap.open( ssaux.str().c_str() );
//Get first enemy info
fileMap >> cenemy_time>>cenemy_x>>cenemy_y>>cenemy_prefab>>cenemy_behavior;

_complete = false;

}
void MAP::startSpawnEnemies(void){

SpawningEnemies = true;

timeEnemySpawn = SDL_GetTicks();

if( GAME_SETTINGS.getTimeStart() > 0 )
{
    ignoreSpawn = true;
    timeIgnoreTill = GAME_SETTINGS.getTimeStart();
}
else
{
    ignoreSpawn = false;
}
}
void MAP::AddChunk( int nr,int x,int y ){
int iSlice = 0;

iSlice = floor( (double)x/MapSliceSize );

MapChunk* newchunk = new MapChunk;

//Asign val
newchunk->Body.x = x;
newchunk->Body.y = y;

if( nr == 1 )
{
    newchunk->tex    = txMC1;
    newchunk->Body.w =   600;
    newchunk->Body.h =   100;
}

newchunk->next = MapSlices[iSlice].FirstMapChunk->next;
MapSlices[iSlice].FirstMapChunk->next = newchunk;

if( MapSlices[iSlice].draw == false ) MapSlices[iSlice].draw = true;

}
void MAP::handleEnemySpawn(void){
#define ctime SDL_GetTicks() - timeEnemySpawn

if( SpawningEnemies )
{

    while( ( cenemy_time <= ctime || ( ignoreSpawn && cenemy_time < timeIgnoreTill ) )  && fileMap.is_open() )
    {
        //Spawn enemy
        if(  !ignoreSpawn  )
        {
            if( cenemy_behavior != -10 )
            GAME_Enemies.spawn( cenemy_x, cenemy_y, cenemy_prefab,cenemy_behavior );
            else
            //End Level
            _complete = true;
        }


        //Get next Enemy Data Stream
        if( fileMap >> cenemy_time )
        {
            fileMap >>cenemy_x>>cenemy_y>>cenemy_prefab>>cenemy_behavior;
        }

        else
        fileMap.close();
    }

    if( ignoreSpawn )
    {
        ignoreSpawn = false;
        timeEnemySpawn = SDL_GetTicks() - timeIgnoreTill;
    }

}
}
void MAP::handleLogics(void){

if( timeBG + 20 < SDL_GetTicks() )
{
    timeBG = SDL_GetTicks();
    iBgy  += mapScrollSpeed;
    iBg2y += mapScrollSpeed;

    //Reset Position
    if( iBgy  > 0 && iBg2y > iBgy ) iBg2y = - rAuxBg.h + iBgy;
    else
    if( iBg2y > 0 && iBg2y < iBgy ) iBgy  = - rAuxBg.h + iBg2y;

}

if( iTranslate != 0 && timeTrans + 15 < SDL_GetTicks()  )
{

    if( iTranslate == LEFT )
    {
        iTranslate_x -= 55;
        if( iTranslate_x <= -SCREEN_WIDTH ) iTranslate = 0;
    }
    else
    if( iTranslate == RIGHT  )
    {
        iTranslate_x += 55;
        if( iTranslate_x >= SCREEN_WIDTH  ) iTranslate = 0;
    }


    timeTrans = SDL_GetTicks();
}

}
void MAP::translate( int direct ){
iTranslate = direct;
//cons_out( direct );
iTranslate_x = 0;
}
void MAP::draw(){
//int i,viewp_x
//MapChunk *imc;

//viewp_x = 0;

///Render BG


if( iTranslate != 0 )
{
    //Old
    ApplyTex( iTranslate_x,iBgy    ,txBg,NULL,SCREEN_WIDTH );
    ApplyTex( iTranslate_x,iBg2y  ,txBg2,NULL,SCREEN_WIDTH );
    //New
    if( iTranslate == LEFT )
    {
        ApplyTex( iTranslate_x + SCREEN_WIDTH,iBgy   ,txBg,NULL,SCREEN_WIDTH );
        ApplyTex( iTranslate_x + SCREEN_WIDTH,iBg2y  ,txBg2,NULL,SCREEN_WIDTH );
    }
    else
    if( iTranslate == RIGHT )
    {
        ApplyTex( - SCREEN_WIDTH + iTranslate_x ,iBgy ,txBg,NULL,SCREEN_WIDTH );
        ApplyTex( - SCREEN_WIDTH + iTranslate_x ,iBg2y  ,txBg2,NULL,SCREEN_WIDTH );
    }

}
else
{
    ApplyTex( 0,iBgy,txBg,NULL,SCREEN_WIDTH );
    ApplyTex( 0,iBg2y,txBg2,NULL,SCREEN_WIDTH );
}

/*
///Render Entities
for( i = viewp_x/MapSliceSize;
     i < (viewp_x+iMapWidth)/MapSliceSize && i*MapSliceSize < SCREEN_WIDTH ;
     i++ )
    if( MapSlices[i].draw )
    {
        for( imc = MapSlices[i].FirstMapChunk->next;imc != MapSlices[i].LastMapChunk;imc = imc->next )
        {
            ApplyTex( imc->Body.x ,imc->Body.y,imc->tex,NULL,imc->Body.w,imc->Body.h );
        }
    }

*/
}
bool MAP::getComplete(){
return _complete;
}














