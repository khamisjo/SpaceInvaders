#include "Laser.h"
#include "Actor.h"
#include "Utilities.h"

Laser::Laser(Actor *actor, bool isFriendly) :
	MovingObject('|',
		isFriendly ? actor->getPosition().row - 1 : actor->getPosition().row + 1, actor->getPosition().column), m_shooter(actor) {
	m_isFreindly = isFriendly;
	if (m_isFreindly) {
		m_speed = 2;
	}
	else {
		m_speed = 1;
	}
	m_strength = actor->getStrength();
}
Laser::~Laser() {
	//Error is thrownwhen I delete
	//delete this;
}

void Laser::collide(Actor* actor) {
	actor->takeDamage(m_strength);
	if (actor->getHP() <= 0) {
		delete actor;
	}
	delete this;
}


bool Laser::isFriendly() const {
	return m_isFreindly;
}

bool Laser::move(char key) {
	int row = getPosition().row;
	int column = getPosition().column;
	if (m_isFreindly) {
		if (row > 0 && row < BOARD_HEIGHT - 2) {
			setPosition(row - m_speed, column);
			return true;
		}
	}
	else if (row > 0 && row < BOARD_HEIGHT - 2) {
		setPosition(row + m_speed, column);
		return true;
	}
	delete this;
	return false;
}

Actor * Laser::getShooter() const {
	return m_shooter;
}