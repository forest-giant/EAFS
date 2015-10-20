#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <fstream>

class SETTINGS{
private:
int _resolution_x,_resolution_y,_volume;
bool _fullscr,_vsync;
std::string _sMapFile;
long _timeStartStageAt;
int _FPScap;

public:
void loadFromFile( void );
int  getRes_x(void);
int  getRes_y(void);
bool getFullScr(void);
unsigned long getTimeStart(void);
std::string getCMap(void);
void setVsync(bool x);
bool getVsync(void);
int getVolume(void);
void setFPScap(int x);
int  getFPScap(void);
void saveToFile(void);
};

extern SETTINGS GAME_SETTINGS;

#endif // SETTINGS_H_INCLUDED
