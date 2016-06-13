#ifndef __globals_h
#define __globals_h

//*********************************************************************************
// TYPEDEFS for all data
//*********************************************************************************
struct aMap;
struct aWarpdata;
struct aTextboxdata;

//sprite data
typedef struct aSpritedata
{
	unsigned char id;
	signed int map_x;
	signed int map_y;
	unsigned char direction;
	bool visible;// incase special sprite that will only show with certain rules (use script)
	unsigned char spritescript;//(0 = none)
	unsigned char spritetext;
	unsigned char *spritetiles;
	unsigned short *spritepal;
} aSpritedata;


//map data
typedef struct aMap
{
	unsigned short int id;
	std::string name;
	unsigned char width;
	unsigned char height;
	unsigned short int *border;
	unsigned short int *mapdata;
	unsigned char *mapcol;
	unsigned short int *mapspec;
	std::string *textbox;
	aTextboxdata *textboxdata;
	unsigned char Spritedatasize;
	aSpritedata *Spritedata;
	unsigned char *Spritescriptstart;
	unsigned char *Spritescript;
	aWarpdata *warpdata;
	aMap *connection_north_name;
	signed char connection_north_offset;
	aMap *connection_south_name;
	signed char connection_south_offset;
	aMap *connection_west_name;
	signed char connection_west_offset;
	aMap *connection_east_name;
	signed char connection_east_offset;
} aMap;
	
//textbox data
typedef struct aTextboxdata
{
	unsigned short int tile;
	char type;
	char lines;
	char offsetx;
	char offsety;
	char linelength;
	char id;

} aTextboxdata;

//warp data
typedef struct aWarpdata
{
	unsigned short int tile;
	bool topbottom;
	unsigned char type;
	aMap *mapto;
	unsigned char mapx;
	unsigned char mapy;		
	
} aWarpdata;

//animation groups
typedef struct aAnimation
{ 
	unsigned char anim_id;
	std::string anim_name;
	unsigned char anim_no_of_frames;
	unsigned char anim_no_of_tiles;
	unsigned char anim_bg_to_use;
	unsigned char anim_tile_to_replace;
	unsigned char anim_fps;

} aAnimation;

//main sprite data
typedef struct aSprite
{
	unsigned char id;
	unsigned int screen_x;
	unsigned int screen_y;
	unsigned char priority;
	short unsigned int *memloc;
	unsigned char *discloc;
	unsigned char paletteno;
	unsigned short *palette;
	unsigned int size;
	SpriteSize size2;
	unsigned char frame;
	bool hidden;

} aSprite;


//*********************************************************************************
// constant variables to use (could be removed and all instances replaced with the value)
//*********************************************************************************

const unsigned char BG0_Tiles_Memory = 3; // setting the areas of memory for the floor tile data
const unsigned char BG1_Tiles_Memory = 8; // setting the areas of memory for the tile data
const unsigned char BG2_Tiles_Memory = 13; // setting the areas of memory for the tile data
const unsigned char BG3_Tiles_Memory = 1; // setting the areas of memory for the textbox tile data

const unsigned char BG0_map_Memory = 1; // setting the areas of memory for the floor map data
const unsigned char BG1_map_Memory = 3; // setting the areas of memory for the bottom map data 
const unsigned char BG2_map_Memory = 5; // setting the areas of memory for the top map data
const unsigned char BG3_map_Memory = 0; // setting the areas of memory for the textbox data

//*********************************************************************************
// Global variables
//*********************************************************************************
extern bool mapfunction, battlefunction, mainmenufunction, pausemenufunction, boolafterwarp; // move between system function
extern bool lock_player, player_script_lock, lock_a, lock_b, lock_x, lock_y, lock_l, lock_r, lock_start, lock_select, textboxdone, textbox_firstpass, changemap;
extern u16 mapbg0[64*32], mapbg1[64*32], mapbg2[64*32], mapbg3[32*32]; //map backgrounds pallettes and tiles
extern int map_player_x, map_player_y; // map player pos
extern int bg0, bg1, bg2, bg3;
extern int unsigned screen_player_x, screen_player_y, mapcol, mapspec; // point on screen were player is
extern unsigned char playerdirection, changedmap, maptojoindirection; // direction of movement and way player facing
extern int sx, sy; // these numbers keep the scrolling working when going straight up 
extern unsigned char ismove, move, vblankcount, timer1, timer2, vblanktime; //if player moving on map + vblank and timing
extern unsigned int keysheld, keyspressed, keysreleased; //keys
extern unsigned int border_no, texttilesize, textboxline, textletter;// text box vars 
extern unsigned char wateranimationcount; //animation counters (expand)
extern unsigned char tempchar,tempchar2; //temp var to store variables in
//*********************************************************************************
// pointers for maps
//*********************************************************************************
	
extern aMap *maptouse, *maptojoin, *mapviewable;

//*********************************************************************************
// pointers for sprites
//*********************************************************************************
extern aSprite playerspritedata,charspritedata[];

#endif