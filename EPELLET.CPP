#include "EPELLET.H"
#include<graphics.h>
#include<math.h>
#include<dos.h>
extern int score, mode, complete;
void epellet::assignpellets(epellet *p)
{
	int n=0;
	for(int i=0;i<=SCREEN_W;i+=SCREEN_W)
	  	for(int j=0;j<=SCREEN_H;j+=SCREEN_H) 	
		{
			p[n].x=abs(i-110);
			p[n].y=abs(j-60);
			n++;		
		}
}
void epellet::check(pm &pac)
{
	if(pac.getposx()==x && pac.getposy()==y)
	{
		score+=50;
		setcolor(3);
		settextstyle(0,HORIZ_DIR,1);
		outtextxy(x,y,"50");
		x=y=-10;
		sound(300);
		delay(200);	
		mode=2;	
	}
}
void epellet::putpellet(int a)
{
	int r;
	if(a==0) {r=3;setfillstyle(1,0);bar(x+5,y+5,x-5,y-5);}
		else r=5;
	setcolor(15);
	setfillstyle(1,15);
	circle(x,y,r);
	floodfill(x,y,15);
	//if you're reading this my friend, power to you!
	if(x!=-10) complete=0;
}
