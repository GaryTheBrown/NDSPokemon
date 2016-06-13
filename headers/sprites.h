#ifndef __sprites_h
#define __sprites_h
#include "pokemon.h"

//*********************************************************************************
// functions
//*********************************************************************************
extern void initspritesystem();
extern void updateplayerspritepriority();
extern void updatecharspritepriority(unsigned char n);
extern void updatesprite(aSprite *sprite);
extern void updatespritepriority(aSprite *sprite,unsigned char priority = 2);
extern void initplayersprite();
extern void clearcharsprite();
extern void initcharsprite();
extern void checkcharvisible();
extern void charspriteplace(aSprite *sprite);
extern void charspritechange(aSprite *sprite , char playerspriteno);

//*********************************************************************************
// DATA
//*********************************************************************************

//******
// Tiles 
//******
extern const unsigned char playerTiles[];
extern const unsigned char OAKTiles[];

//********
//Palettes
//********
extern const unsigned short playerPal[];
extern const unsigned short OAKPal[];



#endif