#ifndef KEYS_H_
#define KEYS_H_

typedef enum
{
	QUIT,
	ADDTERMINAL,
	ADDRUNWAY,
	ADDGATE,
	DESTROY,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ROT,
	CONT
} keypress;

int keys_setupInput();
int keys_destroyInput();
keypress keys_getKey();

#endif //KEYS_H_
