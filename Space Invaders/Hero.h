#ifndef HERO_H
#define HERO_H

#include "Actor.h"

class Hero : public Actor {
public:
	Hero(int row, int column);
	virtual ~Hero();
	void shootLaser(Game*game);
	bool move(char key);
	void incrementHeroStrength() {  }

};

#endif // HERO_H
