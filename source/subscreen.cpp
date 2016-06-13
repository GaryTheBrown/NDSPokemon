#include "pokemon.h"

//==============================================================================
// TEMP CAN BE REMOVED
// Setup console screen to display info on sub screen
//==============================================================================
void subscreenconsolesetup(){
//------------------------------------------------------------------------------

//    PrintConsole bottomScreen;
    videoSetModeSub(MODE_0_2D); 
    vramSetBankC(VRAM_C_SUB_BG); 
    consoleInit(0 , 0 , BgType_Text4bpp , BgSize_T_256x256 , 31 , 0 , false , true);

}

