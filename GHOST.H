#ifndef _GHOST
#define _GHOST
#include<graphics.h>
class ghost
{

		int x,y;
		int defx,defy;
		int r;
		int xspeed, yspeed;
		int dir, predir;
		int col;
		int doa;
		int tx,ty;		   //dead or alive
 public:ghost(int c,int px,int py)
		{
			doa=0;
			col=c;
			x=defx=px;
			y=defy=py;
			r=GM_RADIUS;
			//xspeed=yspeed=GM_SPEED;
			dir=predir=0;
		}
		void update_pos(pm &);
		int dist(int, int, int, int);
		int mindist(int *);
		void draw_gh(short);
		void draw_ghbody(short &);
		void erase_gh()
		{
			setfillstyle(1,0);
			setcolor(0);
			bar(x-r,y-r,x+r,y+r);
		}

};
#endif
