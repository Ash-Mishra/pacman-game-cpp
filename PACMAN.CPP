#include<iostream.h>

#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<bios.h>
#include<time.h>
#include "PM.cpp"
#include "MAP.h"
#include "GHOST.cpp"
#include "PELLET.cpp"
#include "EPELLET.cpp"
int score, mode, reset, complete, warn;
time_t cur,start;
pm pac;
pellet p[688];
epellet ep[4];
ghost blinky(4,620,460),pinky(13,20,460),inky(3,620,20),clyde(12,20,20);
void main()
{
	int gd=9,gm=2;
	char a[10];
	randomize();
	initgraph(&gd,&gm,"c:\\turboc3\\bgi\\");
	cleardevice();
	setcolor(14);
	settextstyle(10,HORIZ_DIR,7);
	outtextxy(120,120,"PACMAN");
	for(;gm<30;gm++)
	{
		sound(100+random(2000));
		delay(100);
		nosound();
	}
	do{
	score=0;
	complete=1;
	int lvl=0,lvlmdur, lives=3;
	short fdelay=0,fcount=0;
	while(key!=283 && lives)
	{
	double mode_dur=20;
	mode=key=quit=0;
	cleardevice();
	reset=1;
	warn=0;
	if(complete==1 || lvl==0)
	{
		lvl++;
		complete=0;
		itoa(lvl,a,10);
		setcolor(14);
		settextstyle(7,HORIZ_DIR,5);
		outtextxy(250,200,"Level");
		outtextxy(350,200,a);
		delay(1200);
		p[0].assignpellets(p);
		ep[0].assignpellets(ep);
	}
	lvlmdur=20/lvl;
	draw_map();
	start=time(NULL);
	while(key!=283 && !quit && !complete)
	{
		setcolor(9);
		settextstyle(2,0,5);
		itoa(lives,a,10);
		outtextxy(305,190,"Lives");
		outtextxy(320,210,a);
		itoa(score,a,10);
		outtextxy(305,254,"Score");
		outtextxy(308,269,a);
		complete=1;
		pac.get_input();
		pac.draw_pacman(fcount);
		blinky.update_pos(pac);
		pinky.update_pos(pac);
		inky.update_pos(pac);
		clyde.update_pos(pac);
		blinky.draw_gh(fcount);
		pinky.draw_gh(fcount);
		inky.draw_gh(fcount);
		clyde.draw_gh(fcount);
		delay(20);
		for(int i=0;i<688;i++) {p[i].check(pac);p[i].putpellet();}
		for(i=0;i<4;i++){ep[i].check(pac);ep[i].putpellet(fcount);}
		pac.erase_pacman();
		blinky.erase_gh();
		pinky.erase_gh();
		inky.erase_gh();
		clyde.erase_gh();
		fdelay++;
		cur=time(NULL);
		if(difftime(cur,start)>mode_dur || (mode==2 && mode_dur!=lvlmdur ))
		{
			if(mode==2)
			{
			      if(mode_dur!=lvlmdur) mode_dur=lvlmdur;
				else if(difftime(cur,start)<mode_dur+2)
				{if(warn==0)warn++;}
				 else if(mode_dur==lvlmdur) {mode_dur=20;mode=0;warn=0;}

			}
			else if(mode==0)
				 {
					mode=1;
					mode_dur=5;
				 }
					if(mode==1)
					{
						mode=0;
						mode_dur=20;
					}
			if(!warn)start=time(NULL);
		}
		if(fdelay==2)
		{
			nosound();
			fdelay=0;
			fcount++;
			if(fcount==2) fcount=0;
		}
		reset=0;
		setcolor(0);
		setfillstyle(1,0);
		bar(307,266,360,300);
	}
	nosound();
	cleardevice();
	if(!complete) lives--;
	}
	setcolor(14);
	settextstyle(3,HORIZ_DIR,10);
	outtextxy(130,20,"SCORE");
	itoa(score,a,10);
	settextstyle(2,HORIZ_DIR,10);
	outtextxy(300,200,a);
	settextstyle(7,HORIZ_DIR,2);
	outtextxy(300,400,"Press any key to continue...");
	getch();
	cleardevice();
	outtextxy(200,200,"Play again? Y/N..");
	do{
	key=getch();
	}while(key!='Y' && key!='y' && key!='N' && key!='n');
	}while(key=='Y' || key=='y');
	cleardevice();
	settextstyle(5,HORIZ_DIR,3);
	outtextxy(120,170,"Thank you for playing- Nikolas Socrates");
	delay(2000);
	closegraph();
}























