#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "headers.h"
#include "enemy.h"
#include <fstream>



class MAP{
private:
int iMapWidth,iBgtexw,iMapSliceNr,iBgx,
     cenemy_x,cenemy_y,cenemy_prefab,cenemy_behavior,
     iTranslate,iTranslate_x;
float iBgy,iBg2y;
SDL_Texture *txBg,*txBg2,*txMC1;
SDL_Rect rAuxBg;
Uint32 timeBG,timeEnemySpawn,cenemy_time,timeTrans,timeIgnoreTill;
std::ifstream fileMap;
bool ignoreSpawn,SpawningEnemies,_complete;

public:
void init(void);
int  getWidth();
void setBG(int player_x,int player_y = 0);
void AddChunk(int nr,int x,int y);
void connect(int iMapNr);
void startSpawnEnemies(void);
void handleEnemySpawn(void);
void handleLogics(void);
void draw(void);
bool getComplete(void);
void translate( int direct );
};

extern MAP GAME_MAP;

#endif // MAP_H_INCLUDED
