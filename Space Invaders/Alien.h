#ifndef ALIEN_H
#define ALIEN_H

#include "Actor.h"

class Hero;

class Alien : public Actor {
public:
	Alien(int row, int column);
	virtual ~Alien();
	void collide(Hero* hero);
	bool move(char key);
	void shootLaser(Game*game);
	int getHitValue() const { return m_hitValue; }
	bool isSpecial() { return m_isSpecial; }
private:
	int m_direction;
	int m_hitValue = 50;
	bool m_isSpecial = false;
};

#endif // ALIEN_H
