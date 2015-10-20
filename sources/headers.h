#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <fstream>
#include <sstream>


struct KeyBindings{
unsigned int
UP   ,
DOWN ,
LEFT ,
RIGHT,
ATTACK;
};
struct MapChunk{
SDL_Rect Body;
SDL_Texture *tex;
MapChunk *next;
};
struct MapSlice{
MapChunk *FirstMapChunk,*LastMapChunk;
int x,maxw;
bool draw;
};

///CONSTANTS
const int MapSliceSize = 400;
const unsigned char UP    = 0;
const unsigned char DOWN  = 1;
const unsigned char RIGHT = 2;
const unsigned char LEFT  = 3;
const unsigned char FACTION_PLAYER = 1;
const unsigned char FACTION_ENEMY = 0;


extern SDL_Window* WINDOW_MAIN;   ///----MAIN WINDOW----
extern SDL_Renderer* RENDER_MAIN; ///----MAIN RENDERER----

///VARIABLES
extern MapSlice *MapSlices;
extern Uint32 WINDOW_MAIN_ID;

bool Init(void);
void RUN_GAME(void);

///FONTS
extern TTF_Font* Font_Amble_16;
extern TTF_Font* Font_Amble_20;
extern TTF_Font* Font_Amble_24;
extern TTF_Font* Font_Amble_30;

///COLORS
extern SDL_Color ConsTextColor,ConsBgColor,WHITE,RED,YELLOW,BLACK;

#endif // HEADERS_H_INCLUDED
