#include "settings.h"
#include "Basics.h"
#include "SDL2/SDL_mixer.h"

void SETTINGS::loadFromFile(){
std::string ssaux;
std::ifstream in( "settings.txt" );

in>>ssaux>>_resolution_x>>_resolution_y;
in>>ssaux>>_fullscr;
in>>ssaux>>_vsync;
in>>ssaux>>_FPScap;
in>>ssaux>>_volume;
in>>ssaux>>_sMapFile;
in>>ssaux>>_timeStartStageAt;

in.close();

SCREEN_WIDTH  = _resolution_x;
SCREEN_HEIGHT = _resolution_y;
}
int SETTINGS::getRes_x(){
return _resolution_x;
}
int SETTINGS::getRes_y(){
return _resolution_y;
}
std::string SETTINGS::getCMap(){
return _sMapFile;
}
int SETTINGS::getVolume(void){
return _volume;
}
bool SETTINGS::getFullScr(){
return _fullscr;
}
unsigned long SETTINGS::getTimeStart(){


return _timeStartStageAt;
}
void SETTINGS::setVsync(bool x){
_vsync = x;
}
bool SETTINGS::getVsync(void){
return _vsync;
}
void SETTINGS::setFPScap(int x){
_FPScap = x;
}
int  SETTINGS::getFPScap(void){
return _FPScap;
}
void SETTINGS::saveToFile(void){

std::ofstream out( "settings.txt" );

out<<"resolution: "<<_resolution_x<<' '<<_resolution_y<<'\n';
out<<"fullscr: "<<_fullscr<<'\n';
out<<"vsync: "<<_vsync<<'\n';
out<<"framecap: "<< _FPScap<<'\n';
out<<"volume: "  << _volume<<'\n';
out<<"cmap: "<< _sMapFile<<'\n';
out<<"timeStart: "<< _timeStartStageAt<<'\n';

out.close();

}


