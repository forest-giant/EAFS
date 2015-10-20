#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "headers.h"

#include <string>

struct Cons_Line{
SDL_Texture *tex;
Cons_Line *next,*prev;
};

extern SDL_Window *WINDOW_CONSOLE;
extern SDL_Renderer *RENDER_CONSOLE;
extern unsigned int Cons_ID;

bool Cons_init();
void cons_out(std::string sNewText,SDL_Color color = ConsTextColor);
void cons_out(int iNewText,SDL_Color color = ConsTextColor);
void cons_clear(void);
void Cons_update_command(void);
void Cons_update_text   (void);
void Cons_giveEvent( SDL_Event *event );



#endif // CONSOLE_H_INCLUDED
