#include "pokemon.h"
	
//==============================================================================
// Function to setup top screen for map
//
//==============================================================================
void setupmapscreen(){
//------------------------------------------------------------------------------


	//initilise video mode on main screen (mode 0)
	videoSetMode( MODE_0_2D | DISPLAY_SPR_ACTIVE | DISPLAY_BG3_ACTIVE | DISPLAY_SPR_1D_LAYOUT);

	
	//set bank A of memory for sprite graphics
	vramSetBankA(VRAM_A_MAIN_BG);
	
	//set bank B of memory for top screen layers
	vramSetBankB(VRAM_B_MAIN_BG);
	
	//set bank C of memory for top screen layer
	//vramSetBankC(VRAM_C_MAIN_BG);
	
	//set bank D of memory for top screen layer
	//vramSetBankD(VRAM_D_MAIN_BG);
	
	//set bank E of memory for sprite graphics
	vramSetBankE(VRAM_E_MAIN_SPRITE);
	//set bank F of memory for main screen extended palette
	vramSetBankF(VRAM_F_BG_EXT_PALETTE);
	
	//set bank G of memory for main screen extended palette
	vramSetBankG( VRAM_G_BG_EXT_PALETTE);
	
	//setup extended palettes
	REG_DISPCNT |= DISPLAY_BG_EXT_PALETTE;
	
	//initilise background 0(bg number, size, location of map, location of Tiles)
	bg0 = bgInit(0, BgType_Text8bpp, BgSize_T_512x256, BG0_map_Memory,BG0_Tiles_Memory);
	
	//initilise background 1 (sprites)
	bg1 = bgInit(1, BgType_Text8bpp, BgSize_T_512x256, BG1_map_Memory,BG1_Tiles_Memory);

	//initilise background 2 (above tiles)
	bg2 = bgInit(2, BgType_Text8bpp, BgSize_T_512x256, BG2_map_Memory,BG2_Tiles_Memory);
	
	// initilise background 3 (textbox)
	bg3 = bgInit(3, BgType_Text8bpp, BgSize_T_256x256, BG3_map_Memory,BG3_Tiles_Memory);
	
	// BG order (higher number = bottom layer)
	bgSetPriority(bg0, 3);
	bgSetPriority(bg1, 2);
	bgSetPriority(bg2, 1);
	bgSetPriority(bg3, 0);
	
	bgHide(bg0);
	bgHide(bg1);
	bgHide(bg2);
	
	// clear memory
	DC_FlushRange(mapbg0,32*64*2);
	DC_FlushRange(mapbg1,32*64*2);
	DC_FlushRange(mapbg2,32*64*2);
	//DC_FlushRange(mapbg3,32*32*2);	

	// Load tiles ** TO BE EXPANDED INTO MORE DYNAMIC SETUP see tiles.cpp
	tiles_load();
	
	// Load palette ** TO BE EXPANDED INTO MORE DYNAMIC SETUP see palette.cpp
	palette_load();
	
	// vblank enabled
	irqSet(IRQ_VBLANK,irqvblank);
	irqEnable(IRQ_VBLANK);

}
//==============================================================================
// Changed map functions to run I.E change music show map name
// 
//==============================================================================
void changed_map(std::string oldmapname){
//------------------------------------------------------------------------------
	// this is where you tell system to change music over and eventually load tiles and pallettes & sprites
	// first call functions 
				
	// function to display map name
	if (oldmapname !=maptouse->name){ // if map name moving to different then display it. (Do the same for music (areas of suspence))
		cleartextbox();
		textbox(0/*type*/,maptouse->name/*text to show*/);
		textboxdone = true;
		vblanktime = vblankcount;
		timer1 = 1;
	}
}

//==============================================================================
// Changes map
// 
//==============================================================================
void change_map(){
	
	//lock player sprite
	lock_player = true;
	player_script_lock = true;
	
	//black screen
	//use tile 335 to black screen
		for (unsigned int iy = 0; iy < (sizeof(mapbg3));) {
		// clear screen of other data
		mapbg3[iy] = 335;
		iy++;
	}
	dmaCopy(mapbg3 , BG_MAP_RAM(BG3_map_Memory) , (sizeof(mapbg3)));
	bgSetScrollf(3,0,0);	
	sx=(136);
        sy=(40);	
	bgSetScrollf(0,sx,sy);
	bgSetScrollf(1,sx,sy);
	bgSetScrollf(2,sx,sy);
	
	//disable sprites		
	oamDisable(&oamMain);
	clearcharsprite();
	
	
	std::string mapname = maptouse->name; // take down map name to check against when moving off map	
	signed int mapx = maptouse->warpdata[(getmapspec(0 , map_player_y , map_player_x)-1)].mapx;
	signed int mapy = maptouse->warpdata[(getmapspec(0 , map_player_y , map_player_x)-1)].mapy;
	maptouse = (aMap*)maptouse->warpdata[(getmapspec(0 , map_player_y , map_player_x)-1)].mapto;
	
	
	setupmapscreen();
	start_map(mapx, mapy,playerdirection);
	
	initspritesystem();	
	oamUpdate(&oamMain);
	
	
	for (unsigned int iy = 0; iy < 64;iy++) {
	swiWaitForVBlank();
	}
	cleartextbox();
	changed_map(mapname);
	changedmap = 0;	
}


//==============================================================================
// start of map function loads first section of map to screen needs to have
// calls for what map to load and where on map.
//==============================================================================
void start_map(signed int map_x, signed int map_y, unsigned char direction){
//------------------------------------------------------------------------------
	map_player_x = map_x;
	map_player_y = map_y;
	playerdirection = direction;
	
	// set top left of screen pos
	signed int map_screen_x = map_player_x - 16;
	signed int map_screen_y = map_player_y - 8;
	
	DC_FlushRange(mapbg0,32*64*2);
	DC_FlushRange(mapbg1,32*64*2);
	DC_FlushRange(mapbg2,32*64*2);

	// loop to load first data into main map (need to add custom co-ods)
	// copy part of map into map memory	
	for (unsigned char iy = 0; iy < 16;iy++) {
		for (unsigned char ix = 0; ix < 32;ix++) {
		place_tile(ix, iy, map_screen_x + ix, map_screen_y + iy);		
		}
	}
	
	updatebg();
	
	//set player location to centre of screen
	screen_player_x = 17;
	screen_player_y = 9;
}

//==============================================================================
// update the row/coloum of the map with new data
//
//==============================================================================
void partialmapupdate(){
//------------------------------------------------------------------------------

	signed int map_screen_x, map_screen_y;
	unsigned char screen_corner_x, screen_corner_y;

	switch (playerdirection) {
		case 1: //up
			// get data to use
			map_screen_x = map_player_x - 16;
			map_screen_y = map_player_y - 8;
			screen_corner_x = ((screen_player_x + 64 - 17) % 32);
			screen_corner_y = ((screen_player_y + 32 + 7) % 16);

		
			// check if tile is off map and load boarder tile otherwise load the tiles from the map
			for (unsigned char ix = 0; ix < 32;ix++) {
				place_tile((screen_corner_x + ix) % 32, screen_corner_y, map_screen_x + ix, map_screen_y);
			}
			break;
		case 2: //down
			// get data to use
			map_screen_x = map_player_x - 16;
			map_screen_y = map_player_y + 8;
			screen_corner_x = ((screen_player_x + 64 - 17) % 32);
			screen_corner_y = ((screen_player_y + 32 - 9) % 16);
		
		
			// check if tile is off map and load boarder tile otherwise load the tiles from the map		
			for (unsigned char ix = 0; ix < 32;ix++) {
				place_tile((screen_corner_x + ix) % 32, screen_corner_y, map_screen_x + ix, map_screen_y);
			}
			break;
		case 3: //left
			// get data to use
			map_screen_x = map_player_x - 16;
			map_screen_y = map_player_y - 8;
			screen_corner_x = ((screen_player_x + 64 + 15) % 32);
			screen_corner_y = ((screen_player_y + 32 - 9) % 16);
		
			// check if tile is off map and load boarder tile otherwise load the tiles from the map
			for (unsigned char iy = 0; iy < 16;iy++) {
				place_tile(screen_corner_x, (screen_corner_y + iy) % 16, map_screen_x, map_screen_y + iy);
			}
			break;
		case 4: //right
			// get data to use
			map_screen_x = map_player_x + 16;
			map_screen_y = map_player_y - 8;
			screen_corner_x = ((screen_player_x + 64 - 17) % 32);
			screen_corner_y = ((screen_player_y + 32 - 9) % 16);
		
			// check if tile is off map and load boarder tile otherwise load the tiles from the map
			for (unsigned char iy = 0; iy < 16;iy++) {
				place_tile(screen_corner_x, (screen_corner_y + iy) % 16, map_screen_x, map_screen_y + iy);
			}
			break;
	}
	updatebg();

}
//==============================================================================
// Get the tile from map data
// map id is which map to use 0=current 1=joining mp
// ix/iy coordinates to use
//==============================================================================
short int getmapdata(unsigned char mapid,int ix,int iy) {
//------------------------------------------------------------------------------
	unsigned short int toreturn;
	switch (mapid){
		case 0:
			toreturn = maptouse->mapdata[ix*maptouse->width+iy];
			break;
		case 1:
			toreturn = maptojoin->mapdata[ix*maptojoin->width+iy];
			break;
		case 2:
			toreturn = mapviewable->mapdata[ix*mapviewable->width+iy];
			break;
		default:
			toreturn = 0;
	}
	return toreturn;
}
//==============================================================================
// Get the collision data from map data
// map id is which map to use 0=current 1=joining mp
// ix/iy coordinates to use
//==============================================================================
short int getmapcol(unsigned char mapid,int ix,int iy) {
//------------------------------------------------------------------------------	
	unsigned short int toreturn;
	switch (mapid){
		case 0:
			toreturn = maptouse->mapcol[ix*maptouse->width+iy];
			break;
		case 1:
			toreturn = maptojoin->mapcol[ix*maptojoin->width+iy];
			break;
		case 2:
			toreturn = mapviewable->mapcol[ix*mapviewable->width+iy];
			break;
		default:
			toreturn = 0;
	}
	return toreturn;
}
//==============================================================================
// Get the special bit for tile from map data
// map id is which map to use 0=current 1=joining mp
// ix/iy coordinates to use
//==============================================================================
short int getmapspec(unsigned char mapid,int ix,int iy) {
//------------------------------------------------------------------------------
	unsigned short int toreturn;
	switch (mapid){
		case 0:
			toreturn = maptouse->mapspec[ix*maptouse->width+iy];
			break;
		case 1:
			toreturn = maptojoin->mapspec[ix*maptojoin->width+iy];
			break;
		case 2:
			toreturn = mapviewable->mapspec[ix*mapviewable->width+iy];
			break;
		default:
			toreturn = 0;
	}
	return toreturn;
}
//==============================================================================
// Get the special bit for tile from map data
// map id is which map to use 0=current 1=joining mp
// id 
//==============================================================================
short int getmaptextboxextradata(unsigned char mapid,int id) {
//------------------------------------------------------------------------------
	unsigned short int toreturn;
	switch (mapid){
		case 0:
			toreturn = maptouse->textboxdata[id].tile;
			break;
		case 1:
			toreturn = maptojoin->textboxdata[id].tile;
			break;
		case 2:
			toreturn = mapviewable->textboxdata[id].tile;
			break;
		default:
			toreturn = 0;
	}	
	return toreturn;
}
//==============================================================================
// Get the special bit for tile from map data
// map id is which map to use 0=current 1=joining mp
// ix/iy coordinates to use
//==============================================================================
short int getmapwarpextradata(unsigned char mapid,int id) {
//------------------------------------------------------------------------------
	unsigned short int toreturn;
	switch (mapid){
		case 0:
			toreturn = maptouse->warpdata[id].tile;
			break;
		case 1:
			toreturn = maptojoin->warpdata[id].tile;
			break;
		case 2:
			toreturn = mapviewable->warpdata[id].tile;
			break;
		default:
			toreturn = 0;
	}	
	return toreturn;
}




//==============================================================================
// Function to load the 16x16 tiles into the 8x8 memory 
// map id is which map to use 0=current 1=joining mp
// ix/iy coordinates to use on screen
// map_x/map_y coordinates to use to load tile data
//==============================================================================
void maintile(unsigned char mapid,int ix, int iy, int map_x, int map_y){
//------------------------------------------------------------------------------

// checks if map needs an upper tile, if so it places it in memory so far only col [0,1] has upper part if needed
	switch (getmapcol(mapid,map_y,map_x)) {
		
		//below player place tile
		case 0x00://impassible tile (below player so top of head will look correct)
		case 0x01://walk normal tile
		case 0x04://battle walk normal	
			
			mapbg1[((iy)*128)+((ix)*2)] = bg2_Tiles_map[getmapspec(mapid,map_y,map_x)*4];
			mapbg1[((iy)*128)+((ix)*2+1)] = bg2_Tiles_map[getmapspec(mapid,map_y,map_x)*4+1];
			mapbg1[((iy)*128+64)+((ix)*2)] = bg2_Tiles_map[getmapspec(mapid,map_y,map_x)*4+2];
			mapbg1[((iy)*128+64)+((ix)*2+1)] = bg2_Tiles_map[getmapspec(mapid,map_y,map_x)*4+3];
			mapbg2[((iy)*128)+((ix)*2)] = 0;
			mapbg2[((iy)*128)+((ix)*2+1)] = 0;
			mapbg2[((iy)*128+64)+((ix)*2)] = 0;
			mapbg2[((iy)*128+64)+((ix)*2+1)] = 0;
			break;
		
		//above player place tile
		case 0x02://walk normal tile 
		case 0x03://battle walk normal
				
			mapbg2[((iy)*128)+((ix)*2)] = bg2_Tiles_map[getmapspec(mapid,map_y,map_x)*4];
			mapbg2[((iy)*128)+((ix)*2+1)] = bg2_Tiles_map[getmapspec(mapid,map_y,map_x)*4+1];
			mapbg2[((iy)*128+64)+((ix)*2)] = bg2_Tiles_map[getmapspec(mapid,map_y,map_x)*4+2];
			mapbg2[((iy)*128+64)+((ix)*2+1)] = bg2_Tiles_map[getmapspec(mapid,map_y,map_x)*4+3];
			mapbg1[((iy)*128)+((ix)*2)] = 0;
			mapbg1[((iy)*128)+((ix)*2+1)] = 0;
			mapbg1[((iy)*128+64)+((ix)*2)] = 0;
			mapbg1[((iy)*128+64)+((ix)*2+1)] = 0;
			break;
		
		//special place tiles
		
		//case 0x05://grass - both upper and lower used
		
		//	break;
			
		case 0xC0://textbox - get upper tile from another place
			mapbg1[((iy)*128)+((ix)*2)] = bg2_Tiles_map[getmaptextboxextradata(mapid,getmapspec(mapid,map_y,map_x))*4];
			mapbg1[((iy)*128)+((ix)*2+1)] = bg2_Tiles_map[getmaptextboxextradata(mapid,getmapspec(mapid,map_y,map_x))*4+1];
			mapbg1[((iy)*128+64)+((ix)*2)] = bg2_Tiles_map[getmaptextboxextradata(mapid,getmapspec(mapid,map_y,map_x))*4+2];
			mapbg1[((iy)*128+64)+((ix)*2+1)] = bg2_Tiles_map[getmaptextboxextradata(mapid,getmapspec(mapid,map_y,map_x))*4+3];
			mapbg2[((iy)*128)+((ix)*2)] = 0;
			mapbg2[((iy)*128)+((ix)*2+1)] = 0;
			mapbg2[((iy)*128+64)+((ix)*2)] = 0;
			mapbg2[((iy)*128+64)+((ix)*2+1)] = 0;
			break;
			
		case 0xC5://warp
			if (maptouse->warpdata[(getmapspec(mapid,map_y,map_x)-1)].topbottom){
				mapbg2[((iy)*128)+((ix)*2)] = bg2_Tiles_map[getmapwarpextradata(mapid,(getmapspec(mapid,map_y,map_x)-1))*4];
				mapbg2[((iy)*128)+((ix)*2+1)] = bg2_Tiles_map[getmapwarpextradata(mapid,(getmapspec(mapid,map_y,map_x)-1))*4+1];
				mapbg2[((iy)*128+64)+((ix)*2)] = bg2_Tiles_map[getmapwarpextradata(mapid,(getmapspec(mapid,map_y,map_x)-1))*4+2];
				mapbg2[((iy)*128+64)+((ix)*2+1)] = bg2_Tiles_map[getmapwarpextradata(mapid,(getmapspec(mapid,map_y,map_x)-1))*4+3];
				mapbg1[((iy)*128)+((ix)*2)] = 0;
				mapbg1[((iy)*128)+((ix)*2+1)] = 0;
				mapbg1[((iy)*128+64)+((ix)*2)] = 0;
				mapbg1[((iy)*128+64)+((ix)*2+1)] = 0;
			}else{
				mapbg1[((iy)*128)+((ix)*2)] = bg2_Tiles_map[getmapwarpextradata(mapid,(getmapspec(mapid,map_y,map_x)-1))*4];
				mapbg1[((iy)*128)+((ix)*2+1)] = bg2_Tiles_map[getmapwarpextradata(mapid,(getmapspec(mapid,map_y,map_x)-1))*4+1];
				mapbg1[((iy)*128+64)+((ix)*2)] = bg2_Tiles_map[getmapwarpextradata(mapid,(getmapspec(mapid,map_y,map_x)-1))*4+2];
				mapbg1[((iy)*128+64)+((ix)*2+1)] = bg2_Tiles_map[getmapwarpextradata(mapid,(getmapspec(mapid,map_y,map_x)-1))*4+3];
				mapbg2[((iy)*128)+((ix)*2)] = 0;
				mapbg2[((iy)*128)+((ix)*2+1)] = 0;
				mapbg2[((iy)*128+64)+((ix)*2)] = 0;
				mapbg2[((iy)*128+64)+((ix)*2+1)] = 0;
			}
			
			break;
						
		default:
			mapbg1[((iy)*128)+((ix)*2)] = 0;
			mapbg1[((iy)*128)+((ix)*2+1)] = 0;
			mapbg1[((iy)*128+64)+((ix)*2)] = 0;
			mapbg1[((iy)*128+64)+((ix)*2+1)] = 0;
			mapbg2[((iy)*128)+((ix)*2)] = 0;
			mapbg2[((iy)*128)+((ix)*2+1)] = 0;
			mapbg2[((iy)*128+64)+((ix)*2)] = 0;
			mapbg2[((iy)*128+64)+((ix)*2+1)] = 0;
			break;
	}
		
	//loads under player part of the map to screen.	
	mapbg0[((iy)*128)+((ix)*2)] = bg0_Tiles_map[getmapdata(mapid,map_y,map_x)*4];
	mapbg0[((iy)*128)+((ix)*2+1)] = bg0_Tiles_map[getmapdata(mapid,map_y,map_x)*4+1];
	mapbg0[((iy)*128+64)+((ix)*2)] = bg0_Tiles_map[getmapdata(mapid,map_y,map_x)*4+2];
	mapbg0[((iy)*128+64)+((ix)*2+1)] = bg0_Tiles_map[getmapdata(mapid,map_y,map_x)*4+3];

}

//==============================================================================
// Function to check which border piece to use and paste it into the map
// Function to load the 16x16 border into the 8x8 memory chosing the right tile
// for the right part of the screen
// map id is which map to use 0=current 1=joining mp
// ix/iy coordinates to use on screen
// map_x/map_y coordinates to use to load border from tile data
//==============================================================================
void bordertile(int ix, int iy, signed int map_x , signed int map_y){
//------------------------------------------------------------------------------
			
	// Checks what border tile to put down not right
	unsigned char bordertouse=0; 
	if ((map_x % 2 == 0) 				&& ((map_y % 2 == 1) || (map_y % 2 ==  -1))) 	{bordertouse = 3;}				
	if (((map_x % 2 == 1) || (map_x % 2 == -1)) 	&& ((map_y % 2 == 1) || (map_y % 2 ==  -1))) 	{bordertouse = 2;}
	if ((map_x % 2 == 0) 				&& (map_y % 2 == 0)) 				{bordertouse = 1;}
	if (((map_x % 2 == 1) || (map_x % 2 == -1)) 	&& (map_y % 2 == 0)) 				{bordertouse = 0;}

	// inserts tile
	mapbg0[((iy)*128)+((ix)*2)] = bg0_Tiles_map[maptouse->border[bordertouse]*4];
	mapbg0[((iy)*128)+((ix)*2+1)] = bg0_Tiles_map[maptouse->border[bordertouse]*4+1];
	mapbg0[((iy)*128+64)+((ix)*2)] = bg0_Tiles_map[maptouse->border[bordertouse]*4+2];
	mapbg0[((iy)*128+64)+((ix)*2+1)] = bg0_Tiles_map[maptouse->border[bordertouse]*4+3];
	mapbg1[((iy)*128)+((ix)*2)] = bg2_Tiles_map[maptouse->border[bordertouse+4]*4];
	mapbg1[((iy)*128)+((ix)*2+1)] = bg2_Tiles_map[maptouse->border[bordertouse+4]*4+1];
	mapbg1[((iy)*128+64)+((ix)*2)] = bg2_Tiles_map[maptouse->border[bordertouse+4]*4+2];
	mapbg1[((iy)*128+64)+((ix)*2+1)] = bg2_Tiles_map[maptouse->border[bordertouse+4]*4+3];

	//clear top layer if anything there
	mapbg2[((iy)*128)+((ix)*2)] = 0;
	mapbg2[((iy)*128)+((ix)*2+1)] = 0;
	mapbg2[((iy)*128+64)+((ix)*2)] = 0;
	mapbg2[((iy)*128+64)+((ix)*2+1)] = 0;
		
}

//==============================================================================
// Function to check which border piece to use and paste it into the map
// Function to load the 16x16 border into the 8x8 memory chosing the right tile
// for the right part of the screen
// map id is which map to use 0=current 1=joining mp
// ix/iy coordinates to use on screen
// map_x/map_y coordinates to use to load data from
//==============================================================================
void place_tile(int ix, int iy, signed int map_x , signed int map_y){
//------------------------------------------------------------------------------
	bool placed = false;
	// check up
	if ((map_y < 0)&&(not(maptouse->connection_north_name==0))){ 
		maptojoin = maptouse->connection_north_name;
		maptojoindirection = 1;
		//check up left
		if ((map_x - maptouse->connection_north_offset < 0)&&(not(maptojoin->connection_west_name==0))){
			mapviewable = maptojoin->connection_west_name;
			if (not((map_x + mapviewable->width - maptouse->connection_north_offset < 0)||(map_y + maptojoin->height - maptojoin->connection_west_offset < 0)||(map_y + maptojoin->height - maptojoin->connection_west_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x + mapviewable->width - maptouse->connection_north_offset, map_y + maptojoin->height - maptojoin->connection_west_offset);
				placed = true;
			}
		//check up right
		}else if ((map_x - maptouse->connection_north_offset > maptojoin->width -1)&&(not(maptojoin->connection_east_name==0))){
			mapviewable = maptojoin->connection_east_name;
			if (not((map_x - mapviewable->width - maptouse->connection_north_offset > mapviewable->width -1)||(map_y + maptojoin->height - maptojoin->connection_west_offset < 0)||(map_y + maptojoin->height - maptojoin->connection_west_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x - maptojoin->width - maptouse->connection_north_offset, map_y + maptojoin->height - maptojoin->connection_east_offset);
				placed = true;
			}
		//check up up
		}else if ((map_y + maptojoin->height < 0)&&(not(maptojoin->connection_north_name==0))){
			mapviewable = maptojoin->connection_north_name;
			if (not((map_x - maptouse->connection_north_offset - maptojoin->connection_north_offset < 0)||(map_x - maptouse->connection_north_offset - maptojoin->connection_north_offset > mapviewable->width -1)||(map_y + maptojoin->height + mapviewable->height < 0))){
				maintile(2,ix, iy, map_x - maptouse->connection_north_offset - maptojoin->connection_north_offset, map_y + maptojoin->height + mapviewable->height);
				placed = true;
			}
		}else {
			
			if (not((map_x - maptouse->connection_north_offset < 0)||(map_x - maptouse->connection_north_offset > maptojoin->width -1)||(map_y + maptojoin->height < 0))){
				maintile(1,ix, iy, maptojoin->width + map_x - maptouse->connection_north_offset, maptojoin->height -1 + map_y);
				placed = true;
			}
		}
	}
	//check down
	if ((!placed)&&(map_y > maptouse->height -1)&&(not(maptouse->connection_south_name==0))){
		maptojoin = maptouse->connection_south_name;
		maptojoindirection = 2;
		//check down left
		if ((map_x - maptouse->connection_south_offset < 0)&&(not(maptojoin->connection_west_name==0))){
			mapviewable = maptojoin->connection_west_name;
			if (not((map_x + mapviewable->width - maptouse->connection_south_offset < 0)||(map_y - maptouse-> height - maptojoin->connection_west_offset < 0)||(map_y - maptouse-> height - maptojoin->connection_west_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x + mapviewable->width - maptouse->connection_south_offset, map_y - maptouse-> height - maptojoin->connection_west_offset);
				placed = true;
			}
		//check down right
		}else if ((map_x - maptouse->connection_south_offset > maptojoin->width-1)&&(not(maptojoin->connection_east_name==0))){
			mapviewable = maptojoin->connection_east_name;
			if (not((map_x - maptojoin->width - maptouse->connection_south_offset > mapviewable->width -1)||(map_y - maptouse-> height - maptojoin->connection_east_offset < 0)||(map_y - maptouse-> height - maptojoin->connection_east_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x - maptojoin->width - maptouse->connection_south_offset, map_y - maptouse-> height - maptojoin->connection_east_offset);
				placed = true;
			}
		//check down down
		}else if ((map_y > (maptouse->height-1)+(maptojoin->height-1))&&(not(maptojoin->connection_south_name==0))){
			mapviewable = maptojoin->connection_south_name;
			if (not((map_x - maptouse->connection_south_offset - maptojoin->connection_south_offset < 0)||(map_x - maptouse->connection_south_offset - maptojoin->connection_south_offset > mapviewable->width -1)||(map_y - maptouse->height - maptojoin->height > mapviewable->height -1))){
				maintile(2,ix, iy, map_x - maptouse->connection_south_offset - maptojoin->connection_south_offset, map_y - maptouse->height - maptojoin->height);
				placed = true;
			}
		}else{
			if (not((map_x - maptouse->connection_south_offset < 0)||(map_x - maptouse->connection_south_offset > maptojoin->width-1)||(map_y > (maptouse->height-1)+(maptojoin->height-1)))){
				maintile(1,ix, iy, maptojoin->width + map_x - maptouse->connection_south_offset, map_y - maptouse->height - 1);
				placed = true;
			}
		}
	}
	// check left
	if ((!placed)&&(map_x < 0)&&(not(maptouse->connection_west_name==0))){
		maptojoin = maptouse->connection_west_name;
		maptojoindirection = 3;
		// check left up
		if ((map_y - maptouse->connection_west_offset < 0)&&(not(maptojoin->connection_north_name==0))){
			mapviewable = maptojoin->connection_north_name;
			if (not((map_x + maptojoin->width - maptouse->connection_north_offset < 0)||(map_y + mapviewable->height - maptojoin->connection_west_offset < 0)||(map_y + mapviewable->height - maptojoin->connection_west_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x + maptojoin->width - maptouse->connection_north_offset, map_y + mapviewable->height - maptojoin->connection_west_offset);
				placed = true;
			}
		// check left down
		}else if((map_y - maptouse->connection_west_offset > maptojoin->height -1)&&(not(maptojoin->connection_south_name==0))){
			mapviewable = maptojoin->connection_south_name;
			if (not((map_x + maptojoin->width - maptouse->connection_south_offset < 0)||(map_x + maptojoin->width - maptouse->connection_south_offset > mapviewable->width -1)||( map_y - maptojoin->height - maptojoin->connection_west_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x + maptojoin->width -  maptouse->connection_south_offset, map_y - maptojoin->height - maptojoin->connection_west_offset);
				placed = true;
			}
		// check left left
		}else if((map_x + maptojoin->width < 0 )&&(not(maptojoin->connection_west_name==0))){
			mapviewable = maptojoin->connection_west_name;
			if (not((map_x + maptojoin->width + mapviewable->width < 0)||(map_y - maptouse->connection_west_offset - maptojoin->connection_west_offset < 0)||(map_y - maptouse->connection_west_offset - maptojoin->connection_west_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x + maptojoin->width + mapviewable->width , map_y - maptouse->connection_west_offset - maptojoin->connection_west_offset);
				placed = true;
			}
		}else{
			if (not((map_y - maptouse->connection_west_offset < 0)||(map_y - maptouse->connection_west_offset > maptojoin->height -1)||(map_x + maptojoin->width < 0 ))){
				maintile(1,ix, iy, maptojoin->width + map_x, map_y - maptouse->connection_west_offset);
				placed = true;
			}
		}
	}
	//check right
	if ((!placed)&&(map_x > maptouse->width -1)&&(not(maptouse->connection_east_name==0))){
		maptojoin = maptouse->connection_east_name;
		maptojoindirection = 4;
		//check right up
		if ((map_y - maptouse->connection_east_offset < 0)&&(not(maptojoin->connection_north_name==0))){
			mapviewable = maptojoin->connection_north_name;
			if (not((map_x - maptouse->width - maptouse->connection_north_offset > mapviewable->width -1)||(map_y + mapviewable->height - maptojoin->connection_east_offset < 0)||(map_y + mapviewable->height - maptojoin->connection_east_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x - maptouse->width - maptouse->connection_north_offset, map_y + mapviewable->height - maptojoin->connection_east_offset);
				placed = true;
			}
		//check right down
		}else if ((map_y - maptouse->connection_east_offset > maptojoin->height-1)&&(not(maptojoin->connection_south_name==0))){
			mapviewable = maptojoin->connection_south_name;
			if (not((map_x - maptojoin->width - maptouse->connection_south_offset > mapviewable->width -1)||(map_y - maptojoin->height - maptojoin->connection_east_offset < 0 )||(map_y - maptojoin->height - maptojoin->connection_east_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x - maptojoin->width - maptouse->connection_south_offset, map_y - maptojoin->height - maptojoin->connection_east_offset);
				placed = true;
			}
		//check right right
		}else if (( map_x > (maptouse->width-1)+(maptojoin->width-1))&&(not(maptojoin->connection_east_name==0))){
			mapviewable = maptojoin->connection_east_name;
			if (not((map_x - maptojoin->width - maptouse->width > mapviewable->width -1)||(map_y - maptouse->connection_east_offset - maptojoin->connection_east_offset < 0)||(map_y - maptouse->connection_east_offset - maptojoin->connection_east_offset > mapviewable->height -1))){
				maintile(2,ix, iy, map_x - maptojoin->width - maptouse->width , map_y - maptouse->connection_east_offset - maptojoin->connection_east_offset + 1);
				placed = true;
			}
		}else{
			if(not((map_y - maptouse->connection_east_offset < 0)||(map_y - maptouse->connection_east_offset > maptojoin->height-1)||( map_x > (maptouse->width-1)+(maptojoin->width-1)))){
				maintile(1,ix, iy,map_x - maptouse->width,map_y - maptouse->connection_east_offset );
				placed = true;
			}
		}
	// else we add the tile in the data
	}
	if(!placed){
		if ((map_x > maptouse->width -1)||(map_x < 0)||(map_y > maptouse->height -1)||(map_y < 0)){
			maptojoindirection = 0;
			bordertile(ix, iy, map_x, map_y);
		}else{
			maintile(0,ix, iy, map_x, map_y);
		}
	}
}

//==============================================================================
// Function to update background info from data
//
//==============================================================================
void updatebg(){
//------------------------------------------------------------------------------
	
	for (unsigned char iy = 0; iy < 32; iy++) {
		//first bg0
		//first the left half
		dmaCopy(mapbg0 + iy * 64, BG_MAP_RAM(BG0_map_Memory) + iy * 32,  32 * 2);
		//then the right half
		dmaCopy(mapbg0 + iy * 64 + 32, BG_MAP_RAM(BG0_map_Memory) + (32 * 32) + iy * 32,  32 * 2);

		//Second bg1
		//first the left half
		dmaCopy(mapbg1 + iy * 64, BG_MAP_RAM(BG1_map_Memory) + iy * 32,  32 * 2);
		//then the right half
		dmaCopy(mapbg1 + iy * 64 + 32, BG_MAP_RAM(BG1_map_Memory) + (32 * 32) + iy * 32,  32 * 2);
			
		//third bg2
		//first the left half
		dmaCopy(mapbg2 + iy * 64, BG_MAP_RAM(BG2_map_Memory) + iy * 32,  32 * 2);
		//then the right half
		dmaCopy(mapbg2 + iy * 64 + 32, BG_MAP_RAM(BG2_map_Memory) + (32 * 32) + iy * 32,  32 * 2);
	}
}
