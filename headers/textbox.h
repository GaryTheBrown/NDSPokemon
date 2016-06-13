#ifndef __textbox_h
#define __textbox_h
#include "pokemon.h"

extern int textbox(unsigned char type , std::string text, unsigned char textlines = 2, signed char offsetx = -1, signed char offsety = -1, signed char textperline = -1);
extern int questionbox(unsigned char type, std::string question, unsigned char textlines);
extern int getcharacter(char letter, char letter2 = ' ');
extern void errorbox(unsigned char error = 0);
extern void cleartextbox();
extern bool drawtextbox(unsigned int n, unsigned char textperline, unsigned char textlines);
extern bool textboxtext(bool clip, bool arrows, int location, unsigned char textperline, unsigned char textlines, std::string text);
#endif
