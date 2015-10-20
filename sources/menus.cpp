#include "menus.h"
#include "sound.h"
#include "settings.h"
#include "interface.h"
#include <cstdlib>

void RUNMENU_SETTINGS(){
///VAR
SDL_Event event;
bool RUN = true,_vsync;
int _FPScap;
GAME_Entity geBg,geVsync,geFPScap_30,geFPScap_60,geFPScap_120,geBack;

///INIT
//BACKGROUND
geBg.setTex( "Data//Textures//Menus//bg_settings.png" );
geBg.setPosition( SCREEN_WIDTH/2 - geBg.getSizeW()/2, SCREEN_HEIGHT/2 - geBg.getSizeH()/2 );
//Back Button
geBack.setTex( "Data//Textures//Menus//back.png" );
geBack.setPosition( SCREEN_WIDTH/2 - geBack.getSizeW()/2,
                    SCREEN_HEIGHT/2 + geBg.getSizeH()/2 - geBack.getSizeH() - 10 );

_vsync  = GAME_SETTINGS.getVsync();
_FPScap = GAME_SETTINGS.getFPScap();

geVsync.setTex( "Data//Textures//Menus//check.png" );
geVsync.setPosition( SCREEN_WIDTH/2 - geBg.getSizeW()/2 + 222,
                     SCREEN_HEIGHT/2 - geBg.getSizeH()/2 + 156 );
geFPScap_30.setTex( "Data//Textures//Menus//check.png" );
geFPScap_60.setTex( "Data//Textures//Menus//check.png" );
geFPScap_120.setTex( "Data//Textures//Menus//check.png" );

geFPScap_30.setPosition(   SCREEN_WIDTH/2 - geBg.getSizeW()/2 + 223,
                            SCREEN_HEIGHT/2 - geBg.getSizeH()/2 + 193 );
geFPScap_60.setPosition(   SCREEN_WIDTH/2 - geBg.getSizeW()/2 + 310,
                            SCREEN_HEIGHT/2 - geBg.getSizeH()/2 + 192 );
geFPScap_120.setPosition(  SCREEN_WIDTH/2 - geBg.getSizeW()/2 + 407,
                            SCREEN_HEIGHT/2 - geBg.getSizeH()/2 + 192 );

std::stringstream ssaux;
GAME_Text gtText( "" );

ssaux<<SCREEN_WIDTH<<'x'<<SCREEN_HEIGHT;
gtText.setFont( Font_Amble_24 );
gtText.setText( ssaux.str().c_str() );// ,'x',(std::string)(SCREEN_HEIGHT) );
gtText.setPosX( SCREEN_WIDTH/2 - geBg.getSizeW()/2 + 170 );
gtText.setPosY( SCREEN_HEIGHT/2 - geBg.getSizeH()/2 + 124 );

///LOOP
while( RUN ){

///EVENTS
while( SDL_PollEvent( &event ) )
{
    //Console
    Cons_giveEvent( &event );

    if( event.type == SDL_QUIT ) RUN = false;
    else
    if( event.type == SDL_KEYDOWN )
    {
        if( event.key.keysym.sym == SDLK_ESCAPE )
        {
            GAME_MAP.translate( RIGHT );

            RUN = false;
        }

    }
    else
    if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT )
    {
        int mouse_x,mouse_y;

        mouse_x = event.button.x;
        mouse_y = event.button.y;

        if( mouse_x > geVsync.getPosX() && mouse_x < geVsync.getPosX() + geVsync.getSizeW() &&
            mouse_y > geVsync.getPosY() && mouse_y < geVsync.getPosY() + geVsync.getSizeH() )
        {
            _vsync = !_vsync;
            GAME_SETTINGS.setVsync( _vsync );

            GAME_SOUND.playEffect( 1 );
        }
        else
        if( mouse_x > geFPScap_30.getPosX() && mouse_x < geFPScap_30.getPosX() + geFPScap_30.getSizeW() &&
            mouse_y > geFPScap_30.getPosY() && mouse_y < geFPScap_30.getPosY() + geFPScap_30.getSizeH() )
        {
            _FPScap = 30;
            GAME_SETTINGS.setFPScap( 30 );
            GAME_SOUND.playEffect( 1 );
        }
        else
        if( mouse_x > geFPScap_60.getPosX() && mouse_x < geFPScap_60.getPosX() + geFPScap_60.getSizeW() &&
            mouse_y > geFPScap_60.getPosY() && mouse_y < geFPScap_60.getPosY() + geFPScap_60.getSizeH() )
        {
            _FPScap = 60;
            GAME_SETTINGS.setFPScap( 60 );
            GAME_SOUND.playEffect( 1 );
        }
        else
        if( mouse_x > geFPScap_120.getPosX() && mouse_x < geFPScap_120.getPosX() + geFPScap_120.getSizeW() &&
            mouse_y > geFPScap_120.getPosY() && mouse_y < geFPScap_120.getPosY() + geFPScap_120.getSizeH() )
        {
            _FPScap = 120;
            GAME_SETTINGS.setFPScap( 120 );
            GAME_SOUND.playEffect( 1 );
        }
        else
        if( mouse_x > geBack.getPosX() && mouse_x < geBack.getPosX() + geBack.getSizeW() &&
            mouse_y > geBack.getPosY() && mouse_y < geBack.getPosY() + geBack.getSizeH() )
        {
            GAME_MAP.translate( RIGHT );
            GAME_SOUND.playEffect( 1 );
            RUN = false;
        }

    }

    GAME_SETTINGS.saveToFile();
}
///LOGICS

GAME_MAP.handleLogics();

///RENDER

GAME_MAP.draw();

geBg.draw();
gtText.draw();
geBack.draw();


//CHECKS
if( _vsync )
    geVsync.draw();
if( _FPScap == 30 )
geFPScap_30.draw();
else
if( _FPScap == 60 )
geFPScap_60.draw();
else
if( _FPScap == 120 )
geFPScap_120.draw();



SDL_RenderPresent( RENDER_MAIN );

}
}
void RUNMENU_MAIN(){
///VAR
SDL_Event event;
bool RUN = true,switchTo_settings = false,switchTo_main = false,showtitle = true
     ,onbutton_play = false,onbutton_settings = false, onbutton_quit = false;
GAME_Entity geTitle,geButton_play,geButton_settings,geButton_quit;
Uint32 timeSwitch,timeFade;
int iTexAlpha,iMoveTimes;
SDL_Texture *txButton_play,*txButton_play_over,*txButton_settings,*txButton_settings_over,
            *txButton_quit,*txButton_quit_over;

///INIT
//Init Textures
txButton_play           = LoadTex( "Data//Textures//Menus//button_play.png" );
txButton_play_over      = LoadTex( "Data//Textures//Menus//button_play_over.png" );

txButton_settings       = LoadTex( "Data//Textures//Menus//button_settings.png" );
txButton_settings_over  = LoadTex( "Data//Textures//Menus//button_settings_over.png" );

txButton_quit           = LoadTex( "Data//Textures//Menus//button_quit.png" );
txButton_quit_over      = LoadTex( "Data//Textures//Menus//button_quit_over.png" );


//Title
geTitle.setTex( "Data//Textures//title.png" );
geTitle.setPosition( SCREEN_WIDTH/2 - geTitle.getSizeW()/2,0 );
//PLAY
geButton_play       .setTex( txButton_play );
geButton_play.setPosition( SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2-50 );
//SETTINGS
geButton_settings   .setTex( txButton_settings );
geButton_settings.setPosition( SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2 + 50 );
//QUIT
geButton_quit       .setTex( txButton_quit );
geButton_quit.setPosition( SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2+150 );


GAME_INTERFACE.switchCursor( CURSOR_DEFAULT );

///Play Music
GAME_SOUND.playMusic( 1 );

///LOOP
while( RUN ){

///EVENTS
while( SDL_PollEvent( &event ) ){
//Console
Cons_giveEvent( &event );


    if( event.type == SDL_QUIT ) RUN = false;
    else
    if( event.type == SDL_KEYDOWN )
    {
        if( event.key.keysym.sym == SDLK_ESCAPE ) RUN = false;
    }
    else
    if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && switchTo_settings == false )
    {
        int mouse_x,mouse_y;

        mouse_x = event.button.x;
        mouse_y = event.button.y;

        //PLAY
        if( mouse_x > geButton_play.getPosX() && mouse_x < geButton_play.getPosX() + geButton_play.getSizeW() &&
            mouse_y > geButton_play.getPosY() && mouse_y < geButton_play.getPosY() + geButton_play.getSizeH() )
        {
            GAME_SOUND.playEffect( 1 );

            RUN_GAME();
            //Switch to menu mouse
            GAME_SOUND.playMusic( 1 );
            GAME_INTERFACE.switchCursor( CURSOR_DEFAULT );
            SDL_SetWindowTitle( WINDOW_MAIN, "E.A.F.S" );
        }
        else
        //SETTINGS
        if( mouse_x > geButton_settings.getPosX() && mouse_x < geButton_settings.getPosX() + geButton_settings.getSizeW() &&
            mouse_y > geButton_settings.getPosY() && mouse_y < geButton_settings.getPosY() + geButton_settings.getSizeH() )
        {
            GAME_SOUND.playEffect( 1 );

            //Deselect Button
            geButton_play     .setTex( txButton_play );
            geButton_settings .setTex( txButton_settings );
            geButton_quit     .setTex( txButton_quit );

            //fade out and start switching
            switchTo_settings = true;
            showtitle = false;
            timeSwitch = SDL_GetTicks();
            timeFade   = SDL_GetTicks();
            iTexAlpha  = 220;
            iMoveTimes = 0;

            //translate map GAME_MAP.
            GAME_MAP.translate( LEFT );
        }
        else
        //QUIT
        if( mouse_x > geButton_quit.getPosX() && mouse_x < geButton_quit.getPosX() + geButton_quit.getSizeW() &&
            mouse_y > geButton_quit.getPosY() && mouse_y < geButton_quit.getPosY() + geButton_quit.getSizeH() )
        {
            GAME_SOUND.playEffect( 1 );

            RUN = false;
        }

    }
    else
    if( event.type == SDL_MOUSEMOTION && switchTo_settings == false )
    {
        int mouse_x,mouse_y;

        mouse_x = event.motion.x;
        mouse_y = event.motion.y;

        //PLAY
        if( mouse_x > geButton_play.getPosX() && mouse_x < geButton_play.getPosX() + geButton_play.getSizeW() &&
            mouse_y > geButton_play.getPosY() && mouse_y < geButton_play.getPosY() + geButton_play.getSizeH() )
        {
            if( !onbutton_play )
            {
                onbutton_play = true;

                geButton_play    .setTex( txButton_play_over );
                geButton_settings.setTex( txButton_settings );
                geButton_quit    .setTex( txButton_quit );

                GAME_SOUND.playEffect( 0 );
            }

            onbutton_settings = false;
            onbutton_quit     = false;

        }
        else
        //SETTINGS
        if( mouse_x > geButton_settings.getPosX() && mouse_x < geButton_settings.getPosX() + geButton_settings.getSizeW() &&
            mouse_y > geButton_settings.getPosY() && mouse_y < geButton_settings.getPosY() + geButton_settings.getSizeH() )
        {
            if( !onbutton_settings )
            {
                onbutton_settings = true;

                geButton_play    .setTex( txButton_play );
                geButton_settings.setTex( txButton_settings_over );
                geButton_quit    .setTex( txButton_quit );

                GAME_SOUND.playEffect( 0 );
            }

            onbutton_play = false;
            onbutton_quit = false;

        }
        else
        //QUIT
        if( mouse_x > geButton_quit.getPosX() && mouse_x < geButton_quit.getPosX() + geButton_quit.getSizeW() &&
            mouse_y > geButton_quit.getPosY() && mouse_y < geButton_quit.getPosY() + geButton_quit.getSizeH() )
        {

            if( !onbutton_quit )
            {
                onbutton_quit = true;

                geButton_play    .setTex( txButton_play );
                geButton_settings.setTex( txButton_settings );
                geButton_quit    .setTex( txButton_quit_over );

                GAME_SOUND.playEffect( 0 );
            }

            onbutton_play     = false;
            onbutton_settings = false;

        }
        else
        {
            geButton_play    .setTex( txButton_play );
            geButton_settings.setTex( txButton_settings );
            geButton_quit    .setTex( txButton_quit );

            onbutton_play     = false;
            onbutton_settings = false;
            onbutton_quit     = false;
        }

    }
}
///LOGICS

GAME_MAP.handleLogics();

if( switchTo_settings ){
#define timePassed SDL_GetTicks() - timeSwitch
#define timeSwitchTotal 500

//Set Alpha & position
if( SDL_GetTicks() - timeFade > 15 )
{
    //ALPHA
    iTexAlpha -= 25;
    if( iTexAlpha < 0 ) iTexAlpha = 0;

    iMoveTimes ++;

    SDL_SetTextureAlphaMod( txButton_play     , iTexAlpha );
    SDL_SetTextureAlphaMod( txButton_settings , iTexAlpha );
    SDL_SetTextureAlphaMod( txButton_quit     , iTexAlpha );

    //POSITION
    geButton_play.setPosition    ( -iMoveTimes*15 + SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2-50 );
    geButton_settings.setPosition( -iMoveTimes*15 + SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2+50 );
    geButton_quit.setPosition    ( -iMoveTimes*15 + SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2+150 );

    timeFade = SDL_GetTicks();
}

if( timePassed > timeSwitchTotal )
{
    ///SWITCHING
    RUNMENU_SETTINGS();
    switchTo_settings = false;
    switchTo_main     = true;

    ///RESTORATION
    timeSwitch = SDL_GetTicks();
    iTexAlpha  = 0;
    iMoveTimes = 0;

    geButton_play.setPosition    ( -200 + SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2-50 );
    geButton_settings.setPosition( -200 + SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2+50 );
    geButton_quit.setPosition    ( -200 + SCREEN_WIDTH/2 - geButton_play.getSizeW()/2, SCREEN_HEIGHT/2+150 );

}
}
else
if( switchTo_main ){

    #define timePassed SDL_GetTicks() - timeSwitch
    #define timeSwitchTotal 500

//Set Alpha & position
if( SDL_GetTicks() - timeFade > 15 )
{
    bool done = false;
    //ALPHA
    if( iTexAlpha < 255 )
    {
        iTexAlpha += 15;
        if( iTexAlpha > 255 ) iTexAlpha = 255;

        SDL_SetTextureAlphaMod( txButton_play     , iTexAlpha );
        SDL_SetTextureAlphaMod( txButton_settings , iTexAlpha );
        SDL_SetTextureAlphaMod( txButton_quit     , iTexAlpha );

        timeFade = SDL_GetTicks();
    }
    else
    {
        done = true;
        showtitle = true;
    }

    //POSITION
    if( geButton_play.getPosX() < SCREEN_WIDTH/2 - geButton_play.getSizeW()/2 )
    {
        int iAux = 13;

        if( geButton_play.getPosX() + iAux > SCREEN_WIDTH/2 - geButton_play.getSizeW()/2 )
        iAux = SCREEN_WIDTH/2 - geButton_play.getSizeW()/2 - geButton_play.getPosX();

        //Set Pos
        geButton_play.setPosition    ( geButton_play    .getPosX() + iAux );
        geButton_settings.setPosition( geButton_settings.getPosX() + iAux );
        geButton_quit.setPosition    ( geButton_quit    .getPosX() + iAux );
    }
    else
    if( done ) switchTo_main = false;


    timeFade = SDL_GetTicks();
}

}

///RENDER

GAME_MAP.draw();
if( showtitle )
geTitle.draw();
geButton_play.draw();
geButton_quit.draw();
geButton_settings.draw();
GAME_INTERFACE.draw_cursor();

SDL_RenderPresent( RENDER_MAIN );

}

}


