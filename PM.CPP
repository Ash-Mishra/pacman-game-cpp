#include "pm.h"
#include<bios.h>
#include<process.h>
extern int reset;
int key;
void pm::draw_pacman(short ang)
{
	if(ang==1) ang=37; 
	setcolor(14);
	setfillstyle(1,14);
	if(dir!=RIGHT)
	{
		circle(x,y,r);
		floodfill(x,y,14);
		setfillstyle(1,0);
		setcolor(0);
	}

	switch(dir)
	{
	case RIGHT :pieslice(x,y,ang,360-ang,r);
				break;
	case LEFT  :pieslice(x,y,180+ang,180-ang,r);
			    break;
	case DOWN  :pieslice(x,y,270+ang,270-ang,r);
				break;
	case UP	   :pieslice(x,y,90+ang,90-ang,r);
				break;
	}

}
void pm::get_input()
{
     if(reset) {x=320;y=240;}
	 int i, flag, temp;
     temp=key;
     if(bioskey(1)!=0) key=bioskey(0);
     if(key!=UP && key!=DOWN && key!=RIGHT && key!=LEFT && key!=283) key=temp; 
     switch(key)
     {
		case  LEFT :flag=1;
					for(i=0;i<=r;i++)
					if(getpixel(x-r-1,y+i)==9 || getpixel(x-r-1,y-i)==9)
						flag=0;
					if(flag) dir=LEFT;
					break;
		case  RIGHT:flag=1;
					for(i=0;i<=r;i++)
					if(getpixel(x+r+1,y+i)==9 || getpixel(x+r+1,y-i)==9)
						 flag=0;
					if(flag) dir=RIGHT;
					break;
		case  UP   :flag=1;
					for(i=0;i<=r;i++)
					if(getpixel(x+i,y-r-1)==9 || getpixel(x-i,y-r-1)==9)
						 flag=0;
					if(flag) dir=UP;
					break;
		case  DOWN :flag=1;
					for(i=0;i<=r;i++)
					if(getpixel(x+i,y+r+1)==9 || getpixel(x-i,y+r+1)==9)
						flag=0;
					if(flag) dir=DOWN;
					break;
     }
     switch(dir)
     {
     	case  LEFT :flag=1;
					for(i=0;i<=r;i++)
					if(getpixel(x-r-1,y+i)==9 || getpixel(x-r-1,y-i)==9)
						flag=0;
					if(flag) 
					{
						xspeed=-GM_SPEED;
						yspeed=0;
					}
						else xspeed=0;
					break;
		case  RIGHT:flag=1;
					for(i=0;i<=r;i++)
					if(getpixel(x+r+1,y+i)==9 || getpixel(x+r+1,y-i)==9)
						 flag=0;
					if(flag)
					{
						xspeed=GM_SPEED;
						yspeed=0;
					}
						 else xspeed=0;	
					break;
		case  UP   :flag=1;
					for(i=0;i<=r;i++)
					if(getpixel(x+i,y-r-1)==9 || getpixel(x-i,y-r-1)==9)
						 flag=0;
					if(flag)
					{
						yspeed=-GM_SPEED;
						xspeed=0;
					} 
						else yspeed=0;
					break;
		case  DOWN :flag=1;
					for(i=0;i<=r;i++)
					if(getpixel(x+i,y+r+1)==9 || getpixel(x-i,y+r+1)==9)
						flag=0;
					if(flag)
					{
						yspeed=GM_SPEED;
						xspeed=0;
					} 
						else yspeed=0;
					break;
     }
	 x+=xspeed;
     y+=yspeed;
     //cout<<'('<<key<<','<<dir<<')'<<' '<<'\r';
     if(x==-GM_SPEED && dir==LEFT) x=SCREEN_W;           //values > 640 ! allowed?!
		else if(x==SCREEN_W-10 && dir==RIGHT) x=-10;


}
