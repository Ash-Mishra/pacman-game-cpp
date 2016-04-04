#ifndef _pm
#define _pm
#define SCREEN_W 640
#define SCREEN_H 480
#define GM_SPEED 5
#define LEFT 0x4B00
#define UP 0x4800
#define RIGHT 0x4D00
#define DOWN 0x5000
#define GM_RADIUS 9
#include<graphics.h>
class pm
{

		int x,y;
		int r;
		int xspeed, yspeed;
		int dir;
 public:void get_input();
 		int getposx() {return x;}
		int getposy() {return y;}
		void draw_pacman(short);
		pm()
		{
		     x=320;
			 y=240;
			 r=GM_RADIUS;
		}
		void erase_pacman()
		{
			setfillstyle(1,0);
			bar(x-r,y-r,x+r,y+r);
		}
};
#endif
