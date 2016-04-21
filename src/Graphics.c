#include <curses.h>
#include <stdio.h>

#include "Graphics.h"

#define GRID_SCALE 6

static void displayInventory();
static void drawBuilding(building_st* build);

int termSizeY, termSizeX;
WINDOW *borderWin, *win, *invWin;

inventory_st* tempInv;

void graphics_setupDisplay()
{
	initscr(); //typical ncurses setup
	noecho();
	curs_set(0);	

	getmaxyx(stdscr, termSizeY, termSizeX);
	refresh();

	borderWin = newwin(termSizeY-15, termSizeX, 0, 0);
	box(borderWin,0,0);
	wrefresh(borderWin);

	win = newwin(termSizeY-17, termSizeX-2, 1, 1);
	wrefresh(win);

        invWin = newwin(16, termSizeX, termSizeY-16, 0);
        wborder(invWin, 0, 0, 0, 0, ACS_LTEE, ACS_RTEE, 0, 0);
	wrefresh(invWin);
}

void graphics_destroyDisplay()
{
	endwin();
}

void graphics_display(building_st* buildArr, int buildSel, inventory_st* inv, int key)
{
	werase(win);	
	int i = 0;
	for (i; i < MAX_BUILDS; i++)
	{
		if(buildArr[i].exist)
			drawBuilding(&buildArr[i]);
	}
	mvwprintw(win, 1, 1+(buildSel*GRID_SCALE), "*");
	wrefresh(win);

	//TODO: if updated inv included in entity list update tempInv
	tempInv = inv;
	displayInventory();
}

static void displayInventory()
{
	char invBuf[125];	
	
	sprintf(invBuf, "Money: %i \t Reputation: %i \t Skill: %i", tempInv->money, tempInv->reputation, tempInv->skill);

	mvwprintw(invWin, 1, 1, invBuf);	
	
	wrefresh(invWin);
}

static void drawBuilding(building_st* build)
{
	int x = build->xPos * GRID_SCALE;
	int y = build->yPos * GRID_SCALE;
	int xSize = build->xSize * (GRID_SCALE-1);
	int ySize = build->ySize * (GRID_SCALE-1);
	int type = build->type;
	
	mvwhline(win, y, x, 0, xSize);
	mvwhline(win, y+ySize, x, 0, xSize);
	if (!(type & NO_RWALL))
		mvwvline(win, y, x, 0, ySize);
		
	if (!(type & NO_LWALL))
		mvwvline(win, y, x+xSize, 0, ySize);

	int tl, tr, ll, lr; //corners
		tl = ACS_ULCORNER;
		tr = ACS_URCORNER;	
		ll = ACS_LLCORNER;	
		lr = ACS_LRCORNER;	

	if (type & NO_LWALL) {
		tr = ACS_HLINE;
		lr = ACS_HLINE;
	}
	
	if (type & NO_RWALL) {
		tl = ACS_HLINE;
		ll = ACS_HLINE;
	}

	if (type & RUNWAY) //print dashed line in middle of runway
		mvwaddch(win, (y+y+ySize)/2, (x+x+xSize)/2, '-');
	else if (type & TERMINAL)
		mvwprintw(win, ySize-1, x+1, "terminal");


	mvwaddch(win, y, x, tl); //corners clockwise
	mvwaddch(win, y, x+xSize, tr); 
	mvwaddch(win, y+ySize, x, ll);
	mvwaddch(win, y+ySize, x+xSize, lr); 
}
	
