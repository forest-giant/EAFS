#include "headers.h"
#include "menus.h"
#include "settings.h"
#include "SDL2/SDL_mixer.h"


int main(int argc,char **argv){

GAME_SETTINGS.loadFromFile();

if( !Init() ) return 1; /// <--LEVEL 1 ERROR on INIT

//Set Volume
Mix_VolumeMusic( GAME_SETTINGS.getVolume() );

//RUN_GAME();
RUNMENU_MAIN();
//RUNMENU_SETTINGS();

return 0;
}
