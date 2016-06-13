#include "pokemon.h"

//==============================================================================
// animation function will read all tiles in database and see what needs to be 
// animated and animate them.
//==============================================================================
void animation(){
//------------------------------------------------------------------------------

//these settings for water animation
unsigned char no_of_frames = 8, no_of_tiles = 11, bg_to_use = 0, tile_to_replace = 1, fps = 4;
u16* offset;
	if ((vblankcount%(60/fps))==1){
		const unsigned char* frame = water_Tiles + (wateranimationcount*(no_of_tiles*256));
		switch (bg_to_use){
			case 0:
				offset = (BG_TILE_RAM(BG0_Tiles_Memory))+(tile_to_replace*128);
				break;
			case 1:
			default:
				offset = (BG_TILE_RAM(BG1_Tiles_Memory))+(tile_to_replace*128);
				break;
			case 2:
				offset = (BG_TILE_RAM(BG2_Tiles_Memory))+(tile_to_replace*128);
				break;
		}
		dmaCopy(frame , offset ,(no_of_tiles*256));            
		wateranimationcount++;
		if(wateranimationcount >= no_of_frames) {wateranimationcount = 0;}
	}	
}


