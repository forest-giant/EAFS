#ifndef BASICS_H_INCLUDED
#define BASICS_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <fstream>

#define BaseWidthSize  1024//1280
#define BaseHeightSize 768//1024
#define BaseAspRatio_X 5
#define BaseAspRatio_Y 4
#define ScrWRap (float)SCREEN_WIDTH/BaseWidthSize
#define ScrHRap (float)SCREEN_HEIGHT/BaseHeightSize

extern int SCREEN_WIDTH;       /// SCREEN WIDTH
extern int SCREEN_HEIGHT;      /// SCREEN HEIGHT
extern int AS_RATIO_X;         /// ASPECT RATIO X/Y
extern int AS_RATIO_Y;         /// ASPECT RATIO X/Y

extern int camera_x,camera_y;

///CONSTANTS
const int NO_CHANGE = -9879;
const int UPDATED   = true;

class GAME_Entity{
private:
int _x,_y,_w,_h;
bool _cliped;
SDL_Rect _clip;
SDL_Texture *_tex;


public:
GAME_Entity(void);
GAME_Entity( std::string src );
void setClip(bool cliped);
void setClip(SDL_Rect* clip);
void setTex( std::string src );
void setTex( SDL_Texture *tex );
void setSize(int w,int h = NO_CHANGE);
void setPosition(int x,int y = NO_CHANGE);
int  getSizeW(void);
int  getSizeH(void);
int  getPosX(void);
int  getPosY(void);
void draw(void);
SDL_Texture *getTex(void);
};
class GAME_Text{
private:
int _x,_y,_w,_h;
bool _rendered;
SDL_Surface *_surf;
SDL_Texture *_tex;
std::string _sText;
TTF_Font *_font;
SDL_Color *_color;

public:
GAME_Text( std::string sText = "" );
void setText( std::string sText1,std::string sText2 = "",std::string sText3 = "",std::string sText4 = "",std::string sText5 = "" );
void setPosX(int x);
void setPosY(int y);
void setColor( SDL_Color *color );
void setFont( TTF_Font *font );
void update(void);
void draw( void );
};

/*
class clsDebug{
private:
std::ofstream file_out;
public:
clsDebug(void);
void inspectHere(std::string);
void ok(void);
};
extern clsDebug GAME_DEBUG;
*/
SDL_Surface *LoadSurf(std::string file);
SDL_Texture *LoadTex(std::string file );
void        ApplyTex(int x,int y,SDL_Texture *tex,SDL_Rect *clip = NULL,int w = -1,int h = -1 );

void GAME_ctos( char carray[], std::string &strnew );
void GAME_itos(int nr,std::string &newstr );
void GAME_strcpy( char *dest,const char *sourc );
void GAME_strcat( char *dest,const char *sourc );

#endif // BASICS_H_INCLUDED
