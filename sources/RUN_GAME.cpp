#include "headers.h"
#include "Map.h"
#include "Player.h"
#include "Console.h"
#include "bullets.h"
#include "enemy.h"
#include "interface.h"
#include "Basics.h"
#include "sound.h"
#include "effects.h"
#include "settings.h"

int FPScap;

void RUN_GAME(){
bool RUN = true,GAME_OVER = false,showEndTitle = false,
     complete = false;
SDL_Event event;
Uint32 timeFPScap,timeFPScount = SDL_GetTicks(),timeComplete;
int iFPScount = 0,iFPSframecount = 0;
long long int iFPSallcount = 0;
std::ofstream file_fpsout;
Uint32 timeShowTitle,timeEndGame;
GAME_Text txtGameOver,txtComplete;

///INIT
//Misc
txtGameOver.setText( "GAME OVER" );
txtGameOver.setFont( Font_Amble_30 );
txtGameOver.setColor( &WHITE );
txtGameOver.update();
txtGameOver.setPosX( 430 );
txtGameOver.setPosY( 300 );

txtComplete.setText( "LEVEL COMPLETE" );
txtComplete.setFont( Font_Amble_30 );
txtComplete.setColor( &WHITE );
txtComplete.update();
txtComplete.setPosX( 390 );
txtComplete.setPosY( 300 );

//CURRENT MAP

if( GAME_SETTINGS.getVsync() )
FPScap = 99999;
else
FPScap = GAME_SETTINGS.getFPScap();


GAME_Enemies.reset_list();
GAME_MAP.connect( 1 ); //! parametrul 1 nu are efect !!!
GAME_MAP.startSpawnEnemies();

PLAYER.resetPos();
PLAYER.resetScore();
PLAYER.resetLives();

GAME_BULLETS.cleanup();

GAME_INTERFACE.switchCursor( CURSOR_NONE );

GAME_SOUND.playMusic( 2 );

while( RUN )
{
    //start FPS count
    timeFPScap = SDL_GetTicks();

    ///EVENTS
    while( SDL_PollEvent( &event ) )
    {
        Cons_giveEvent( &event );

        if( event.type == SDL_QUIT ) RUN = false;
        else
        if( event.type == SDL_MOUSEBUTTONDOWN )
        {
            if( event.button.button == SDL_BUTTON_LEFT )
            PLAYER.StartShootingSequence();
        }
        else
        if( event.type == SDL_KEYDOWN )
        {
            if( event.key.keysym.sym == SDLK_ESCAPE ) RUN = false;
            else
            if( event.key.keysym.sym == SDLK_BACKQUOTE )
            {
                //TOGGLE CONSOLE WINDOW
            }
        }

    }

    ///LOGICS
    if( !GAME_OVER && PLAYER.getLivesLeft() == 0 )
    {
        GAME_OVER = true;
        timeEndGame = timeShowTitle = SDL_GetTicks();
    }
    else
    if( GAME_OVER )
    {
        //Game Over Title
        if( !showEndTitle && timeShowTitle + 1500 < SDL_GetTicks() )
        {
            showEndTitle = true;
        }

        //Close Session
        if( timeEndGame + 5000 < SDL_GetTicks() )
            RUN = false;
    }

    if( !complete && !GAME_OVER )
    {
        complete = GAME_MAP.getComplete();
        if( complete )
        timeComplete = SDL_GetTicks();
    }
    else if( complete )
    {
        if( SDL_GetTicks() - timeComplete >= 4000  )
        RUN = false;
    }

    PLAYER.handleKeys();
    //PLAYER.handleMouse();
    PLAYER.handleMisc();
    GAME_MAP.handleLogics();
    GAME_MAP.handleEnemySpawn();
    GAME_BULLETS.handle();
    GAME_Enemies.behave();
    GAME_INTERFACE.handleLogics();




    ///RENDER
    SDL_SetRenderDrawColor( RENDER_MAIN,255,255,255,255 );
    SDL_RenderClear( RENDER_MAIN );

    GAME_MAP    .draw();
    GAME_EFFECTS.handleAndDrawStars();
    GAME_Enemies.draw();
    PLAYER      .draw();
    GAME_BULLETS.draw();
    GAME_EFFECTS.draw();


    GAME_INTERFACE.draw();
    GAME_INTERFACE.draw_cursor();



    if( showEndTitle )
    txtGameOver.draw();
    else
    if( complete )
    txtComplete.draw();

    SDL_RenderPresent( RENDER_MAIN );

    //FPS cap
    if( SDL_GetTicks() - timeFPScap < (float)1000/FPScap )
    SDL_Delay( (float)1000/FPScap - ( SDL_GetTicks() - timeFPScap ) );

    //FPS count
    iFPScount ++;
    if( SDL_GetTicks() - timeFPScount >= 1000 )
    {
        //cons_out(iFPScount);
        std::stringstream ssaux;
        ssaux<<"E.A.F.S FPS:"<<iFPScount;
        SDL_SetWindowTitle( WINDOW_MAIN, ssaux.str().c_str() );
        iFPSframecount++;
        iFPSallcount += iFPScount;

        //File Out
        file_fpsout.open( "Benchmark.txt" );

        file_fpsout<<"Resolution: "<<SCREEN_WIDTH<<'x'<<SCREEN_HEIGHT<<'\n';
        file_fpsout<<"Average FPS: "<<iFPSallcount/iFPSframecount<<'\n';

        file_fpsout.close();


        timeFPScount = SDL_GetTicks();
        iFPScount = 0;

        //GAME_EFFECTS.addAnim( 200,200,1 );
    }


}

}
