#include "pokemon.h"


//==============================================================================
// function to do the movement based on collision data
//
//==============================================================================
void collisionmovement(char mapcollision){
//------------------------------------------------------------------------------
	
	switch(mapcollision){
		case 0x01: //walk normal(above tile)
		case 0x02: //walk normal(below tile)
		case 0x03: //battle walk normal(above tile)
		case 0x04: //battle walk normal(below tile)
		case 0x05: //battle (grass)walk normal(both tile)
			if ((((sy-8)%16)==0)||(((sx-8)%16)==0)) {partialmapupdate();checkcharvisible();}			
			playermove();			
			
			//animate player walking
			if ((((sy-8)%32)==8)||(((sx-8)%32)==8)){charspritechange(&playerspritedata,(((playerdirection-1)*3)+1));}
			if ((((sy-8)%32)==24)||(((sx-8)%32)==24)){charspritechange(&playerspritedata,(((playerdirection-1)*3)+2));}
			if ((((sy-8)%16)==0)&&(((sx-8)%16)==0)&&(ismove>0)){charspritechange(&playerspritedata,((playerdirection-1)*3));}
			break;	
		case 0xC5: //warp(tile,top/bottom,type,mapto,warptoid,mapx,mapy)
			timer2++;
			tempchar=maptouse->warpdata[((getmapspec(0,map_player_y,map_player_x)+1)*6-6)].type;
			switch(tempchar){
				case 0:
				case 1:
				case 3:
				default:
					playermove();
					break;
				case 2:
					if((timer2 == 1)||(timer2 > 32)){
						playermove();
					} else if((timer2 == 9)||(timer2 == 17)){
						unsigned int nexttile = ((timer2-1)/8);
						switch(playerdirection){
							case 1:
								if (maptouse->warpdata[(getmapspec(0,map_player_y-1,map_player_x)-1)].topbottom){
									mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+nexttile)*4];
									mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+nexttile)*4+1];
									mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+nexttile)*4+2];
									mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+nexttile)*4+3];
								}else{
									mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+nexttile)*4];
									mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+nexttile)*4+1];
									mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+nexttile)*4+2];
									mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+nexttile)*4+3];
								}
								break;
							case 2:
								if (maptouse->warpdata[(getmapspec(0,map_player_y+1,map_player_x)-1)].topbottom){
									mapbg2[((screen_player_y)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y+1,map_player_x)-1))+nexttile)*4];
									mapbg2[((screen_player_y)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y+1,map_player_x)-1))+nexttile)*4+1];
									mapbg2[((screen_player_y)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y+1,map_player_x)-1))+nexttile)*4+2];
									mapbg2[((screen_player_y)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y+1,map_player_x)-1))+nexttile)*4+3];
								}else{
									mapbg1[((screen_player_y)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y+1,map_player_x)-1))+nexttile)*4];
									mapbg1[((screen_player_y)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y+1,map_player_x)-1))+nexttile)*4+1];
									mapbg1[((screen_player_y)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y+1,map_player_x)-1))+nexttile)*4+2];
									mapbg1[((screen_player_y)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y+1,map_player_x)-1))+nexttile)*4+3];
								}
								break;
							case 3:
								if (maptouse->warpdata[(getmapspec(0,map_player_y,map_player_x-1)-1)].topbottom){
									mapbg2[((screen_player_y-1)*128)+((screen_player_x-2)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x-1)-1))+nexttile)*4];
									mapbg2[((screen_player_y-1)*128)+((screen_player_x-2)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x-1)-1))+nexttile)*4+1];
									mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-2)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x-1)-1))+nexttile)*4+2];
									mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-2)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x-1)-1))+nexttile)*4+3];
								}else{
									mapbg1[((screen_player_y-1)*128)+((screen_player_x-2)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x-1)-1))+nexttile)*4];
									mapbg1[((screen_player_y-1)*128)+((screen_player_x-2)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x-1)-1))+nexttile)*4+1];
									mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-2)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x-1)-1))+nexttile)*4+2];
									mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-2)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x-1)-1))+nexttile)*4+3];
								}
								break;
							case 4:
								if (maptouse->warpdata[(getmapspec(0,map_player_y,map_player_x+1)-1)].topbottom){
									mapbg2[((screen_player_y-1)*128)+((screen_player_x)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x+1)-1))+nexttile)*4];
									mapbg2[((screen_player_y-1)*128)+((screen_player_x)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x+1)-1))+nexttile)*4+1];
									mapbg2[((screen_player_y-1)*128+64)+((screen_player_x)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x+1)-1))+nexttile)*4+2];
									mapbg2[((screen_player_y-1)*128+64)+((screen_player_x)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x+1)-1))+nexttile)*4+3];
								}else{
									mapbg1[((screen_player_y-1)*128)+((screen_player_x)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x+1)-1))+nexttile)*4];
									mapbg1[((screen_player_y-1)*128)+((screen_player_x)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x+1)-1))+nexttile)*4+1];
									mapbg1[((screen_player_y-1)*128+64)+((screen_player_x)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x+1)-1))+nexttile)*4+2];
									mapbg1[((screen_player_y-1)*128+64)+((screen_player_x)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x+1)-1))+nexttile)*4+3];
								}
								break;
						}
						updatebg();
					
					} else if(timer2 == 25){		
						switch(playerdirection){
							case 1:
								mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = 0;
								mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = 0;
								mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = 0;
								mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = 0;
								mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = 0;
								mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = 0;
								mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = 0;
								mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = 0;
								break;
							case 2:
								mapbg2[((screen_player_y)*128)+((screen_player_x-1)*2)] = 0;
								mapbg2[((screen_player_y)*128)+((screen_player_x-1)*2+1)] = 0;
								mapbg2[((screen_player_y)*128+64)+((screen_player_x-1)*2)] = 0;
								mapbg2[((screen_player_y)*128+64)+((screen_player_x-1)*2+1)] = 0;
								mapbg1[((screen_player_y)*128)+((screen_player_x-1)*2)] = 0;
								mapbg1[((screen_player_y)*128)+((screen_player_x-1)*2+1)] = 0;
								mapbg1[((screen_player_y)*128+64)+((screen_player_x-1)*2)] = 0;
								mapbg1[((screen_player_y)*128+64)+((screen_player_x-1)*2+1)] = 0;
								break;                                                         
							case 3:
								mapbg2[((screen_player_y-1)*128)+((screen_player_x-2)*2)] = 0;
								mapbg2[((screen_player_y-1)*128)+((screen_player_x-2)*2+1)] = 0;
								mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-2)*2)] = 0;
								mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-2)*2+1)] = 0;
								mapbg1[((screen_player_y-1)*128)+((screen_player_x-2)*2)] = 0;
								mapbg1[((screen_player_y-1)*128)+((screen_player_x-2)*2+1)] = 0;
								mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-2)*2)] = 0;
								mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-2)*2+1)] = 0;
								break;
							case 4:
								mapbg2[((screen_player_y-1)*128)+((screen_player_x)*2)] = 0;
								mapbg2[((screen_player_y-1)*128)+((screen_player_x)*2+1)] = 0;
								mapbg2[((screen_player_y-1)*128+64)+((screen_player_x)*2)] = 0;
								mapbg2[((screen_player_y-1)*128+64)+((screen_player_x)*2+1)] = 0;
								mapbg1[((screen_player_y-1)*128)+((screen_player_x)*2)] = 0;
								mapbg1[((screen_player_y-1)*128)+((screen_player_x)*2+1)] = 0;
								mapbg1[((screen_player_y-1)*128+64)+((screen_player_x)*2)] = 0;
								mapbg1[((screen_player_y-1)*128+64)+((screen_player_x)*2+1)] = 0;
								break;
						}
						updatebg();
						if ((((sy-8)%16)==3)||(((sx-8)%16)==3)){updatespritepriority(&playerspritedata,3);}
					} 
			
					//animate player walking
					if ((((sy-8)%32)==8)||(((sx-8)%32)==8)){charspritechange(&playerspritedata,(((playerdirection-1)*3)+1));}
					if ((((sy-8)%32)==24)||(((sx-8)%32)==24)){charspritechange(&playerspritedata,(((playerdirection-1)*3)+2));}
					if ((((sy-8)%16)==0)&&(((sx-8)%16)==0)&&(ismove>0)){charspritechange(&playerspritedata,((playerdirection-1)*3));timer1=0;}
				break;
				//case 2:
				}
			
			break;
			
		default: // inpassable. add in sound etc.
			move = 0;
			lock_player = false;
			player_script_lock = false;
			break;
			
		}
}	



//==============================================================================
// function to do the button actions based on collision data
//
//==============================================================================
void collisionbutton(char mapcollision){
//------------------------------------------------------------------------------
	switch(mapcollision){
		case 0xC0: // sign
			if (textboxdone){
				lock_player = false;
				player_script_lock = false;
				textboxdone = false;
				lock_a = false;
				cleartextbox();
			}else{
				lock_player = true;
				player_script_lock = true;
				lock_a = false;
				textbox(maptouse->textboxdata[mapspec].type,maptouse->textbox[(unsigned short int)maptouse->textboxdata[mapspec].id],maptouse->textboxdata[mapspec].lines,maptouse->textboxdata[mapspec].offsetx,maptouse->textboxdata[mapspec].offsety,maptouse->textboxdata[mapspec].linelength);
			}
			break;
			
		case 0xC4: //warp(tile,top/bottom,type,mapto,warptoid,mapx,mapy)
			
			break;
			
		default:
			// do nothing otherwise
			break;
	}
}

//==============================================================================
// function to do the walk on tile actions based on collision data
//
//==============================================================================
void collisionstep(char mapcollision){
//------------------------------------------------------------------------------
	switch(mapcollision){
		case 0xC5:
			timer2=0;
			if ((((sy-8)%16)==0)&&(((sx-8)%16)==0)) {
				bgHide(bg0);
				bgHide(bg1);
				bgHide(bg2);
				bgHide(bg3);
				change_map();
				bgShow(bg0);
				bgShow(bg1);
				bgShow(bg2);
				bgShow(bg3);
				switch(tempchar){
					
					case 2:
						updatespritepriority(&playerspritedata,3);
						lock_player = false;
						player_script_lock = false;
						break;
					case 1:	
						break;
					case 3:
						updatespritepriority(&playerspritedata,3);
					default:
						lock_player = false;
						player_script_lock = false;
						break;
				}
				boolafterwarp = true;
			}
			break;
		default:
			// do nothing otherwise
			break;
	}
}


//==============================================================================
// basic movement function 
//
//==============================================================================
void playermove(){
//------------------------------------------------------------------------------
	ismove = playerdirection;
	switch(playerdirection){
		case 1:
			sy--;
			for (unsigned int i = 0; i < maptouse->Spritedatasize; i++){
				charspritedata[i].screen_y++;
				charspritechange(&charspritedata[i],charspritedata[i].frame);
			}
			break;
		case 2:
			sy++;
			for (unsigned int i = 0; i < maptouse->Spritedatasize; i++){
				charspritedata[i].screen_y--;
				charspritechange(&charspritedata[i],charspritedata[i].frame);
			}
			break;
		case 3:
			sx--;
			for (unsigned int i = 0; i < maptouse->Spritedatasize; i++){
				charspritedata[i].screen_x++;
				charspritechange(&charspritedata[i],charspritedata[i].frame);
			}
			break;
		case 4:
				sx++;
			for (unsigned int i = 0; i < maptouse->Spritedatasize; i++){
				charspritedata[i].screen_x--;
				charspritechange(&charspritedata[i],charspritedata[i].frame);
			}
			break;
	}
}


//==============================================================================
// function that runs after you have warped, if any action is needed to be done
// after loading new map. i.e. animations or player movements
//==============================================================================
void afterwarp(){
//------------------------------------------------------------------------------
	switch(tempchar){
		default:
			boolafterwarp = false;
			break;
		case 3:
			timer2++;
			if(timer2 == 8){
				if (maptouse->warpdata[(getmapspec(0,map_player_y,map_player_x)-1)].topbottom){
					mapbg2[((screen_player_y-1)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+1)*4];
					mapbg2[((screen_player_y-1)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+1)*4+1];
					mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+1)*4+2];
					mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+1)*4+3];
				}else{
					mapbg1[((screen_player_y-1)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+1)*4];
					mapbg1[((screen_player_y-1)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+1)*4+1];
					mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+1)*4+2];
					mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+1)*4+3];
				}
				updatebg();
			}else if(timer2 == 16){
				if (maptouse->warpdata[(getmapspec(0,map_player_y,map_player_x)-1)].topbottom){
					mapbg2[((screen_player_y-1)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+2)*4];
					mapbg2[((screen_player_y-1)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+2)*4+1];
					mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+2)*4+2];
					mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+2)*4+3];
				}else{
					mapbg1[((screen_player_y-1)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+2)*4];
					mapbg1[((screen_player_y-1)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+2)*4+1];
					mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+2)*4+2];
					mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y,map_player_x)-1))+2)*4+3];
				}
				updatebg();
			} else if(timer2 == 24){		
				mapbg2[((screen_player_y-1)*128)+((screen_player_x-1)*2)] = 0;
				mapbg2[((screen_player_y-1)*128)+((screen_player_x-1)*2+1)] = 0;
				mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-1)*2)] = 0;
				mapbg2[((screen_player_y-1)*128+64)+((screen_player_x-1)*2+1)] = 0;
				mapbg1[((screen_player_y-1)*128)+((screen_player_x-1)*2)] = 0;
				mapbg1[((screen_player_y-1)*128)+((screen_player_x-1)*2+1)] = 0;
				mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-1)*2)] = 0;
				mapbg1[((screen_player_y-1)*128+64)+((screen_player_x-1)*2+1)] = 0;
	
			}else if(timer2 == 32){
				move+=1;
				updatespritepriority(&playerspritedata,2);
				
			}else if(timer2 == 49){
				if (maptouse->warpdata[(getmapspec(0,map_player_y-1,map_player_x)-1)].topbottom){
					mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+2)*4];
					mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+2)*4+1];
					mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+2)*4+2];
					mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+2)*4+3];
				}else{
					mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+2)*4];
					mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+2)*4+1];
					mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+2)*4+2];
					mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+2)*4+3];
				}
				updatebg();
			
			}else if(timer2 == 57){
				if (maptouse->warpdata[(getmapspec(0,map_player_y-1,map_player_x)-1)].topbottom){
					mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+1)*4];
					mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+1)*4+1];
					mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+1)*4+2];
					mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+1)*4+3];
				}else{
					mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+1)*4];
					mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+1)*4+1];
					mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+1)*4+2];
					mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1))+1)*4+3];
				}
				updatebg();
			}else if (timer2 == 65){
				if (maptouse->warpdata[(getmapspec(0,map_player_y-1,map_player_x)-1)].topbottom){
					mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1)))*4];
					mapbg2[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1)))*4+1];
					mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1)))*4+2];
					mapbg2[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1)))*4+3];
				}else{
					mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1)))*4];
					mapbg1[((screen_player_y-2)*128)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1)))*4+1];
					mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1)))*4+2];
					mapbg1[((screen_player_y-2)*128+64)+((screen_player_x-1)*2+1)] = bg2_Tiles_map[(getmapwarpextradata(0,(getmapspec(0,map_player_y-1,map_player_x)-1)))*4+3];
				}
				updatebg(); 
			}else if(timer2 == 73){
			//	playermove();
				boolafterwarp = false;
				timer2 = 0;
			
			}
			
			//animate player walking
			if ((((sy-8)%32)==8)||(((sx-8)%32)==8)){charspritechange(&playerspritedata,(((playerdirection-1)*3)+1));}
			if ((((sy-8)%32)==24)||(((sx-8)%32)==24)){charspritechange(&playerspritedata,(((playerdirection-1)*3)+2));}
			if ((((sy-8)%16)==0)&&(((sx-8)%16)==0)&&(ismove>0)){charspritechange(&playerspritedata,((playerdirection-1)*3));}
			break;
	}
}

