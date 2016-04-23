#include <curses.h>
#include <stdio.h>

#include "Graphics.h"
#include "Grid.h"


static void displayInventory();
static void drawBuilding(building_st* build);

static const int  GRID_SCALE_X = 6;
static const int  GRID_SCALE_Y = 4;
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

void graphics_display(building_st* buildArr, int selX, int selY, inventory_st* inv)
{
	werase(win);	
	for (int i = 0; i < GRID_SIZE_X; i++){
		for (int j = 0; j < GRID_SIZE_Y; j++){	
			int index = (i*GRID_SIZE_Y)+j;	
			if(buildArr[index].exist)
				drawBuilding(&(buildArr[index]));
		}
	}
	mvwprintw(win, 1+selY*(GRID_SCALE_Y), 1+(selX*GRID_SCALE_X), "*");
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
	int x = build->xPos * GRID_SCALE_X;
	int y = build->yPos * GRID_SCALE_Y;
	int xSize = build->xSize * (GRID_SCALE_X-1);
	int ySize = build->ySize * (GRID_SCALE_Y-1);
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
		mvwprintw(win, y+ySize-1, x+1, "terminal");


	mvwaddch(win, y, x, tl); //corners clockwise
	mvwaddch(win, y, x+xSize, tr); 
	mvwaddch(win, y+ySize, x, ll);
	mvwaddch(win, y+ySize, x+xSize, lr); 
}
	
