#include "Game.h"
#include "Keys.h"
#include "Graphics.h"

#include "Inventory.h"
#include "Building.h"

static void update(keypress key);
static void setupUnits();
static int spaceOccupied(int xSel);
static int isBlocked(int xSel, int xSize);

void spawnRunway();
void spawnTerminal();
void spawnGate();
void destroyBuilding();


inventory_st inventory = {0};

building_st buildArr[MAX_BUILDS];
int buildSel = 0;


int gameLoop()
{
	graphics_setupDisplay();
	keys_setupInput();
	setupUnits();
	
	int key;
	while((key = keys_getKey()) != QUIT)
	{
		update(key);
		graphics_display(buildArr, buildSel, &inventory, key);
	}

	keys_destroyInput();
	graphics_destroyDisplay();
	
	return 0;
}

static void update(keypress key)
{
	void (*action)() = 0; //TODO: spawning is similar enough these should be one function
	if (key == ADDRUNWAY)		action = &spawnRunway;
	else if (key == ADDTERMINAL) 	action = &spawnTerminal;
	else if (key == ADDGATE) 	action = &spawnGate;
	else if (key == DESTROY)	action = &destroyBuilding;

	else if (key == RIGHT)
	{
		if (buildSel < MAX_BUILDS - 1)
			buildSel++;
	}		

	else if (key == LEFT)
	{
		if (buildSel > 0)
			buildSel--;
	}

	if (action != 0)
		(*action)();
}

static void setupUnits()
{
	inventory.money = 1000;
	inventory.reputation = 0; 
	inventory.skill = 10;

	for(int i = 0; i < MAX_BUILDS; i++)
	{
		buildArr[buildSel].exist = 0;
	}
}

static int spaceOccupied(int xSel)
//checks if grid is already occupied
//returns ANCHOR_POS (top left corner) if taken, 0 otherwise
{
	if (xSel < 0 || xSel >= MAX_BUILDS)
		return 0;

	for (int i = 0; i < MAX_BUILDS; i++)
	{
		building_st tempB = buildArr[i];
		if ((tempB.xPos <= xSel) && (tempB.xPos+tempB.xSize-1 >= xSel))
			return i;
	}

	return 0;
}

static int isBlocked(int xSel, int xSize)
//checks if there is open space for items which take up multiple grid spaces; 
//returns index of blocking building if space exists, 0 otherwise
{
	for (int i = 0; i < MAX_BUILDS; i++)
	{
		building_st tempB = buildArr[i];
		if ((tempB.xPos > xSel) && (tempB.xPos <= (xSel + xSize-1)))
			return i;
	}

	return 0;
}

void spawnRunway()
{
	if (!spaceOccupied(buildSel))
	{
		building_st* tempB = &buildArr[buildSel];
		tempB->xPos = buildSel;
		tempB->yPos = 0;
		tempB->xSize = 1;
		tempB->ySize = 2;
		tempB->exist = 1;
		

		int neighbor; 
		tempB->type = RUNWAY;
		if (neighbor = spaceOccupied(buildSel-1))
		{
			if (buildArr[neighbor].type & RUNWAY){
				tempB->type |= NO_RWALL;
				buildArr[neighbor].type |= NO_LWALL;
			}	
		}
	
		if (neighbor = spaceOccupied(buildSel+1))
		{
			if (buildArr[neighbor].type & RUNWAY){
				tempB->type |= NO_LWALL;
				buildArr[neighbor].type |= NO_RWALL;
			}	
		}	
		inventory.money -=  100;
	}
}

void spawnTerminal()
{
	if (!spaceOccupied(buildSel) && !isBlocked(buildSel, 2)){
		building_st* tempB = &buildArr[buildSel];
		tempB->xPos = buildSel;
		tempB->yPos = 0;
		tempB->xSize = 3;
		tempB->ySize = 3;
		tempB->type = TERMINAL;
		tempB->exist = 1;

		inventory.money -= 200;
	}
}

void spawnGate()
{
	if (!spaceOccupied(buildSel))
	{
		building_st* tempB = &buildArr[buildSel];
		tempB->xPos = buildSel;
		tempB->yPos = 0;
		tempB->xSize = 1;
		tempB->ySize = 1;
		tempB->exist = 1;
		

		int neighbor; 
		tempB->type = GATE;
		if (neighbor = spaceOccupied(buildSel-1))
		{
			if (buildArr[neighbor].type & GATE){
				tempB->type |= NO_RWALL;
				buildArr[neighbor].type |= NO_LWALL;
			}	
		}
	
		if (neighbor = spaceOccupied(buildSel+1))
		{
			if (buildArr[neighbor].type & GATE){
				tempB->type |= NO_LWALL;
				buildArr[neighbor].type |= NO_RWALL;
			}	
		}	
		inventory.money -=  50;
	}
	
}

//TODO: a buildings left neightbor may be index at elemToDestroy-2
// with current bildings it isn't an issue but it could cause future bugs
void destroyBuilding()
{
	int elemToDestroy;
	if ((elemToDestroy = spaceOccupied(buildSel)) != 0){ 
		buildArr[elemToDestroy].exist = 0;
		buildArr[elemToDestroy].xPos = -1;
		buildArr[elemToDestroy].yPos = -1;
		buildArr[elemToDestroy].xSize = 0;
		buildArr[elemToDestroy].ySize = 0;

		int type = buildArr[elemToDestroy].type;
		if (type & NO_LWALL)
			buildArr[elemToDestroy+1].type ^= NO_RWALL; //TODO: this work numerically, but is a bit confusing.
		if (type & NO_RWALL)
			buildArr[elemToDestroy-1].type ^= NO_LWALL;
	}
}
