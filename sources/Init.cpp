#include "headers.h"
#include "SDL2/SDL_image.h"
#include <fstream>
#include "Player.h"
#include "Map.h"
#include "Console.h"
#include "bullets.h"
#include "enemy.h"
#include "interface.h"
#include "sound.h"
#include "effects.h"
#include "settings.h"

int SCREEN_WIDTH  = 1024;
int SCREEN_HEIGHT = 768;//768
int AS_RATIO_X = 1;
int AS_RATIO_Y = 1;
Uint32 WINDOW_MAIN_ID =-1;


bool Init(){

if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
{
    return false;
}

if( TTF_Init() == -1 )
    return false;

///OPEN FONTS
Font_Amble_16 = TTF_OpenFont( "Data//Fonts//Amble-Regular.ttf",16 );
Font_Amble_20 = TTF_OpenFont( "Data//Fonts//Amble-Regular.ttf",20 );
Font_Amble_24 = TTF_OpenFont( "Data//Fonts//Amble-Regular.ttf",24 );
Font_Amble_30 = TTF_OpenFont( "Data//Fonts//Amble-Regular.ttf",30 );

///-----CONSOLE INIT------
Cons_init();
Cons_update_text();
Cons_update_command();

///-----MAIN WINDOW INIT----
int iWindowFlags = 0,iRenderFlags = 0;

iWindowFlags  = SDL_WINDOW_SHOWN;
if( GAME_SETTINGS.getFullScr() ) iWindowFlags |= SDL_WINDOW_FULLSCREEN;


WINDOW_MAIN = SDL_CreateWindow( "E.A.F.S",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH,SCREEN_HEIGHT,iWindowFlags );//| SDL_WINDOW_FULLSCREEN
if( WINDOW_MAIN == NULL )
{
    return false;
}


iRenderFlags |= SDL_RENDERER_ACCELERATED;

if( GAME_SETTINGS.getVsync() )
    iRenderFlags |= SDL_RENDERER_PRESENTVSYNC;

RENDER_MAIN = SDL_CreateRenderer( WINDOW_MAIN,-1, SDL_RENDERER_ACCELERATED | iRenderFlags );//| SDL_RENDERER_PRESENTVSYNC
if( RENDER_MAIN == NULL )
{
    return false;
}

WINDOW_MAIN_ID = SDL_GetWindowID( WINDOW_MAIN );

///--INIT CLASSES--
GAME_SOUND    .init();
PLAYER        .init();
GAME_MAP      .init();
GAME_BULLETS  .init();
GAME_Enemies  .init();
GAME_INTERFACE.init();
GAME_EFFECTS  .init();


return true;
}

MapSlice *MapSlices;

SETTINGS  GAME_SETTINGS;
PLAYERcls PLAYER;
MAP       GAME_MAP;
BULLET    GAME_BULLETS;
Enemies   GAME_Enemies;
Interface GAME_INTERFACE;
SOUND     GAME_SOUND;
EFFECTS   GAME_EFFECTS;


///FONTS
TTF_Font *Font_Amble_16,*Font_Amble_20,*Font_Amble_24,*Font_Amble_30;


///COLORS
SDL_Color ConsTextColor = {   0,213, 31,255 },  ///WHITE
          ConsBgColor   = {   0,  0,  0,255 },  ///BLACK
          WHITE         = { 255,255,255,255 },
          RED           = { 255,  0,  0,255 },
          YELLOW        = { 255,233,177,255 },
          BLACK         = {   0,  0,  0,  0 } ;
