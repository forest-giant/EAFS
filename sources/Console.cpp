#include "Console.h"
#include "Basics.h"
#include "headers.h"
#include "Player.h"
#include "cstdlib"

SDL_Window   *WINDOW_CONSOLE   = NULL;
SDL_Renderer *RENDER_CONSOLE   = NULL;

unsigned int Cons_ID = -1,Cons_nrItem;
bool Cons_Focused = false;
char ConsText[200];
SDL_Texture *Cons_inText;

Cons_Line *FirstLine,*LastLine;

bool Cons_init(){
WINDOW_CONSOLE = SDL_CreateWindow( "Console",50,SCREEN_HEIGHT - 250,300,250,SDL_WINDOW_SHOWN );//
if( WINDOW_CONSOLE == NULL ) return false;

RENDER_CONSOLE = SDL_CreateRenderer( WINDOW_CONSOLE,-1 ,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
if( RENDER_CONSOLE == NULL ) return false;

Cons_ID = SDL_GetWindowID( WINDOW_CONSOLE );

ConsText[0] = '\0';

Cons_nrItem = 0;

FirstLine = new Cons_Line;
LastLine  = new Cons_Line;
FirstLine->next = LastLine;
FirstLine->prev = NULL;
LastLine ->next = NULL;
LastLine ->prev = FirstLine;

return true;
}
void cons_out(std::string sNewText,SDL_Color color){
Cons_Line* newline = new Cons_Line;
SDL_Surface *tempsurf = NULL;

newline->next = FirstLine->next;
newline->prev = FirstLine;
FirstLine->next->prev = newline;
FirstLine->next = newline;


tempsurf = TTF_RenderText_Blended( Font_Amble_16,sNewText.c_str(),color );
newline->tex = SDL_CreateTextureFromSurface( RENDER_CONSOLE,
                                             tempsurf );
SDL_FreeSurface( tempsurf );
Cons_nrItem ++;
while( Cons_nrItem > 50 )
{
    Cons_nrItem--;
    Cons_Line* delaux = LastLine->prev;
    LastLine->prev->prev->next = LastLine;
    LastLine->prev = LastLine->prev->prev;

    SDL_DestroyTexture( delaux->tex );
    delete delaux;
}

Cons_update_text();
}
void cons_out(int iNewText,SDL_Color color){
std::string saux;
Cons_Line* newline = new Cons_Line;
SDL_Surface *tempsurf = NULL;

GAME_itos( iNewText,saux );

newline->next = FirstLine->next;
newline->prev = FirstLine;
FirstLine->next->prev = newline;
FirstLine->next = newline;

tempsurf = TTF_RenderText_Blended( Font_Amble_16,saux.c_str(),color );
newline->tex = SDL_CreateTextureFromSurface( RENDER_CONSOLE,
                                             tempsurf );
SDL_FreeSurface( tempsurf );

Cons_nrItem ++;
while( Cons_nrItem > 50 )
{
    Cons_nrItem--;
    Cons_Line* delaux = LastLine->prev;
    LastLine->prev->prev->next = LastLine;
    LastLine->prev = LastLine->prev->prev;

    SDL_DestroyTexture( delaux->tex );
    delete delaux;
}

Cons_update_text();
}
void cons_clear(void){
Cons_Line *delaux;
while( FirstLine->next != LastLine )
{
    delaux = FirstLine->next;
    FirstLine->next = FirstLine->next->next;
    SDL_DestroyTexture( delaux->tex );
    delete delaux;
}

LastLine->prev = FirstLine;

}
void Cons_update_text(){
SDL_Rect rText,rTextZone;
int i;
Cons_Line *icl;

rTextZone.x = 0;
rTextZone.y = 0;
rTextZone.w = 300;
rTextZone.h = 236;

rText.x = 0;


SDL_SetRenderDrawColor( RENDER_CONSOLE,ConsBgColor.r ,ConsBgColor.g,ConsBgColor.b,255 );
SDL_RenderFillRect( RENDER_CONSOLE, &rTextZone );


for( icl = FirstLine->next,i = 2;icl->next != NULL && i < 20; icl = icl->next,i++ )
{
    rText.y = 250 - 16*i;
    SDL_QueryTexture( icl->tex,0,0,&rText.w,&rText.h );
    SDL_RenderCopy( RENDER_CONSOLE,icl->tex,NULL,&rText );
}


SDL_RenderPresent( RENDER_CONSOLE );
}
void Cons_update_command(){
SDL_Surface *suAux = NULL;
SDL_Rect rText,rTextZone;

rTextZone.x = 0;
rTextZone.w = 300;
rTextZone.y = 236;
rTextZone.h = 40;

rText.x = 0;

suAux = TTF_RenderText_Blended( Font_Amble_16,ConsText,ConsTextColor );
Cons_inText = SDL_CreateTextureFromSurface( RENDER_CONSOLE,suAux );

if( suAux != NULL ){
rText.y = 250 - 18;
rText.w = suAux->w;
rText.h = suAux->h;
}


SDL_SetRenderDrawColor( RENDER_CONSOLE,ConsBgColor.r ,ConsBgColor.g,ConsBgColor.b,255 );
SDL_RenderFillRect( RENDER_CONSOLE, &rTextZone );

//Draw IN text
SDL_RenderCopy( RENDER_CONSOLE,Cons_inText,NULL,&rText );

SDL_RenderPresent( RENDER_CONSOLE );


//Cleanup
SDL_FreeSurface( suAux );
SDL_DestroyTexture( Cons_inText );
}


///COMMANDS
void Cons_giveEvent( SDL_Event *event ){

if( event->type == SDL_MOUSEBUTTONDOWN && event->button.windowID == Cons_ID )
{
    Cons_Focused = true;
    SDL_SetWindowTitle( WINDOW_CONSOLE,"Console" );
}
else
if( event->type == SDL_MOUSEBUTTONDOWN && event->button.windowID == WINDOW_MAIN_ID )
{
    Cons_Focused = false;
    SDL_SetWindowTitle( WINDOW_CONSOLE,"Console(X)" );
}



    bool UpdateCons = false;
    if( Cons_Focused == true )
    {
        SDL_StartTextInput();
    }
    else
    if( Cons_Focused == false )
    {
        SDL_StopTextInput();
    }

    if( event->type == SDL_KEYDOWN  )
    {
        ///HANDLE COMMANDS
        if( event->key.keysym.sym == SDLK_RETURN )
        {
            #define SET_UNKNOWN GAME_strcat( ConsText," (X)" );
            #define text(x) CTStr[x]

            std::string CTStr[10];
            int cstr = 0;

            for( unsigned int i = 0; i < SDL_strlen( ConsText );i++ )
            if( ConsText[i] == ' ' ) cstr++;
            else
            CTStr[cstr] += ConsText[i];

            ///Switch Command
            //if( text(0) == "exit" ) cons_out( "Not Exiting!" );
            //else
            if( text(0) == "set" )
            {
                if( text(1) == "ll" )
                {
                    //Lifes Left
                    //PLAYER.setCHealth( atoi(text(2).c_str()) );
                }
            }
            else
            if( text(0) == "clear" )
            {
                cons_clear();
                ConsText[0] = '\0';
            }
            else
            if( text(0) == "invi" )
            {
                PLAYER.setInvi_forced( atoi( text(1).c_str() ) );
            }
            else
            SET_UNKNOWN;

            cons_out( ConsText );
            ConsText[0] = '\0';
            UpdateCons = true;

            Cons_update_text();
        }
        else
        if( event->key.keysym.sym == SDLK_BACKSPACE )
        {
            ConsText[ SDL_strlen( ConsText ) -1 ] = '\0';
            UpdateCons = true;
        }
    }

    if( Cons_Focused )
    {
        if( event->type == SDL_TEXTINPUT )
        {
            GAME_strcat(ConsText,event->text.text );
            UpdateCons = true;
        }
    }


    if( UpdateCons ) Cons_update_command() ;



}

