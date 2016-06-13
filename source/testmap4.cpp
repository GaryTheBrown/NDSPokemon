#include "pokemon.h"



//*********************************************************************************
// testmap
//*********************************************************************************
	const unsigned short int testmap4_border[8] = {1,1,1,1,1,1,1,1};
	const unsigned short int testmap4_mapdata[]= {
		0x59,0x59,0x59,0x59,0x59,
		0x59,0x59,0x59,0x59,0x59,
		0x59,0x59,0x59,0x59,0x59,
		0x59,0x59,0x59,0x59,0x59,
		0x59,0x59,0x77,0x59,0x59,
		0x00,0x00,0x00,0x00,0x00
	};
	const unsigned char testmap4_mapcol[]=	{	//collision or special number
		0x00,0x00,0x00,0x00,0x00,
		0x00,0x02,0x02,0x02,0x00,
		0x00,0x02,0x02,0x02,0x00,
		0x00,0x02,0x02,0x02,0x00,
		0x00,0x02,0x02,0x02,0x00,
		0x00,0x00,0xC5,0x00,0x00
		
	};
	const unsigned short int testmap4_mapspec[]= {	// special number to go with collision to gain extra info
		0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x01,0x00,0x00
	};
	
	const std::string testmap4_textbox[1] = {
	"Welcome to the indoor room please leave now!!"
	};
	
	const aSpritedata testmap4_Spritedata[1] = {
	// 	id	map_x	map_y	direct	visible	script	text	tiles				pal
	{	1,	2,	1,	2,	true,	0,	1,	(unsigned char*)&OAKTiles, 	(unsigned short*)&OAKPal}
	};
	
	const aWarpdata testmap4_warpdata[1] = {
	//(char tile,	top/bottom,char type,amap* mapto,char mapx,char mapy)
	{	1,	true,	3,	&testmap1,	9,	3}
	};
	
	aMap testmap4 = {
	4, // id
	"Test House", //name
	5,6, //width, height 
	(unsigned short int*)&testmap4_border,
	(unsigned short int*)&testmap4_mapdata,
	(unsigned char*)&testmap4_mapcol,
	(unsigned short int*)&testmap4_mapspec,
	(std::string*)&testmap4_textbox,
	0,
	1,(aSpritedata*)&testmap4_Spritedata,
	0,0,
	(aWarpdata*)&testmap4_warpdata,
	0,0,
	0,0,
	0,0,
	0,0
};	

