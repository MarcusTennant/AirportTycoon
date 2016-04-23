#include <curses.h>
#include <stdio.h>

#include "Keys.h"


int keys_setupInput()
{
	cbreak();
	return 1;
}

int keys_destroyInput()
{ 

	return 1;
}

keypress keys_getKey()
{
	int key;
	scanf(" %c",&key);
	if (key == 'q')		return QUIT;
	else if (key == 't')	return ADDTERMINAL;
	else if (key == 'r')	return ADDRUNWAY;
	else if (key == 'g')	return ADDGATE;
	else if (key == 'd')	return DESTROY;
	else if (key == 'k')	return UP;
	else if (key == 'j')	return DOWN;
	else if (key == 'h')	return LEFT;
	else if (key == 'l')	return RIGHT;
	else if (key == 'e')	return ROT;
	else 			return CONT;
}
