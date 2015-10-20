#include "sound.h"
#include "headers.h"
#include "Console.h"
#include "Player.h"
#include <cmath>

#define degrees 57.2957

void SOUND::init(){

/**
    ---LOADING MUSIC---

    *Init Audio
    *Load All Music  files
    *Load All Effect files

**/

int flags = MIX_INIT_OGG ,inited;

inited = Mix_Init( flags );

//ERROR
if( (inited & flags) != flags )
{
    //handle
    std::stringstream ssaux;
    cons_out( "Mix_init: Failed to init!",RED );

    ssaux<<"Mix_init: "<<Mix_GetError();
    cons_out( ssaux.str(),RED );
}

if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
{
    cons_out( "Mix_OpenAudio: fail!" );
}


iMusicChannel = -1;

//MUSIC
std::stringstream ssaux;
#define loadmusic(mus,src) mus = NULL; mus = Mix_LoadMUS( src ); if(mus==NULL){ ssaux.str("");ssaux<<"MusicLoadFail: "<< SDL_GetError(); cons_out( ssaux.str(), RED ); }
#define loadeffect(mus,src) mus = NULL; mus = Mix_LoadWAV( src ); if(mus==NULL){ ssaux.str("");ssaux<<"EffectLoadFail: "<< SDL_GetError(); cons_out( ssaux.str(), RED ); }

loadmusic( musMusic[0], "Data//Sound//Music//We're the Resistors.ogg" )
loadmusic( musMusic[1], "Data//Sound//Music//Underclocked.ogg" )

loadeffect( chEffects[0], "Data//Sound//Effects//mouse_over.ogg" );
loadeffect( chEffects[1], "Data//Sound//Effects//mouse_click.ogg" );

}
void SOUND::playMusic(int nr){
Mix_PlayMusic( musMusic[nr-1],-1 );
}
void SOUND::pauseMusic(void){
Mix_PauseMusic();
}
void SOUND::switchToMusic(int nr){
/// De adaugat FADEING
//Mix_FadeOutMusic( 500 );
//Mix_FadeInMusic( musMusic[nr-1],-1,500 );
Mix_PlayMusic( musMusic[nr-1],-1 );
}
void SOUND::playTEST(){
//Mix_SetDistance( iTestEffectChannel,100 );
//Mix_SetPosition( iTestEffectChannel,160 ,30 );
}
void SOUND::handleTEST(){
/*
#define ex 450
#define ey 250
#define px PLAYER.getBody()->x
#define py PLAYER.getBody()->y
#define trueDistance sqrt( (ex-px)*(ex-px) + (ey-py)*(ey-py) )

/// !de sters

Mix_SetPosition( iTestEffectChannel,
                 ((px-ex)/trueDistance)*degrees ,
                 (trueDistance<200)? trueDistance/200*255 : 255);
*/

}
void SOUND::playEffect(int effect){

Mix_PlayChannel( -1,chEffects[effect] ,0 );
}








