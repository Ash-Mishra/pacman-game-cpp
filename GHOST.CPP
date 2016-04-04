#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<time.h>
//#include<stdlib.h>
#include "GHOST.h"
#include"MAP.h"
int quit;
extern ghost pinky,inky, blinky, clyde;
extern int mode, score, reset, warn;
int ghost::dist(int x,int y,int x1,int y1)
{
	 return sqrt(pow(x-x1,2)+pow(y-y1,2));	
}
int ghost::mindist(int d[])
{
	int min=-1;
	for(int i=0;i<4;i++)
	{
		if(d[i])
			if(min==-1) min=i;
				else if(d[i]<d[min]) min=i;
					else if(d[i]==d[min]) 
							if(this==&blinky || this==&inky) min=i;
	} 
	return min;
}
void ghost::update_pos(pm &pac)
{
	if(reset) {x=defx;y=defy;}
	int i, offset=0, flag, d[4]={1,1,1,1}, min;
	static short di=0;
	di++;
	if(di==4) di=0;
//	randomize();
	if(this==&pinky) offset= 20;
		else if(this==&inky) offset= -20;
	xspeed=yspeed=0;
	if(doa && mode!=2) doa--;
	if(doa)
	{
		tx=defx;
		ty=defy;
		if(x==tx && y==ty) doa--;
	}
		else if(mode==0)
		{
			tx=pac.getposx()+offset;
			ty=pac.getposy()+offset;
		}
		else if(mode==1)
			{
				if(this==&blinky) tx=ty=700;
					if(this==&pinky) {tx=20;ty=460;}
						else if(this==&inky) {tx=620;ty=20;}
			}
				else if(mode==2)
				{	
						tx=SCREEN_W-pac.getposx()+offset;
						ty=SCREEN_H-pac.getposy()+offset;
				}
	for(i=0;i<=r;i++)
	{
		if(getpixel(x-r-1,y+i)==9 || getpixel(x-r-1,y-i)==9)
			d[0]=0;
		if(getpixel(x+i,y-r-1)==9 || getpixel(x-i,y-r-1)==9)
			d[1]=0;
		if(getpixel(x+r+1,y+i)==9 || getpixel(x+r+1,y-i)==9)	
			d[2]=0;
		if(getpixel(x+i,y+r+1)==9 || getpixel(x-i,y+r+1)==9)	
			d[3]=0;
			
	}
	if(dir==LEFT) d[2]=0;
		else if(dir==UP) d[3]=0;
			else if(dir==RIGHT) d[0]=0;
				else if(dir==DOWN) d[1]=0;
	
	if(d[0]+d[1]+d[2]+d[3]==1)
	{
		if(d[0]) dir=LEFT;
			else if(d[1]) dir=UP;
				else if(d[2]) dir=RIGHT;
					else if(d[3]) dir=DOWN;
	}
	if(d[0]+d[1]+d[2]+d[3]>1)
	{
//				if(this==&clyde) d[random(4)]=0;
				if(this==&clyde) d[di]=0;	
				if(d[0]) d[0]=dist(x-5,y,tx,ty);
				if(d[1]) d[1]=dist(x,y-5,tx,ty);
				if(d[2]) d[2]=dist(x+5,y,tx,ty);
				if(d[3]) d[3]=dist(x,y+5,tx,ty);
				min=mindist(d);	
				switch(min)
				{
					case 0:dir=LEFT;break;
					case 1:dir=UP;break;
					case 2:dir=RIGHT;break;
					case 3:dir=DOWN;break;
				}	
	}
	switch(dir)
	{
		case LEFT	:xspeed=-GM_SPEED;break;
		case UP 	:yspeed=-GM_SPEED;break;
		case RIGHT 	:xspeed=GM_SPEED;break;
		case DOWN 	:yspeed=GM_SPEED;break;
	}
	x+=xspeed;
	y+=yspeed;
	if(dist(x,y,pac.getposx(),pac.getposy())<15) 
	{
		if(mode==2 && !doa) {
		doa=1;
		setcolor(3);
		settextstyle(0,HORIZ_DIR,1);
		outtextxy(x,y,"200");
		score+=200;
		delay(200);
		}
			else if(mode!=2)quit++;
	}
	if(x==-GM_SPEED && dir==LEFT) x=SCREEN_W;           //values > 640 ! allowed?!
		else if(x==SCREEN_W-10 && dir==RIGHT) x=-10;
	
}
void ghost::draw_gh(short a)
{
	if(!doa) draw_ghbody(a);
	for(int i=-(4*r)/9;i<=(4*r)/9;i+=(8*r)/9)
		if((mode!=2 && !doa) || (mode==2 && doa))
			switch(dir)
			{
				case LEFT :	setfillstyle(1,15);
							setcolor(15);
							circle(x+i-2,y-1,2);
							floodfill(x+i-2,y-1,15);
							setfillstyle(1,1);
							setcolor(1);
							circle(x+i-3,y-1,1);
					    	floodfill(x+i-3,y-1,1);
							break;
				case RIGHT:	setfillstyle(1,15);
							setcolor(15);
							circle(x+i+2,y-1,2);
							floodfill(x+i+2,y-1,15);
							setfillstyle(1,1);
							setcolor(1);
							circle(x+i+3,y-1,1);
						    floodfill(x+i+3,y-1,1);
							break;
				case UP   :	setfillstyle(1,15);
							setcolor(15);
							circle(x+i,y-3,2);
							floodfill(x+i,y-3,15);
							setfillstyle(1,1);
							setcolor(1);
							circle(x+i,y-4,1);
						    floodfill(x+i,y-4,1);
							break;
				case DOWN : setfillstyle(1,15);
							setcolor(15);
							circle(x+i,y+1,2);
							floodfill(x+i,y+1,15);
							setfillstyle(1,1);
							setcolor(1);
							circle(x+i,y+2,1);
						    floodfill(x+i,y+2,1);
							break;
			}
			else 
			{
				setcolor(15);
				circle(x+i,y-1,1);
			}
	
}
void ghost::draw_ghbody(short &a)
{
	if(mode!=2)
	{
		setfillstyle(1,col);
		setcolor(col);
	}
		else
		{	
			int col=1;
			if(warn && a==0) col=15; 
			setfillstyle(1,col);
			setcolor(col);
		}
	sector(x,y,359,1,r,r-r/4);
	if(a==0)
	{
		int drawpts[24]={x-r,y,x+r,y,x+r,y+r,x+(7*r)/10,y+r/2,x+(5*r)/10,y+r,x+(3*r)/10,y+r,x+(3*r)/10,y+r/2,x-(3*r)/10,y+r/2,x-(3*r)/10,y+r,x-(5*r)/10,y+r,x-(7*r)/10,y+r/2,x-r,y+r};
		fillpoly(12, drawpts);
	}
		else
		{
			int drawpts[18]={x-r,y,x+r,y,x+r,y+r-r/8,x+(8*r)/9,y+r,x+r/2,y+r/2,x,y+r,x-r/2,y+r/2,x-(8*r)/9,y+r,x-r,y+r-r/8};
			fillpoly(9, drawpts);
		}
	if(mode==2) 
	{
			if(warn && a==0) setcolor(4);
				else setcolor(15);
			moveto(x-r+2,y+r/2);
			lineto(x-(6*r)/10,y+r/4);
			lineto(x-(4*r)/10,y+r/2);
			lineto(x,y+r/4);
			lineto(x+(4*r)/10,y+r/2);
			lineto(x+(6*r)/10,y+r/4);
			lineto(x+r-2,y+r/2);
	}	
}

