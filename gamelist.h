#ifndef _GAMELIST_H
#define _GAMELIST_H


#include "matrix.h"
#include "nimber.h"

struct Game_Struct {
	Nimber value;
	Matrix game;
	Game_Struct *next;
};

#endif