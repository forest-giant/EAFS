#ifndef EFFECTS_H_INCLUDED
#define EFFECTS_H_INCLUDED

#include "Basics.h"
#include "headers.h"

const int ANIM_CODED  = 0;
const int ANIM_SPRITE = 1;

struct Effect{
int x,y,w,type,frame,frameend,nr;
bool display;
Uint32 timeFrame,timeMove;
Effect *next,*prev;
SDL_Texture *tex;
};

struct EFFECT_STAR{
int x,y;
Uint32 timeSpawn;
EFFECT_STAR *next;
};

class EFFECTS{
private:
Effect *FirstEffect_cod,*LastEffect_cod;
EFFECT_STAR *FirstStar, *LastStar;
SDL_Texture *texEFFECTS[10];
Uint32 timeSpawnStars,timeMoveStars;

public:
void init(void);
void addAnim( int x,int y,int nr );
void handleAndDrawStars(void);
void draw(void);
};

extern EFFECTS GAME_EFFECTS;


#define EFFECT_SPREAD(direction) 10 + direction

#endif // EFFECTS_H_INCLUDED
