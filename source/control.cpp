#include "pokemon.h"
//==============================================================================
// Complete player action function
// This function does all the movement, collision and actions for player.
//==============================================================================
void player_action(){
//------------------------------------------------------------------------------

	//check if movement.
	if ((((sy-8)%16)==0)&&(((sx-8)%16)==0)&&(move == 0)&&(!lock_player)&&(!player_script_lock)&&(!boolafterwarp)){
		//directions
		if (keysheld & KEY_UP   ){lock_a = false;lock_b=false;lock_x = false;lock_y = false;lock_l = false;lock_r = false;lock_start = false;lock_select = false;if (playerdirection != 1){playerdirection=1;charspritechange(&playerspritedata,0);lock_player=true;return;} else {move = 1;}}
		if (keysheld & KEY_DOWN ){lock_a = false;lock_b=false;lock_x = false;lock_y = false;lock_l = false;lock_r = false;lock_start = false;lock_select = false;if (playerdirection != 2){playerdirection=2;charspritechange(&playerspritedata,3);lock_player=true;return;} else {move = 1;}}
		if (keysheld & KEY_LEFT ){lock_a = false;lock_b=false;lock_x = false;lock_y = false;lock_l = false;lock_r = false;lock_start = false;lock_select = false;if (playerdirection != 3){playerdirection=3;charspritechange(&playerspritedata,6);lock_player=true;return;} else {move = 1;}}
		if (keysheld & KEY_RIGHT){lock_a = false;lock_b=false;lock_x = false;lock_y = false;lock_l = false;lock_r = false;lock_start = false;lock_select = false;if (playerdirection != 4){playerdirection=4;charspritechange(&playerspritedata,9);lock_player=true;return;} else {move = 1;}}
	}
		//buttons
		if ((keysheld & KEY_A)&& !lock_a){lock_a = true;}
		if ((keysheld & KEY_B)&& !lock_b){lock_b = true;}
		if ((keysheld & KEY_X)&& !lock_x){lock_x = true;}
		if ((keysheld & KEY_Y)&& !lock_y){lock_y = true;}
		if ((keysheld & KEY_L)&& !lock_l){lock_l = true;}
		if ((keysheld & KEY_R)&& !lock_r){lock_r = true;}
		if ((keysheld & KEY_START)&& !lock_start){lock_start = true;}
		if ((keysheld & KEY_SELECT)&& !lock_select){lock_select = true;}
	
	
		Collision checks
		char playercol = 0;
	switch (playerdirection){
		case 1:
			if (map_player_y == 0){
				//HERE IS WHERE I ADD CHECKS FOR SPRITE on map joining if I do?
				maptojoin = maptouse->connection_north_name;
				mapcol = getmapcol(1 , maptojoin->height - 1, map_player_x - maptouse->connection_north_offset);
				mapspec = getmapspec(1 , maptojoin->height - 1, map_player_x - maptouse->connection_north_offset);
				changedmap = 1;
			}else{
				for (unsigned int i = 0; i < maptouse->Spritedatasize; i++){
					if((maptouse->Spritedata[i].visible)&&(maptouse->Spritedata[i].map_y == map_player_y - 1)&&(maptouse->Spritedata[i].map_x == map_player_x)){playercol = (i+1);}
				}
				mapcol = getmapcol(0 , map_player_y - 1 , map_player_x);
				mapspec = getmapspec(0 , map_player_y - 1 , map_player_x);
				changedmap = 0;
			}
			break;
		case 2:
			if (map_player_y == maptouse->height -1){
				maptojoin = maptouse->connection_south_name;
				mapcol = getmapcol(1 , 0, map_player_x - maptouse->connection_south_offset);
				mapspec = getmapspec(1 , 0, map_player_x - maptouse->connection_south_offset);
				changedmap = 2;
			}else{
				for (unsigned int i = 0; i < maptouse->Spritedatasize; i++){
					if((maptouse->Spritedata[i].visible)&&(maptouse->Spritedata[i].map_y == map_player_y + 1)&&(maptouse->Spritedata[i].map_x == map_player_x)){playercol = (i+1);}
				}
				mapcol = getmapcol(0 , map_player_y + 1 , map_player_x);
				mapspec = getmapspec(0 , map_player_y + 1 , map_player_x);
				changedmap = 0;
			}
			break;
		case 3:
			if (map_player_x == 0){
				maptojoin = maptouse->connection_east_name;
				mapcol = getmapcol(1 , map_player_y - maptouse->connection_west_offset, maptojoin->width - 1 );
				mapspec = getmapspec(1 , map_player_y - maptouse->connection_west_offset, maptojoin->width - 1 );
				changedmap = 3;
			}else{
				for (unsigned int i = 0; i < maptouse->Spritedatasize; i++){
					if((maptouse->Spritedata[i].visible)&&(maptouse->Spritedata[i].map_y == map_player_y)&&(maptouse->Spritedata[i].map_x == map_player_x -1)){playercol = (i+1);}
				}
				mapcol = getmapcol(0 , map_player_y , map_player_x - 1);
				mapspec = getmapspec(0 , map_player_y , map_player_x - 1);
				changedmap = 0;
			}
			break;
		case 4:
			if (map_player_x == maptouse->width -1){
				maptojoin = maptouse->connection_west_name;
				mapcol = getmapcol(1 , map_player_y - maptouse->connection_east_offset , 0 );
				mapspec = getmapspec(1 , map_player_y - maptouse->connection_east_offset , 0 );
				changedmap = 4;
			}else{
				for (unsigned int i = 0; i < maptouse->Spritedatasize; i++){
					if((maptouse->Spritedata[i].visible)&&(maptouse->Spritedata[i].map_y == map_player_y)&&(maptouse->Spritedata[i].map_x == map_player_x + 1)){playercol = (i+1);}
				}
				mapcol = getmapcol(0 , map_player_y , map_player_x + 1);
				mapspec = getmapspec(0 , map_player_y , map_player_x + 1);
				changedmap = 0;
			}
			break;	
	}
	
	if(playercol>0){
		if (maptouse->Spritedata[playercol-1].spritetext>0){
			if (lock_a){
				if (!(keysheld & KEY_A)){
					if (textboxdone){
						charspritedata[playercol-1].frame = ((maptouse->Spritedata[playercol-1].direction-1)*3);
						lock_player = false;
						player_script_lock = false;
						textboxdone = false;
						lock_a = false;
						cleartextbox();
					}else{	
						unsigned char faceme;
						switch(playerdirection){
							case 1:
								faceme = 2;
								break;
							case 2:
								faceme = 1;
								break;
							case 3:
								faceme = 4;
								break;
							case 4:
								faceme = 3;
								break;
							default:
								faceme = 1;
							}
						
							charspritedata[playercol-1].frame = faceme;
							charspritechange(&charspritedata[playercol-1],(faceme-1)*3);
							lock_player = true;
							player_script_lock = true;
							lock_a = false;
							textbox(3,maptouse->textbox[maptouse->Spritedata[playercol-1].spritetext-1]/*text to show*/,4);
					}
				}
			}
		} else{
			lock_player = false;
			player_script_lock = false;
			
		}
		move = 0;
	}
	else{
	
		//movement function
		if((move > 0 && ismove == 0)||(ismove > 0 && (((sy-8)%16)>0))||(((sx-8)%16)>0)){collisionmovement(mapcol);}
		//button function
		if ((lock_a)&&(!(keysheld & KEY_A))){collisionbutton(mapcol);}
	}
	sx=sx%512+512;
        sy=sy%256+256;
        
        if(boolafterwarp){afterwarp();}
        
        //checks for completed move then updates quardinants
	if(((((sx-8)%16)==0)&&((sy-8)%16)==0)&&(ismove>0)){
		move -=1;
		if(move == 0){lock_player = false;player_script_lock = false;}
		ismove = 0;
		std::string oldmapname = maptouse->name; // take down map name to check against when moving off map
		switch(playerdirection){
			case 1:
				screen_player_y--;
				if((map_player_y==0)&&(changedmap==1)){
					map_player_y = maptojoin->height -1;
					map_player_x = map_player_x - maptouse->connection_north_offset;
					maptojoin = maptouse;
					maptouse = maptouse->connection_north_name;
				}else{
					map_player_y--;
				}
				screen_player_y=screen_player_y%16;
				updateplayerspritepriority();
				break;
			case 2:
				screen_player_y++;
				if((map_player_y==maptouse->height -1)&&(changedmap==2)){
					map_player_y = 0;
					map_player_x = map_player_x - maptouse->connection_south_offset;
					maptojoin = maptouse;maptouse = maptouse->connection_south_name;
				}else{
					map_player_y++;
				}
				screen_player_y=screen_player_y%16;
				updateplayerspritepriority();
				break;
			case 3:
				screen_player_x--;
				if((map_player_x==0)&&(changedmap==3)){
					map_player_x = maptojoin->width -1;
					map_player_y = map_player_y - maptouse->connection_west_offset;
					maptojoin = maptouse;maptouse = maptouse->connection_west_name; 
				}else{
					map_player_x--;
				}
				screen_player_x=screen_player_x%32;
				break;
			case 4:
				screen_player_x++;
				if((map_player_x==maptouse->width -1 )&&(changedmap==4)){
					map_player_x = 0;
					map_player_y = map_player_y - maptouse->connection_east_offset;
					maptojoin = maptouse;
					maptouse = maptouse->connection_east_name;
				}else{
					map_player_x++;
				}
				screen_player_x=screen_player_x%32;
				break;
		}
			
		if (changedmap > 0){
			changed_map(oldmapname);
			clearcharsprite();
			initcharsprite();
			initplayersprite();
			updateplayerspritepriority();
		}
		
		//here is where step on tile actions are
		collisionstep(getmapcol(0 , map_player_y , map_player_x));
	}
		
	if ((textboxdone)&&(timer1>0)){
		if (vblankcount == vblanktime){
			timer1++;
		}
		//HERE IS SETTING FOR TEXT BOX TIMER
		if (timer1 == 4){
			cleartextbox();
			timer1 = 0;
			vblanktime = 0;
			textboxdone = false;
		}
	}
	
	//stats on bottom screen temp
	consoleClear();
	printf("screen player x: %d\n" , screen_player_x);
	printf("screen player y: %d\n" , screen_player_y);
	printf("map player x: %d\n" , map_player_x);
	printf("map player y: %d\n" , map_player_y);
	printf("screen x: %d\n" , sx);
	printf("screen y: %d\n" , sy);
	printf("Player Direction: %d\n" , playerdirection);
	printf("vblank: %d\n" , vblankcount);
	printf("lock player: %d\n" , lock_player);
	printf("mapcol: %d\n" , mapcol);
	printf("mapspec: %d\n" , mapspec);
	printf("wateranimationcount: %d\n" , wateranimationcount);
	printf("playercol: %d\n" , playercol);
	printf("coll on: %d\n" ,getmapcol(0 , map_player_y , map_player_x));
	printf("spec on: %d\n" ,getmapspec(0 , map_player_y , map_player_x));
	printf("timer1: %d\n" ,timer1);
	printf("timer2: %d\n" ,timer2);
	if (lock_player){printf("lp ");}
	if (player_script_lock){printf("psl");}
	printf("\n");
	if (lock_a){printf("A");}
	if (lock_b){printf("B");}
	if (lock_x){printf("X");}
	if (lock_y){printf("Y");}
	if (lock_l){printf("LB");}
	if (lock_r){printf("RB");}
	if (lock_start){printf("St");}
	if (lock_select){printf("Se");}
}
