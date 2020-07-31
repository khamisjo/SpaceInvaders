#ifndef UTILITIES_H
#define UTILITIES_H
#include <Windows.h>
#include <iostream>
using namespace std;


//const char LEFT_KEY  = 'a';
//const char RIGHT_KEY= 'd';
//const char UP_KEY    = 'w';
//const char DOWN_KEY = 's';


const int SCREEN_WIDTH = 70;
const int SCREEN_HEIGHT = 20;

const int BOARD_WIDTH = 50;
const int BOARD_HEIGHT = SCREEN_HEIGHT - (int)(SCREEN_HEIGHT * .1);

const int BOARD_X = 0;
const int BOARD_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int HERO_PROMPT_X = 0;
const int HERO_PROMPT_Y = BOARD_HEIGHT + 1;

enum COLOR {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};

static void setColor(COLOR color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


static int randInt(int limit)
{
	return std::rand() % limit;
}


#endif
