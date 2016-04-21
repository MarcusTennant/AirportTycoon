#ifndef BUILDING_H_
#define BUILDING_H_

#define MAX_BUILDS 20

typedef struct building
{
	int xPos;
	int yPos;
	int xSize;
	int ySize;

	int type;
	int exist;
	
} building_st;

//used as bit flags in the structs type field
//ex a runway = 0000 & NO_RWALL = 0010 -> a runway with no right wall 0010
//   a gate = 1000 & NO_LWALL = 0001 -> a gate with no left wall 1001
enum 
{
	NO_LWALL = 1,
	NO_RWALL = 2,
	RUNWAY = 4,
	TERMINAL = 8,
	GATE = 16	
};
	
	

#endif // BUILDING_H_
