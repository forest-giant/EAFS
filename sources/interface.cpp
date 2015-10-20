#include "interface.h"


void Interface::init(){
SDL_Surface *surfAux = NULL;

texCursor = LoadTex( "Data//Textures//Interface//cursor.png" );

texBotbar = LoadTex( "Data//Textures//Interface//stats-bar.png" );
texLivesLeft = NULL;

std::stringstream ssaux;
ssaux<<PLAYER.getLivesLeft();

surfAux = TTF_RenderText_Blended( Font_Amble_30,ssaux.str().c_str() ,WHITE );
if( surfAux != NULL )
{
    texLivesLeft = SDL_CreateTextureFromSurface( RENDER_MAIN, surfAux );
    SDL_FreeSurface( surfAux );
    surfAux = NULL;
}
else
{
    cons_out("Interface fail: lifes");
}

ssaux.str( "" );
ssaux<<PLAYER.getScore();
surfAux = TTF_RenderText_Blended( Font_Amble_30,ssaux.str().c_str() ,WHITE );
if( surfAux != NULL )
{
    texScore = SDL_CreateTextureFromSurface( RENDER_MAIN, surfAux );
    SDL_FreeSurface( surfAux );
    surfAux = NULL;
}
else
{
    cons_out("Interface fail: score");
}

_oldlives = PLAYER.getLivesLeft();
_oldscore = PLAYER.getScore();

}
void Interface::switchCursor(short nr){
iCursor = nr;

SDL_ShowCursor( (iCursor==CURSOR_DEFAULT)?true:false );
}
void Interface::draw_cursor(void){
int x,y;
if( iCursor != CURSOR_DEFAULT && iCursor != CURSOR_NONE )
{
    SDL_GetMouseState( &x,&y );
    ApplyTex( x-10,y-10,texCursor );
}

}
void Interface::draw(){
int iScoreTexW  = 0;
#define pch PLAYER.getCHealth()
#define pmh PLAYER.getMaxHealth()

//Bot Bar
ApplyTex( 0 ,SCREEN_HEIGHT - 100,texBotbar,NULL );//,SCREEN_WIDTH/2,40
//LIFES LEFT
ApplyTex( 80,SCREEN_HEIGHT - 77, texLivesLeft );
//SCORE
SDL_QueryTexture( texScore, NULL,NULL,&iScoreTexW,0 );
ApplyTex( 220 - iScoreTexW,SCREEN_HEIGHT - 37, texScore );

/*
//Health
SDL_Rect rHealth;
rHealth.y = SCREEN_HEIGHT - 75;
rHealth.w = 10 + 10/pmh;
rHealth.h = 30;

SDL_SetRenderDrawColor( RENDER_MAIN,30,30,240,255 );


for( int i = 0; i < pch ;i++ )// 1   (6+1)*((double)pch/pmh)
{
    rHealth.x = 5 + i*13 +10/pmh ;
    SDL_RenderFillRect( RENDER_MAIN,&rHealth );
}
*/
}
void Interface::handleLogics(){
SDL_Surface *surfaux = NULL;
std::stringstream ssaux;
if( PLAYER.getScore() != _oldscore )
{
    //Update Score
    ssaux<<PLAYER.getScore();
    //New surf
    surfaux = TTF_RenderText_Blended( Font_Amble_30,ssaux.str().c_str(),WHITE );
    //If worked
    if( surfaux != NULL )
    {
        //Destroy old
        if( texScore != NULL ) SDL_DestroyTexture( texScore );
        //Make New
        texScore = SDL_CreateTextureFromSurface( RENDER_MAIN, surfaux );

        _oldscore = PLAYER.getScore();
    }
}

if( PLAYER.getLivesLeft() != _oldlives )
{
     //Update Score
    ssaux.str("");
    ssaux<<PLAYER.getLivesLeft();
    //New surf
    if( surfaux != NULL ) SDL_FreeSurface( surfaux );
    surfaux = TTF_RenderText_Blended( Font_Amble_30,ssaux.str().c_str(),WHITE );
    //If worked
    if( surfaux != NULL )
    {
        //Destroy old
        if( texScore != NULL ) SDL_DestroyTexture( texLivesLeft );
        //Make New
        texLivesLeft = SDL_CreateTextureFromSurface( RENDER_MAIN, surfaux );

        _oldlives = PLAYER.getLivesLeft();
    }
}

}
void Interface::cleanup(){
}
