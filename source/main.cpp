#include "pokemon.h"

//*********************************************************************************
//*********************************************************************************
// START OF DATA
//*********************************************************************************
//*********************************************************************************

//*********************************************************************************
// pointers for maps
//*********************************************************************************

aMap* maptouse; // pointers for main map
aMap* maptojoin; // pointers for map moving to
aMap* mapviewable; //pointer for the map connected to the map being joined. this allows a small map to be useable due to need of drawing more than 2 screens.

//*********************************************************************************
// pointers for fixed sprites
//*********************************************************************************
aSprite playerspritedata, charspritedata[32];

//*********************************************************************************
// global variables
//*********************************************************************************
bool mapfunction = true, battlefunction = false, mainmenufunction = false, pausemenufunction = false, boolafterwarp = false;
bool lock_player = false, player_script_lock = false, lock_a = false,lock_b = false,lock_x = false,lock_y = false,lock_l = false,lock_r = false,lock_start = false,lock_select = false, textboxdone = false, textbox_firstpass = false, changemap = false;
u16 mapbg0[64*32] , mapbg1[64*32] , mapbg2[64*32], mapbg3[32*32]; //map backgrounds pallettes and tiles
int map_player_x , map_player_y; // map player pos
int bg0, bg1, bg2, bg3;
unsigned int screen_player_x , screen_player_y, mapcol, mapspec; // point on screen were player is and collision id
unsigned char playerdirection, changedmap = 0,maptojoindirection = 0; // direction of movement and way player facing
int sx = 512 + (8 * 16) + 8, sy = 256 + (4 * 8) + 8; // these numbers keep the scrolling working when going straight up 
unsigned char move = 0 , ismove = 0 , vblankcount = 0, timer1 = 0, timer2 = 0, vblanktime = 0; // movement and screen count
unsigned int keysheld = 0 , keyspressed = 0, keysreleased = 0; //keys info
unsigned int border_no = 0, texttilesize = 105, textboxline = 0, textletter = 0; // text box vars
unsigned char wateranimationcount = 0; //animation counters (expand)
unsigned char tempchar,tempchar2; //temp var to store variables in
//*********************************************************************************
//*********************************************************************************
// END OF DATA
//*********************************************************************************
//*********************************************************************************

//*********************************************************************************	
//*********************************************************************************
// START OF CODE
//*********************************************************************************
//*********************************************************************************

//==============================================================================
//vblank interupt function: for animation of tiles etc??? research
//==============================================================================
void irqvblank(){
//------------------------------------------------------------------------------
}

//==============================================================================
// Main function first function to run all to do firsts done here
//==============================================================================
int main(void){
//------------------------------------------------------------------------------
	
	// need to keep this before loading map!!! but can look at loading from save.
	maptouse = &testmap1;
	// run function to setup map screen
	setupmapscreen();
	start_map(10,5,4);
	subscreenconsolesetup();
	
	// show bg
	bgShow(0);
	bgShow(1);
	bgShow(2);
	bgShow(3);
	
	//setup sprite system
	initspritesystem();	
	//loop game loop start
	while(mapfunction){
		//must be called here to get keys pressed
		scanKeys();
		keysheld = keysHeld();
		keyspressed = keysDown();
		player_action();
		animation();
		swiWaitForVBlank();
		oamUpdate(&oamMain);
		
		bgSetScroll(0 , sx , sy);
		bgSetScroll(1 , sx , sy);
		bgSetScroll(2 , sx , sy);
		
		bgUpdate();
		
		
		if (vblankcount == 60) {vblankcount = 0;}
		if ((player_script_lock == false)&&(vblankcount % 3 == 0)) {lock_player = false;}
		vblankcount++;
	}
}
