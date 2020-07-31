#include "Gameboard.h"
#include "UserInterface.h"
#include "Utilities.h"
#include "Actor.h"
#include "Laser.h"
#include "Hero.h"
#include "Game.h"
#include "Alien.h"
#include <iostream>
using namespace std;
void Gameboard::drawBorder(Screen& screen) {
	setColor(LIGHTCYAN);
	Timer timer;
	const unsigned delay = 50;
	//top side
	//0 - 26
	for (int i = 0; i < BOARD_WIDTH - 1; i++) {
		screen.gotoXY(i, 0);
		screen.printChar('#');
	}
	//right side
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		screen.gotoXY(BOARD_WIDTH - 1, i);
		screen.printChar('#');
	}

	//bottom side
	//The minus 1 helps it print
	//Loops only go up to SIZE - 1
	// 0 - 26
	for (int i = BOARD_WIDTH - 1; i > 0; i--) {
		screen.gotoXY(i, BOARD_HEIGHT - 1);
		screen.printChar('#');
	}
	//left side
	for (int i = BOARD_HEIGHT - 1; i > 0; i--) {
		screen.gotoXY(0, i);
		screen.printChar('#');
	}
	timer.start();
	setColor(WHITE);
	screen.printChar('\n');
}


void Gameboard::displayStats(Screen& screen, Game * game) {

	setColor(LIGHTGRAY);
	screen.gotoXY(HERO_PROMPT_X, HERO_PROMPT_Y);
	// This adding a string to an int causes weird issue
	string health = to_string(game->getHero()->getHP());
	string heroString = "Hero: " + health + '\n';
	screen.gotoXY(0, 22);
	screen.printString("Score: " + to_string(game->getScore()) + "\n");
	screen.printString(heroString);
	screen.gotoXY(HERO_PROMPT_X, HERO_PROMPT_Y + 1);
	screen.printString("Weapon: |\n");
	string laserStrength = "Laser Strength: " + to_string(game->getHero()->getStrength());
	//screen.printString("\n");
	screen.printString(laserStrength + '\n');
}

void Gameboard::nextLevel(Screen & screen, Game*game)
{
	screen.clear();
	screen.gotoXY(0, 0);
	string level = to_string(game->getLevel());
	string message = "\tLevel completed.\n\tMoving on to Level " + level;
	message += "...\n";
	message += "\t+1 Alien @_@\n";
	screen.printString(message);
}

void Gameboard::displayScore(Screen & screen, Game * game)
{
	screen.gotoXY(0, 0);
	string message = "GAME OVER!\n";
	message += "Level: " + to_string(game->getLevel()) + "\n";
	message += "Score: " + to_string(game->getScore()) + "\n";
	float floatTime = (float)game->getTimePlayed() / 1000;
	floatTime = (floatTime*100.0) / 100.0;
	message += "Time Played: " + to_string(floatTime) + " seconds\n";
	screen.printString(message);
}


void Gameboard::drawActor(Screen& screen, Actor * actor) {
	COLOR color = (actor->getSymbol() == '&') ? LIGHTGREEN : LIGHTGRAY;
	setColor(color);
	if (color == LIGHTGREEN) {
		if (dynamic_cast<Alien*>(actor)->isSpecial()) {
			setColor(LIGHTMAGENTA);
		}
	}
	screen.gotoXY(actor->getPosition().column, actor->getPosition().row);
	screen.printChar(actor->getSymbol());
}

void Gameboard::drawLaser(Screen& screen, Laser * laser) {
	setColor(LIGHTRED);
	screen.gotoXY(laser->getPosition().column, laser->getPosition().row);
	screen.printChar(laser->getSymbol());
}



Gameboard::Gameboard() {

}


Gameboard::
~Gameboard() {

}
void Gameboard::displayGameOver() {

	string gameOver[10] = {
		"**********************************************",
		"*                                            *",
		"*                                            *",
		"*               --GAME OVER--                *",
		"*                                            *",
		"*   Press(y) to replay or (n) to end game    *",
		"*                                            *",
		"*                                            *",
		"*                                            *",
		"**********************************************"
	};
	for (unsigned i = 0; i < 10; i++) {
		cout << gameOver[i] << endl;
	}

}
void Gameboard::drawFancyBorder(COLOR color, Screen & screen) {
	setColor(color);
	Timer timer;
	const unsigned delay = 50;
	//top side
	//0 - 26
	for (int i = 0; i < BOARD_WIDTH - 1; i++) {
		screen.gotoXY(i, 0);
		screen.printChar('#');
		while (timer.elapsed() < delay) {

		}
		timer.start();
	}
	//right side
	setColor(color);
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		screen.gotoXY(BOARD_WIDTH - 1, i);
		screen.printChar('#');
		while (timer.elapsed() < delay) {

		}
		timer.start();
	}
	setColor(color);
	for (int i = BOARD_WIDTH - 1; i > 0; i--) {
		screen.gotoXY(i, BOARD_HEIGHT - 1);
		screen.printChar('#');
		while (timer.elapsed() < delay) {

		}
		timer.start();
	}
	setColor(color);
	//left side
	for (int i = BOARD_HEIGHT - 1; i > 0; i--) {
		screen.gotoXY(0, i);
		screen.printChar('#');
		while (timer.elapsed() < delay) {

		}
		timer.start();
	}
	setColor(WHITE);
	screen.printChar('\n');
}
