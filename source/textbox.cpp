#include "pokemon.h"

//==============================================================================
// Main textbox function will do all the main work for text.
//unsigned char type: type of box
//	0 = 1 line small box length top left of screen: 
//	1 = 1 line small box length top right of screen:  
//	2 = multi line box multi line top of screen: no clipping,
//	3 = multi line box multi line bottom of screen: no clipping,
//	4 = random box any location any size: clipping,
//std::string text: text to display will be using temp field
//unsigned char textlines: ammount of lines for multibox
//signed char offsetx: how far onto screen box will be down
//signed char offsety: how far onto screen box will be right
//signed char textperline: how many characters per line
//==============================================================================
int textbox( unsigned char type, std::string text, unsigned char textlines, signed char offsetx, signed char offsety, signed char textperline){
//------------------------------------------------------------------------------
	unsigned int n; // tile number
	unsigned int textlength = text.length();
	switch(type){
		//1 line small box length top left of screen,
		//textbox(type,text)
		case 0:
		case 1:{
			if (textlength > 30){errorbox(0);} else{
				unsigned int textlength2 = textlength;
				for (unsigned char a = 0; a < textlength; a++){
					if ((text[textletter+a] == '$')&&(text[textletter+a+1] != '$')){textlength2--;}
				}
				if (type == 0){n = 0;}else{n = 30-textlength2;}
				//DRAW BOX FIRST (with check built in for error)
				if(!drawtextbox(n,textlength2,1)){break;}
					// add text to box while clipping.
					if(!textboxtext(false,false,(n+33),textlength2,1,text)){break;}
				}
				textboxdone = true;
				textletter = 0;
				break;
		}
		//2 line box multi line top/bottom of screen (merged as only starting pos different
		//int textbox(type,text,textlines*)
		case 2:
		case 3:{
			//top or bottom setting 
			unsigned int boxstart;
			if (type == 2){boxstart = 0;}else{boxstart=((22-textlines)*32);}
			// If First run for textbox create box
			if (textletter == 0){
				//DRAW BOX FIRST (with check built in for error)
				if(!drawtextbox(boxstart,30,textlines)){break;}
			}
			if(!textboxtext(true,true,boxstart+33,30,textlines,text)){break;}
			// add text to box while not clipping.
			//Arrows
			if (textletter >= textlength){mapbg3[boxstart+(textlines*32)+30] = getcharacter('$','2');textboxdone=true;textletter = 0;} //down empty
			else {mapbg3[boxstart+(textlines*32)+30] = getcharacter('$','6');} //down fill
			break;
		}
		//4 = random box any location any size: clipping,
		case 4:{
			 int truetextlength = textlength;
			for (unsigned char a = 0; a < textlength; a++){
				if ((text[a] == '$')&&(text[a+1] != '$')){a++;truetextlength--;}
			}
			//check if settings are set
			if((offsetx == -1)||(offsety== -1)||(textperline== -1)){errorbox(3);} 
			//check if too much text for text area
			else if (truetextlength > (textperline*textlines)){errorbox(0);} 
			else {
				//DRAW BOX FIRST (with check built in for error)
				if(!drawtextbox(((offsetx*32)+offsety),textperline,textlines)){break;}
				// add text to box while clipping.
				if(!textboxtext(false,false,(offsetx*32+offsety+33),textperline,textlines,text)){break;}
			}
			textboxdone = true;
			textletter = 0;
			break;
		}
		default:{
			errorbox(2);
		}
	}		

	//trying flush of cache to see if this helps with the writing of the map
	DC_FlushRange(mapbg3 , sizeof(mapbg3));
	dmaCopy(mapbg3 , BG_MAP_RAM(BG3_map_Memory) , sizeof(mapbg3));

	return 0;
}

//==============================================================================
// Main questionbox function will use textbox function to create textbox for 
// question then will display the answers on top (or bottom screen) eventually
// ability to type answer on keyboard on bottom touch screen.
//unsigned char type: type of box 
//	0 = top question answers bottom 
//	1 =   
//	2 = 
//	3 = 
//std::string question: text to display will be using temp field
//unsigned char textlines: ammount of lines for multibox
//==============================================================================
int questionbox( unsigned char type, std::string question, unsigned char textlines){
//------------------------------------------------------------------------------

	return 0;
}

//==============================================================================
// draw text function remember 32x24 tiles 
// bool clip: will warp text 
//	true: will clip
//	false: will just print text
// bool arrows: leave space for arrows (true/false) 
// unsigned int n: start of box location
// unsigned char textperline: 
// unsigned char textlines: 
//==============================================================================
bool textboxtext(bool clip, bool arrows, int location, unsigned char textperline, unsigned char textlines, std::string text){
//------------------------------------------------------------------------------

	int n = location;
	unsigned int textlength = text.length();
	for (int t= 0; t < textlines; t++){
		unsigned int textrow = textperline;
		if(arrows){if (t == (textlines-1)){textrow--;}}
               
		for (unsigned char a = 0; a < textrow; a++){
                	if ((text[textletter+a] == '$')&&(text[textletter+a+1] != '$')){textrow++;}
                }
                if(clip){
                if (text[textletter] == ' '){textletter++;}
                	if (textletter < textlength){
                		unsigned int s = textletter+textrow;
                		if (s < textlength){
                			unsigned int textremove = 0;
                			while ((text[s] != ' ')&&(s != textletter)){ 
                				textrow--;
                				s--;
                				if((text[s] != '$')&&(text[s-1] != '$')){textremove++;}
                			}
                			textrow = textperline - textremove;
               			} else {textrow = textlength - textletter;}
               		}
               	}
               	unsigned int linetext = 0;
               	while ((linetext < textrow)&&(textletter < textlength)){
                	mapbg3[n] = getcharacter(text[textletter],text[textletter+1]);
                	if((text[textletter] == '$')&&(text[textletter+1] != '$')){textletter++;}
                	n++;
                	textletter++;
                	linetext++;
                }
                if(clip){
                	while (linetext < textperline){
                		mapbg3[n] = getcharacter(' ');
                		linetext++;
                		n++;
                	}
                }
                n=((32*(t+1))+location);
	}
	return true;
}
//==============================================================================
// draw textbox function remember 32x24 tiles 
// unsigned int n: start of box location
// unsigned char textperline: boxlength - 2
// unsigned char textlines: boxheight - 2
//==============================================================================
bool drawtextbox(unsigned int n, unsigned char textperline, unsigned char textlines){
//------------------------------------------------------------------------------
	//check if text goes outside of screen
	if (((textlines+(n/32)) > 22)||(((n%32)+textperline) > 30)){errorbox(1); return false;}
	else {
		// top left
		mapbg3[n] = (texttilesize + (border_no*8)+1);n++;
		//top line length of text.
		for (unsigned char i = 0; i<textperline; i++){
			mapbg3[n] = (texttilesize + (border_no*8)+2);
			n++;
		}
		// top right
		mapbg3[n] = (texttilesize + (border_no*8)+3);
		n+=(31-textperline);
		//LOOP HERE FOR number of lines
		for (unsigned char l = 0; l < textlines; l++){
			//left line one for each line of text
			mapbg3[n] = (texttilesize + (border_no*8)+4);n++;
			//white space
			for (unsigned char i = 0; i<textperline; i++){
				mapbg3[n] = getcharacter(' ');
				n++;	
			}
			
			//right line one for each line of text
			mapbg3[n] = (texttilesize + (border_no*8)+5);
			n+=(31-textperline);
		}
		//bottom left
		mapbg3[n] = (texttilesize + (border_no*8)+6);n++;
		//bottom line length of text.
		for (unsigned char i = 0; i<textperline; i++){
			mapbg3[n] = (texttilesize + (border_no*8)+7);
			n++;
		}	
		//bottom right
		mapbg3[n] = (texttilesize + (border_no*8)+8);
		return true;
	}
}
//==============================================================================
// function to take character and give tile id
//==============================================================================
int getcharacter(char letter, char letter2){
//------------------------------------------------------------------------------
	unsigned int tile = 96;
	if (letter =='A'){tile = 1;}
	if (letter =='B'){tile = 2;}
	if (letter =='C'){tile = 3;}
	if (letter =='D'){tile = 4;}
	if (letter =='E'){tile = 5;}
	if (letter =='F'){tile = 6;}
	if (letter =='G'){tile = 7;}
	if (letter =='H'){tile = 8;}
	if (letter =='I'){tile = 9;}
	if (letter =='J'){tile = 10;}
	if (letter =='K'){tile = 11;}
	if (letter =='L'){tile = 12;}
	if (letter =='M'){tile = 13;}
	if (letter =='N'){tile = 14;}
	if (letter =='O'){tile = 15;}
	if (letter =='P'){tile = 16;}
	if (letter =='Q'){tile = 17;}
	if (letter =='R'){tile = 18;}
	if (letter =='S'){tile = 19;}
	if (letter =='T'){tile = 20;}
	if (letter =='U'){tile = 21;}
	if (letter =='V'){tile = 22;}
	if (letter =='W'){tile = 23;}
	if (letter =='X'){tile = 24;}
	if (letter =='Y'){tile = 25;}
	if (letter =='Z'){tile = 26;}
	if (letter =='a'){tile = 27;}
	if (letter =='b'){tile = 28;}
	if (letter =='c'){tile = 29;}
	if (letter =='d'){tile = 30;}
	if (letter =='e'){tile = 31;}
	if (letter =='f'){tile = 32;}
	if (letter =='g'){tile = 33;}
	if (letter =='h'){tile = 34;}
	if (letter =='i'){tile = 35;}
	if (letter =='j'){tile = 36;}
	if (letter =='k'){tile = 37;}
	if (letter =='l'){tile = 38;}
	if (letter =='m'){tile = 39;}
	if (letter =='n'){tile = 40;}
	if (letter =='o'){tile = 41;}
	if (letter =='p'){tile = 42;}
	if (letter =='q'){tile = 43;}
	if (letter =='r'){tile = 44;}
	if (letter =='s'){tile = 45;}
	if (letter =='t'){tile = 46;}
	if (letter =='u'){tile = 47;}
	if (letter =='v'){tile = 48;}
	if (letter =='w'){tile = 49;}
	if (letter =='x'){tile = 50;}
	if (letter =='y'){tile = 51;}
	if (letter =='z'){tile = 52;}
	if (letter =='0'){tile = 53;}
	if (letter =='1'){tile = 54;}
	if (letter =='2'){tile = 55;}
	if (letter =='3'){tile = 56;}
	if (letter =='4'){tile = 57;}
	if (letter =='5'){tile = 58;}
	if (letter =='6'){tile = 59;}
	if (letter =='7'){tile = 60;}
	if (letter =='8'){tile = 61;}
	if (letter =='9'){tile = 62;}
	if (letter ==':'){tile = 63;}
	if (letter ==';'){tile = 64;}
	if (letter =='?'){tile = 65;}
	if (letter ==','){tile = 66;}
	if (letter =='-'){tile = 67;}
	if (letter =='.'){tile = 68;}
	if (letter =='/'){tile = 69;}
	if (letter =='\\'){tile = 70;} //(letter =='\')
	if (letter =='!'){tile = 71;}
	if ((letter =='$')&&(letter2 == 'S')){tile = 72;} //(letter == " open)
	if ((letter =='$')&&(letter2 == 's')){tile = 73;} //(letter == " close)
	if ((letter =='$')&&(letter2 == '$')){tile = 74;} //(letter == '$')
	if ((letter =='$')&&(letter2 == 'Q')){tile = 75;} //(letter == ' open)
	if ((letter =='$')&&(letter2 == 'q')){tile = 76;} //(letter == ' close)
	if (letter == 27){tile = 76;} //(letter == ')
	if (letter =='('){tile = 77;}
	if (letter ==')'){tile = 78;}
	if (letter =='['){tile = 79;}
	if (letter ==']'){tile = 80;}
	if ((letter =='$')&&(letter2 == '0')){tile = 81;} //(letter =='male') 
	if ((letter =='$')&&(letter2 == '1')){tile = 82;} //(letter =='female')
	if ((letter =='$')&&(letter2 == '.')){tile = 83;} //(letter =='...')
	if ((letter =='$')&&(letter2 == '2')){tile = 84;} //(letter =='downline')
	if ((letter =='$')&&(letter2 == '3')){tile = 85;} //(letter =='rightline')
	if ((letter =='$')&&(letter2 == '4')){tile = 86;} //(letter =='leftline')
	if ((letter =='$')&&(letter2 == '5')){tile = 87;} //(letter =='upline')
	if ((letter =='$')&&(letter2 == '6')){tile = 88;} //(letter =='down block')
	if ((letter =='$')&&(letter2 == '7')){tile = 89;} //(letter =='right block')
	if ((letter =='$')&&(letter2 == '8')){tile = 90;} //(letter =='left block')
	if ((letter =='$')&&(letter2 == '9')){tile = 91;} //(letter =='up block')
	if (letter =='#'){tile = 92;}
	if (letter =='&'){tile = 93;}
	if (letter =='%'){tile = 94;}
	if (letter =='+'){tile = 95;}
	
	// fail to load tile x should be multiply look at this at some point
	if ((letter =='$')&&(letter2 == 'x')){tile = 96;} //(letter =='X' (multiply))
	if ((letter =='$')&&(letter2 == ')')){tile = 97;} //(letter =='smile face')
	if ((letter =='$')&&(letter2 == '(')){tile = 98;} //(letter =='sad face')
	if ((letter =='$')&&(letter2 == '@')){tile = 99;} //(letter =='loud face')
	if ((letter =='$')&&(letter2 == '!')){tile = 100;} //(letter =='angry face')
	if ((letter =='$')&&(letter2 == 'e')){tile = 101;} //(letter =='é')
	if ((letter =='$')&&(letter2 == 't')){tile = 102;} //(letter =='(t)m')
	if ((letter =='$')&&(letter2 == 'm')){tile = 103;} //(letter =='t(m)')
	if ((letter =='$')&&(letter2 == 'c')){tile = 104;} //(letter = 'copyright')
	if (letter ==' '){tile = 105;} // //(letter ==' ' (space))
	
return tile;
}
//==============================================================================
// error textbox function if textbox cannot be displayed
//==============================================================================
void errorbox(unsigned char error){
//------------------------------------------------------------------------------
	cleartextbox();	
	switch (error){
		case 0:
			textbox(0,"Text Length Error");
			break;
		case 1:
			textbox(0,"Textbox Size Error");
			break;
		case 2:
			textbox(0,"Unknown Box Type Error");
			break;
		case 3:
			textbox(0,"Box Settings Error");
			break;
		default:
			textbox(0,"Unknown Error");
			break;
	}
}

//==============================================================================
// clear the text box
//==============================================================================
void cleartextbox(){
//------------------------------------------------------------------------------
	for (unsigned int iy = 0; iy < 1024;iy++) {
		// clear screen of other data
		mapbg3[iy] = 0;
	}
	DC_FlushRange(mapbg3 , sizeof(mapbg3));
	dmaCopy(mapbg3 , BG_MAP_RAM(BG3_map_Memory) , sizeof(mapbg3));
}
