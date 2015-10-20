#include "headers.h"
#include "SDL2/SDL.h"
#include "Player.h"
#include "Basics.h"
#include "Map.h"
#include <cmath>
#include "Console.h"
#include "bullets.h"

///OPTIONS
#define bullet1CD 200

#define Move_Speed_key 3
#define Move_Speed_key_end 6

#define Move_Speed 20
#define modifier 1


#define TURN_NONE  0
#define TURN_LEFT  1
#define TURN_RIGHT 2

#define ACCEL_NONE 3
#define ACCEL_UP   4
#define ACCEL_DOWN 5

void PLAYERcls::init(){
/**
    --- LOAD PLAYER ---

        *Set Keybinding
        *Init Misc
        *Load Ship Texture

**/

int i;

///KEYBINDING
Keybind.UP      = SDL_SCANCODE_UP;
Keybind.DOWN    = SDL_SCANCODE_DOWN;
Keybind.LEFT    = SDL_SCANCODE_LEFT;
Keybind.RIGHT   = SDL_SCANCODE_RIGHT;
Keybind.ATTACK  = SDL_SCANCODE_X;

iTurnType = TURN_NONE;
timeTurn  = SDL_GetTicks();

velx = vely = 0;
omx  = omy  = 0;

iLivesLeft  = 5;
iScore      = 0;
iExploFrame = 0;
timeCheckMouse  = SDL_GetTicks();
timeSwitchFlame = SDL_GetTicks();
iCFlame = 0;
bFlame  = 0;

_respawning  = false;
_invi        = false;
_invi_forced = false;
_exploding   = false;

iExplo_x = 0;
iExplo_y = 0;

Body.x = 0;
Body.y = 0;
Body.w = 75;
Body.h = 80;

rCenter.x = 13;
rCenter.y = 20;
rCenter.w = 22;
rCenter.h = 34;

//Explosion
for( i = 0; i < 5; i++ )
{
    rExplo[i].x = 90*( i );
    rExplo[i].y = 0;
    rExplo[i].w = 90;
    rExplo[i].h = 70;
}


timeBulletCD = SDL_GetTicks();
timeMove     = SDL_GetTicks();
timeExplo    = SDL_GetTicks();

txSkin   = LoadTex( "Data//Textures//_playertex2.png" );
txShield = LoadTex( "Data//Textures//shield.png" );
txExplo  = LoadTex( "Data//Textures//explosion2.png" );

rRender_body.x = 0;
rRender_body.y = 0;
rRender_body.w = 75;
rRender_body.h = 65;

//Flame 1
rRender_flame[0].x = 5;
rRender_flame[0].y = 65;
rRender_flame[0].w = 42;
rRender_flame[0].h = 31;

rRender_flame[1].x = 5;
rRender_flame[1].y = 100;
rRender_flame[1].w = 42;
rRender_flame[1].h = 34;

//Flame 2
rRender_flame[2].x = 57;
rRender_flame[2].y = 67;
rRender_flame[2].w = 42;
rRender_flame[2].h = 43;

rRender_flame[3].x = 57;
rRender_flame[3].y = 109;
rRender_flame[3].w = 42;
rRender_flame[3].h = 43;

//Flame 3
rRender_flame[4].x = 104;
rRender_flame[4].y = 66;
rRender_flame[4].w = 42;
rRender_flame[4].h = 26;

rRender_flame[5].x = 104;
rRender_flame[5].y = 95;
rRender_flame[5].w = 42;
rRender_flame[5].h = 26;

}
void PLAYERcls::draw(){

#define draw_lines 0

///Render Player
//BODY
ApplyTex( Body.x -15 ,Body.y,txSkin,&rRender_body);
//FLAMES
ApplyTex( Body.x + 7,Body.y + 47,txSkin,&rRender_flame[iCFlame + bFlame]);
//SHIELD
if( _invi )
ApplyTex( Body.x - 32,Body.y - 40 ,txShield );

///Render Dev Lines

if( draw_lines )
{
    SDL_SetRenderDrawColor( RENDER_MAIN, 255,0,0,255 );
    SDL_RenderDrawLine( RENDER_MAIN,Body.x + rCenter.x,Body.y + rCenter.y,
                                    Body.x + rCenter.x + rCenter.w ,Body.y + rCenter.y );
    SDL_RenderDrawLine( RENDER_MAIN,Body.x + rCenter.x,Body.y + rCenter.y + rCenter.h,
                                    Body.x + rCenter.x + rCenter.w ,Body.y + rCenter.y + rCenter.h );
    SDL_RenderDrawLine( RENDER_MAIN,Body.x + rCenter.x,Body.y + rCenter.y,
                                    Body.x + rCenter.x,Body.y + rCenter.y + rCenter.h );
    SDL_RenderDrawLine( RENDER_MAIN,Body.x + rCenter.x + rCenter.w,Body.y + rCenter.y,
                                    Body.x + rCenter.x + rCenter.w,Body.y + rCenter.y + rCenter.h );
}



if( _exploding )
ApplyTex( iExplo_x, iExplo_y, txExplo, &rExplo[ iExploFrame ] );

}
SDL_Rect* PLAYERcls::getBody(void){
return &Body;
}
SDL_Rect* PLAYERcls::getCenter(void){
return &rCenter;
}
void PLAYERcls::setXY( int x,int y ){
Body.x = x;
Body.y = y;
}
void PLAYERcls::resetPos(void){ ///AND MISC
Body.x = 500;
Body.y = 650;
iBulletsShootLeft = 0;
_invi = false;
}
KeyBindings PLAYERcls::getKeybind(void){
return Keybind;
}
void PLAYERcls::handleKeys(){///Movement and Attack
int fsx,fsy,px,py;//,pw;//',ph;


const unsigned char *isKeyPress = SDL_GetKeyboardState(NULL);

    px = Body.x;
    py = Body.y;
    //pw = Body.w;
    //ph = Body.h;
///ATTACk
if( ( isKeyPress[Keybind.ATTACK] ) && //Key Pressed
     timeBulletCD + bullet1CD <= SDL_GetTicks() )//CoolDown
{
    GAME_BULLETS.shoot_to(FACTION_PLAYER,4,px      , py + 18,px     ,0 );
    GAME_BULLETS.shoot_to(FACTION_PLAYER,4,px + 29 , py + 18,px + 30,0 );

    timeBulletCD = SDL_GetTicks();
}


///MOVEMENT
///--TURN--
if( isKeyPress[Keybind.RIGHT] )
{
    if( iTurnType != TURN_RIGHT )
        velx = Move_Speed_key;

    iTurnType = TURN_RIGHT;
}
else
if( isKeyPress[Keybind.LEFT] )
{
    if( iTurnType != TURN_LEFT )
        velx = -Move_Speed_key;

    iTurnType = TURN_LEFT;
}
else
{
    velx = 0;
    iTurnType = TURN_NONE;
}

///--ACCELERATE--
if( isKeyPress[Keybind.UP] )
{
    if( iAccelType != ACCEL_UP )
        vely = -Move_Speed_key;

    iAccelType = ACCEL_UP;

    iCFlame = 2;
}
else
if( isKeyPress[Keybind.DOWN] )
{
    if( iAccelType != ACCEL_DOWN )
        vely = Move_Speed_key;

    iAccelType = ACCEL_DOWN;
    iCFlame = 4;
}
else
{
    vely = 0;
    iAccelType = ACCEL_NONE;
    iCFlame = 0;
}


fsx = px + velx;
fsy = py + vely;


///######## KEEP In Screen ##########################################################

if( fsx < 0 ) fsx -= velx;
else
if( fsx + 60 > SCREEN_WIDTH )//cons_out( fsx,RED ),fsx -= velx,cons_out( SCREEN_WIDTH,WHITE );
{
    ///SCREEN Differences
    //cons_out( px,RED );
    //cons_out( velx,RED );
    //cons_out( SCREEN_WIDTH,WHITE );
    fsx -= velx;
}

if( fsy < 0 ) fsy -= vely;
else
if( fsy + 100  > SCREEN_HEIGHT ) fsy -= vely;

///############################################################

///ACCELERATION
if( SDL_GetTicks() - timeTurn > 20 )
{

    //TURN
    if( iTurnType == TURN_LEFT )
    {
        if( velx > -Move_Speed_key_end ) velx--;
    }

    else if( iTurnType == TURN_RIGHT )
    {
        if( velx < Move_Speed_key_end ) velx++;
    }

    //ACCEL

    if( iAccelType == ACCEL_UP )
    {
        if( vely > -Move_Speed_key_end ) vely--;
    }
    else
    if( iAccelType == ACCEL_DOWN )
    {
        if( vely <  Move_Speed_key_end ) vely++;
    }

timeTurn = SDL_GetTicks();
}

/// ---MOVEMENT----
if( !_respawning && SDL_GetTicks() - timeMove >= 16 )
{
    Body.x = fsx;
    Body.y = fsy;
    timeMove = SDL_GetTicks();
}

}
void PLAYERcls::handleMouse(){
#define px (PLAYERcls::Body.x + PLAYERcls::rCenter.x + PLAYERcls::rCenter.w/2 )
#define py (PLAYERcls::Body.y + PLAYERcls::rCenter.y + PLAYERcls::rCenter.h/2 )

/// ---SHOOTING---
if( iBulletsShootLeft > 0 && SDL_GetTicks() - timeBulletCD > 180 ) //FireRate
{
    GAME_BULLETS.shoot_to(FACTION_PLAYER,2,PLAYERcls::Body.x      , PLAYERcls::Body.y + 18,PLAYERcls::Body.x     ,0 );
    GAME_BULLETS.shoot_to(FACTION_PLAYER,2,PLAYERcls::Body.x + 29 , PLAYERcls::Body.y + 18,PLAYERcls::Body.x + 30,0 );

    timeBulletCD = SDL_GetTicks();
    iBulletsShootLeft --;
}

/// ---MOVEMENT---
///ATTEMPT 3

#define difx nmx-omx
#define dify nmy-omy

int nmx,nmy;
double dist;
if( !_respawning && SDL_GetTicks() - timeCheckMouse > 10 ){

SDL_GetMouseState( &nmx,&nmy );

dist = sqrt(  pow( nmx-omx ,2) +  pow( nmy-omy ,2) );


if( dist >= 1 )
{
    if( dist < Move_Speed )
    {
        ///---X---
        if( (difx > 0 && Body.x + Body.w < SCREEN_WIDTH) || (difx < 0 && Body.x > 0) )
            PLAYERcls::Body.x += (difx)/dist*   dist    *modifier;
        ///---Y---
        if( (dify > 0 && Body.y + Body.h < SCREEN_HEIGHT) || (dify < 0 && Body.y > 0) )
            PLAYERcls::Body.y += (dify)/dist*   dist    *modifier;
        //cons_out( (difx)/dist*   dist );
    }
    else
    {
        ///---X---
        if( (difx > 0 && Body.x + Body.w < SCREEN_WIDTH) || (difx < 0 && Body.x > 0) )
            PLAYERcls::Body.x += (difx)/dist*   Move_Speed  *modifier;
        ///---Y---
        if( (dify > 0 && Body.y + Body.h < SCREEN_HEIGHT) || (dify < 0 && Body.y > 0) )
            PLAYERcls::Body.y += (dify)/dist*   Move_Speed  *modifier;
        //cons_out( (difx)/dist*   Move_Speed );
    }

}

omx = nmx;
omy = nmy;

if( nmx > SCREEN_WIDTH/2  + 400 || nmx < SCREEN_WIDTH/2  - 400 )
{
    SDL_WarpMouseInWindow( WINDOW_MAIN, SCREEN_WIDTH/2, nmy );
    nmx = SCREEN_WIDTH/2;
    omx = nmx;
}


if( nmy > SCREEN_HEIGHT/2 + 300 || nmy < SCREEN_HEIGHT/2 - 300 )
{
    SDL_WarpMouseInWindow( WINDOW_MAIN, nmx, SCREEN_WIDTH/2 );
    nmy = SCREEN_WIDTH/2;
    omy = nmy;
}

timeCheckMouse = SDL_GetTicks();
}
}
void PLAYERcls::handleMisc(void){
if( SDL_GetTicks() - timeSwitchFlame >= 100 )
{
    bFlame = !bFlame;
    timeSwitchFlame = SDL_GetTicks();
}

//Respawn Animation( Move up )
if( _respawning && timeRespawn + 10 < SDL_GetTicks() )
{
    timeRespawn = SDL_GetTicks();
    Body.y -= 2;

    if( Body.y <= 650 )
        _respawning = false;
}

//<NATURAL> Invinciblity
if( !_invi_forced && _invi && timeInvi + 4500 < SDL_GetTicks() )
{
    //Disable Invi
    _invi = false;
}

//Explosion
//Move
if( _exploding && timeExplo_move + 16 < SDL_GetTicks() )
{
    iExplo_x += iExplo_velx;
    iExplo_y += iExplo_vely;

    timeExplo_move = SDL_GetTicks();
}
//Animation
if( _exploding && timeExplo + 100 < SDL_GetTicks() )
{
    if( iExploFrame < 7 )
    {
        iExploFrame ++;

        timeExplo = SDL_GetTicks();
    }
    else
    {
        _exploding = false;
    }
}

}
void PLAYERcls::StartShootingSequence(void){
iBulletsShootLeft = 2;
}
int  PLAYERcls::getLivesLeft(void){
return iLivesLeft;
}
int  PLAYERcls::getScore(void){
return iScore;
}
void PLAYERcls::addScore(int score){
iScore += score;
}
void PLAYERcls::resetScore(void){
iScore = 0;
}
void PLAYERcls::resetLives(void){
iLivesLeft = 5;
}
bool PLAYERcls::getInvi(void){
return _invi;
}
void PLAYERcls::damage(void){

if( _invi == false )
{
    //Exploding
    _exploding     = true;
    iExploFrame    = 0;
    timeExplo      = SDL_GetTicks();
    timeExplo_move = SDL_GetTicks();
    iExplo_x = Body.x - 10;
    iExplo_y = Body.y;// - 45;
    iExplo_velx = velx;
    iExplo_vely = vely;

    iLivesLeft--;

    if( iLivesLeft > 0 )
    {
        //Killed

        //Reposition
        PLAYERcls::resetPos();
        Body.y = 1000;


        //Respawn
        _respawning = true;
        timeRespawn = SDL_GetTicks();

        //Give Invi
        _invi = true;
        timeInvi = SDL_GetTicks();

    }
    ///GAME OVER
    else
    {
        Body.y = 1000;
    }


}

}
void PLAYERcls::setInvi_forced(bool x){
_invi = x;
_invi_forced = x;
}















