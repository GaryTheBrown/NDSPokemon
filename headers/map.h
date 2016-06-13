#ifndef __map_h
#define __map_h
#include "pokemon.h"

//*********************************************************************************
// functions
//*********************************************************************************
extern void start_map(signed int map_x, signed int map_y, unsigned char direction);
extern void changed_map(std::string oldmapname);
extern void change_map();
extern void partialmapupdate();
extern void bordertile(unsigned char mapid, int ix, int iy, int signed map_tile_x , int signed map_tile_y);
extern void maintile(unsigned char mapid, int corner_x, int corner_y, int map_x, int map_y);
extern void place_tile(int ix, int iy, signed int map_x , signed int map_y);
extern void updatebg();
extern void setupmapscreen();
extern short int getmapdata(unsigned char mapid, int ix,int iy);
extern short int getmapcol(unsigned char mapid, int ix,int iy);
extern short int getmapspec(unsigned char mapid, int ix,int iy);
extern short int getmaptextboxextradata(unsigned char mapid,int id);
extern short int getmapwarpextradata(unsigned char mapid,int id);
extern int bordertouse;
extern int borderx;
extern int bordery;
#endif