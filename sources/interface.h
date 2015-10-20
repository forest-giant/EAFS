#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include "headers.h"
#include "Basics.h"
#include "Player.h"
#include "Console.h"

const int CURSOR_NONE    = -1;
const int CURSOR_DEFAULT =  0;
const int CURSOR_CROSS   =  1;

class Interface{
private:
SDL_Texture *texBotbar,*texLivesLeft,*texScore,*texCursor;
short iCursor;// 0 = default, 1 = cross-gameplay

int _oldscore,_oldlives;

public:
void init();
void draw();
void switchCursor(short nr);
void draw_cursor(void);
void handleLogics();
void cleanup();
};

extern Interface GAME_INTERFACE;

#endif // INTERFACE_H_INCLUDED
