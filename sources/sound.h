#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "SDL2/SDL_mixer.h"

class SOUND{
private:
Mix_Music *musMusic[10];
Mix_Chunk *chEffects[10];
Uint32 iMusicChannel;

public:
void init(void);
void playMusic(int nr);
void pauseMusic(void);
void switchToMusic(int nr);
void playTEST(void);
void handleTEST(void);
void playEffect(int effect);
};

extern SOUND GAME_SOUND;

#endif // SOUND_H_INCLUDED
