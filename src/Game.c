#include "Game.h"
#include "Keys.h"
#include "Graphics.h"

#include "Inventory.h"
#include "Building.h"
#include "Grid.h"

static void update(keypress key);
static void setupUnits();
static building_st* spaceOccupied(int xSel, int ySel);
static int isBlocked(int xSel, int xSize);

void spawnBuilding(building_t type, int selX, int selY);
void spawnRunway();
void spawnTerminal();
void spawnGate();
void destroyBuilding();


inventory_st inventory = {0};

building_st buildArr[GRID_SIZE_X][GRID_SIZE_Y];
int curSelX = 0;
int curSelY = 0;
int rotation = 0;

int gameLoop()
{
	graphics_setupDisplay();
	keys_setupInput();
	setupUnits();
	
	int key;
	while((key = keys_getKey()) != QUIT)
	{
		update(key);
		graphics_display(&(buildArr[0][0]), curSelX, curSelY, &inventory);
	}

	keys_destroyInput();
	graphics_destroyDisplay();
	
	return 0;
}

static void update(keypress key)
{
	if (key == ADDRUNWAY)		spawnBuilding(RUNWAY | rotation, curSelX, curSelY);
	else if (key == ADDTERMINAL) 	spawnBuilding(TERMINAL | rotation, curSelX, curSelY);
	else if (key == ADDGATE) 	spawnBuilding(GATE | rotation, curSelX, curSelY);
	//else if (key == DESTROY)	
	
	else if (key == RIGHT)
	{
		if (curSelX < GRID_SIZE_X - 1)
			curSelX++;
	}		

	else if (key == LEFT)
	{
		if (curSelX > 0)
			curSelX--;
	}
	
	else if (key == DOWN)
	{
		if (curSelY < GRID_SIZE_Y - 1)
			curSelY++;
	}		
	
	else if (key == UP)
	{
		if (curSelY > 0)
			curSelY--;
	}	

	else if (key == ROT) rotation = rotation ? 0 : 1;

}

static void setupUnits()
{
	inventory.money = 1000;
	inventory.reputation = 0; 
	inventory.skill = 10;

	for(int i = 0; i < GRID_SIZE_X; i++)
	{
		for (int j = 0; j < GRID_SIZE_Y; j++)
			buildArr[i][j].exist = 0;
	}
}

static building_st* spaceOccupied(int xSel, int ySel)
//checks if cell is already occupied
//returns pointer to the occupying building if taken, 0 otherwise
{
	if (xSel < 0 || xSel >= GRID_SIZE_X || ySel < 0 || ySel >= GRID_SIZE_Y)
		return 0;

	for (int i = 0; i < GRID_SIZE_X; i++){
		for (int j = 0; j < GRID_SIZE_Y; j++)
		{
			building_st tempB = buildArr[i][j];
			if ((tempB.xPos <= xSel) && (tempB.xPos+tempB.xSize-1 >= xSel))
				if ((tempB.xPos <= ySel) && (tempB.yPos + tempB.ySize-1 >= ySel))
					return &tempB;
		}	
	}

	return 0;
}

void spawnBuilding(building_t type, int selX, int selY)
{
	int xSize, ySize;
	if 	(type & TERMINAL) {xSize = 2; ySize = 3;} //TODO: there's better ways to do this
	else if (type & RUNWAY) {xSize = 1; ySize = 2;}
	else if (type & GATE)	{xSize = 1; ySize = 1;}

	if (type & ROTATED) {
		int tempSize = xSize;
		xSize = ySize;
		ySize = tempSize;
	}

//	if (!spaceOccupied(buildSel) && !isBlocked(buildSel, 2)){
		building_st* tempB = &(buildArr[curSelX][curSelY]);
		tempB->xPos = selX;
		tempB->yPos = selY;
		tempB->xSize = xSize;
		tempB->ySize = ySize;
		tempB->type = type;
		tempB->exist = 1;

		inventory.money -= 200;
//	}

}
/*static int isBlocked(int xSel, int xSize)
{
	building_st tempB = spaceOccupied(xSel
}*/

/*
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
*/
void spawnTerminal()
{
//	if (!spaceOccupied(buildSel) && !isBlocked(buildSel, 2)){
		building_st* tempB = &(buildArr[curSelX][curSelY]);
		tempB->xPos = curSelX;
		tempB->yPos = curSelY;
		tempB->xSize = 3;
		tempB->ySize = 3;
		tempB->type = TERMINAL;
		tempB->exist = 1;

		inventory.money -= 200;
//	}
}

void spawnGate(){}
/*{
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
	
}*/

//TODO: a buildings left neightbor may be index at elemToDestroy-2
// with current bildings it isn't an issue but it could cause future bugs
void destroyBuilding(){}
/*{
	int elemToDestroy;
	if ((elemToDestroy = spaceOccupied(buildSel)) != 0){ 
		buildArr[elemToDestroy].exist = 0;
		buildArr[elemToDestroy].xPos = -1;
		buildArr[elemToDestroy].yPos = -1;
		buildArr[elemToDestroy].xSize = 0;
		buildArr[elemToDestroy].ySize = 0;

		int type = buildArr[elemToDestroy].type;
		if (type & NO_LWALL)
			buildArr[elemToDestroy+1].type ^= NO_RWALL; //TODO: this works numerically, but is a bit confusing.
		if (type & NO_RWALL)
			buildArr[elemToDestroy-1].type ^= NO_LWALL;
	}
}*/
