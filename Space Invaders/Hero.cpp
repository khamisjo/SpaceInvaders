#include "Hero.h"
#include "UserInterface.h"
#include <iostream>
#include "Game.h"
#include "Laser.h"
#include "Utilities.h"
using namespace std;
Hero::Hero(int row, int column) :Actor('^', 10, 1, row, column) {
}

Hero::~Hero() {

}

void Hero::shootLaser(Game*game)
{
	game->addLaser(new Laser(this, true));
}

//REMEMBER:
//[0,26]
//[1,25]
//width of the border is 30 but the way it was itterated made it go from [0,SIZE -1]
//So we want the hero to only be able to go to [1,SIZE - 2]
bool Hero::move(char key) {
	int row = this->getPosition().row;
	int column = this->getPosition().column;
	//We want it to not move if user is at position 1 or 28
	if (column <= BOARD_WIDTH - 2 && column >= 1) {
		switch (key) {
		case ARROW_LEFT:
			if (column > 1) {
				cout << "LEFT" << endl;
				this->setPosition(row, column - 1);
			}
			break;
		case ARROW_RIGHT:
			if (column < BOARD_WIDTH - 2) {
				cout << "RIGHT" << endl;
				this->setPosition(row, column + 1);
			}
			break;
		default:
			break;
		}
	}
	else {
		return false;
		row = this->getPosition().row;
		column = this->getPosition().column;
	}
}
