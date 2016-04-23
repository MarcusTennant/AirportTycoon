#ifndef BUILDING_H_
#define BUILDING_H_

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
typedef enum 
{
	ROTATED = 1,
	NO_LWALL = 2,
	NO_RWALL = 4,
	RUNWAY = 8,
	TERMINAL = 16,
	GATE = 32	
} building_t;
	
	

#endif // BUILDING_H_
