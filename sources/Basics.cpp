#include "Basics.h"
#include <fstream>
#include <sstream>
#include "Console.h"
#include "headers.h"

SDL_Window*   WINDOW_MAIN = NULL;
SDL_Renderer* RENDER_MAIN = NULL;

//clsDebug GAME_DEBUG;

std::ofstream DEBUG_FileLoadFails;

int camera_x,camera_y;

///GAME ENTITY
GAME_Entity::GAME_Entity(void){
_x = _y = _w = _h = 0;
_cliped = false;
_clip.x = _clip.y = _clip.w = _clip.h = 0;
_tex = NULL;
}
GAME_Entity::GAME_Entity( std::string src ){
_x = _y = _w = _h = 0;
_cliped = false;
_clip.x = _clip.y = _clip.w = _clip.h = 0;
_tex = NULL;

_tex = LoadTex( src );
SDL_QueryTexture( _tex,0,0,&_w,&_h );
}
void GAME_Entity::setClip(bool cliped){
_cliped  = cliped;
}
void GAME_Entity::setClip(SDL_Rect* clip){
_cliped = true;
_clip = *clip;
}
void GAME_Entity::setTex( std::string src  ){
if( _tex != NULL ) SDL_DestroyTexture( _tex ),_tex = NULL;
_tex = LoadTex( src );

SDL_QueryTexture( _tex,0,0,&_w,&_h );
}
void GAME_Entity::setTex( SDL_Texture *tex ){
_tex = tex;

SDL_QueryTexture( _tex,0,0,&_w,&_h );
}
void GAME_Entity::setSize(int w,int h){
_cliped = false;
_w = w;
_h = h;
}
void GAME_Entity::setPosition(int x,int y){
_x = x;
if( y != NO_CHANGE )
_y = y;
}
int  GAME_Entity::getSizeW(void){
return _w;
}
int  GAME_Entity::getSizeH(void){
return _h;
}
int  GAME_Entity::getPosX(void){
return _x;
}
int  GAME_Entity::getPosY(void){
return _y;
}
void GAME_Entity::draw(void){
if(_cliped)
ApplyTex( _x,_y,_tex,&_clip );
else
ApplyTex( _x,_y,_tex,NULL,_w,_h );
}
SDL_Texture *GAME_Entity::getTex(void){
return _tex;
}

///GAME TEXT
GAME_Text::GAME_Text( std::string sText ){
_x = _y = _w = _h = 0;
_rendered = false;
_surf = NULL;
_tex = NULL;
_font = Font_Amble_20;
_color = &BLACK;
_sText = sText;
if( _sText != "" )
{
    update();
}

}
void GAME_Text::draw(){
if( _tex != NULL )
ApplyTex( _x,_y,_tex );
}
void GAME_Text::setPosX(int x){
_x = x;
}
void GAME_Text::setPosY(int y){
_y = y;
}
void GAME_Text::setText(std::string sText1,std::string sText2,std::string sText3,std::string sText4,std::string sText5){
_sText = "";
_sText += sText1;
if( sText2 != "" ) _sText += sText2;
if( sText3 != "" ) _sText += sText3;
if( sText4 != "" ) _sText += sText4;
if( sText5 != "" ) _sText += sText5;
GAME_Text::update();
}
void GAME_Text::setFont( TTF_Font *font ){
_font = font;
}
void GAME_Text::setColor( SDL_Color *color ){
_color = color;
}
void GAME_Text::update(){
if( _surf != NULL ) SDL_FreeSurface( _surf );
_surf = TTF_RenderText_Blended( _font,_sText.c_str(),*_color );

if( _surf != NULL )
{
    _tex = SDL_CreateTextureFromSurface( RENDER_MAIN, _surf );
    SDL_FreeSurface( _surf );
    _surf = NULL;
    _rendered = true;
}
else
{
    cons_out( "Game_text(update):Render Fail!",RED );
}

}



SDL_Surface *LoadSurf(std::string file){
SDL_Surface *loadedimg = NULL;

loadedimg = IMG_Load( file.c_str() );

if( loadedimg == NULL )
{
    DEBUG_FileLoadFails.open( "DEBUG//FileLoadFails.txt", std::ios_base::out | std::ios_base::app );
    DEBUG_FileLoadFails<<"load fail: "<<file<<' '<<SDL_GetError()<<'\n';
    DEBUG_FileLoadFails.close();
    cons_out( "FLF:" + file,RED );
}

return loadedimg;
}
SDL_Texture *LoadTex(std::string file){
SDL_Texture *loadedtex = NULL;

loadedtex = IMG_LoadTexture(RENDER_MAIN,file.c_str() );

if( loadedtex == NULL )
{
    DEBUG_FileLoadFails.open( "DEBUG//FileLoadFails.txt", std::ios_base::out | std::ios_base::app );
    DEBUG_FileLoadFails<<"load fail: "<<file<<' '<<SDL_GetError()<<'\n';
    DEBUG_FileLoadFails.close();
    cons_out( "FLF:" + file,RED );
}

return loadedtex;
}
void ApplyTex(int x,int y,SDL_Texture *tex,SDL_Rect *clip,int w,int h ){
SDL_Rect pos;

pos.x = x;
pos.y = y;

    if( clip != NULL )
    {

        pos.w = clip->w;
        pos.h = clip->h;

    }
    else
    SDL_QueryTexture( tex,NULL,NULL,&pos.w,&pos.h );

    if( w != -1 ) pos.w = w;
    if( h != -1 ) pos.h = h;

    //Rescale based on SCREEN_HEIGHT
    //default ScrHrap
    //pos.x *= ScrHRap;
    //pos.y *= ScrHRap;
    //pos.w *= ScrHRap;
    //pos.h *= ScrHRap;

    ///DISSABLED
    //Adjust by camera
    //pos.x -= camera_x;
    //pos.y -= camera_y;

SDL_RenderCopy( RENDER_MAIN,tex,clip,&pos );
}


void GAME_ctos( char carray[], std::string &strnew ){
int i;
strnew.erase();

while( carray[0] == ' ' )
{
    for( i = 1; (unsigned)i < SDL_strlen( carray ); i++ )
    carray[i-1] = carray[i];
    carray[i-1] = '\0';
}

for( int i = 0; carray[i] != '\0'; i++ )
strnew += carray[i];
}
void GAME_itos(int nr,std::string &newstr ){
std::stringstream ssaux;
newstr.erase();
ssaux<<nr;
ssaux>>newstr;
}
void GAME_strcpy( char *dest,const char *sourc ){
int len_sourc,i;
len_sourc = SDL_strlen( sourc );

for( i = 0; i < len_sourc; i++ )
dest[i] = sourc[i];
dest[len_sourc] = '\0';
}
void GAME_strcat( char *dest,const char *sourc ){
int len_dest,len_sourc,i;
len_dest  = SDL_strlen( dest );
len_sourc = SDL_strlen( sourc );

for( i = 0; i < len_sourc; i++ )
dest[i + len_dest ] = sourc[i];
dest[len_sourc + len_dest ] = '\0';
}



