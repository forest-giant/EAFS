#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "headers.h"

class PLAYERcls{
private:
SDL_Texture *txSkin,*txShield,*txExplo;
SDL_Rect Body,rCenter,rRender_body,rRender_flame[6],rExplo[8];
KeyBindings Keybind;
int velx,vely,iLivesLeft,iBulletsShootLeft,iCFlame,omx,omy,iTurnType,iAccelType,iExploFrame,
    iExplo_x,iExplo_y,iExplo_velx,iExplo_vely;
long long iScore;
Uint32 timeBulletCD,timeMove,timeCheckMouse,timeSwitchFlame,timeTurn,timeRespawn,timeInvi,
       timeExplo,timeExplo_move;
bool _exploding,_respawning,_invi,_invi_forced,bFlame;

public:
void        init(void);
KeyBindings getKeybind(void);
void        draw(void);
SDL_Rect*   getBody(void);
SDL_Rect*   getCenter(void);
bool        getInvi(void);
void        setXY( int x,int y );
void        resetPos(void);
void        resetLives(void);
void        handleKeys(void);
void        handleMouse(void);
void        handleMisc(void);
void        StartShootingSequence(void);
int         getLivesLeft(void);
void        setInvi_forced(bool x);
void        addScore(int score);
int         getScore(void);
void        resetScore(void);

void        damage(void);
};

extern PLAYERcls PLAYER;

#endif // PLAYER_H_INCLUDED
