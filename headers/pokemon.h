#ifndef __pokemon_h
#define __pokemon_h

// C++ Libarys
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

// NDS Libarys
#include <nds.h>

// Globals
#include "globals.h" // global variables

// Start of Program
#include "main.h" // main program 

// Subscreen Setup TEMP
#include "subscreen.h" // main program 

// Map Loading
#include "map.h" // map display

// Controls
#include "control.h" // controls
#include "collision.h" // collision data

// Graphics
#include "palette.h" //palette info
#include "tiles.h" //tiles info
#include "animation.h" // animation program

//Sprite Loading
#include "sprites.h" //sprite functions

//text box
#include "textbox.h" // text box functions.

//Maps need to remove need for this some how and have maps in another folder. eventually loaded from files in a partition on the end of the rom?
#include "maps.h" //test map

#endif