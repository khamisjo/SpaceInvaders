#include "Actor.h"
#include "Gameboard.h"

Actor::Actor(char symbol, int hp, int strength, int row, int column) : MovingObject(symbol, row, column) {
	m_strength = strength;
	m_hp = hp;
	m_HasShotAlready = false;
}

Actor::~Actor() {

}

int Actor::getStrength() const {
	return m_strength;
}

int Actor::getHP() const {
	return m_hp;
}


void Actor::setHP(int hp) {
	m_hp = hp;
}

void Actor::shootLaser(Game*game) {
	Position p = this->getPosition();
	//board.addLaser(getPosition().row,getPosition().column);
}

void Actor::setHasShotAlready(bool hasShot) {
	m_HasShotAlready = hasShot;
}

bool Actor::hasShotAlready() const {
	return m_HasShotAlready;
}
void Actor::takeDamage(int dmg) {
	m_hp -= dmg;
}

