#ifndef ACTOR_H
#define ACTOR_H

#include "MovingObject.h"

class Game;
class Gameboard;
class Actor : public MovingObject {

public:
	Actor(char symbol, int hp, int strength, int row, int column);
	virtual ~Actor();

	int getHP() const;
	void setHP(int hp);
	virtual void shootLaser(Game *game) = 0;
	void takeDamage(int dmg);
	int getStrength() const;
	bool hasShotAlready() const;
	void setHasShotAlready(bool hasShot);
	virtual bool move(char key) = 0;
	void incrementActorStrength() { m_strength++; }
	void incrementHealth() { m_hp++; }
	bool hasShotTooMany() const { return m_activeBullets >= 3; }
	void incrementActiveShots() { m_activeBullets++; }
	void decrementActiveShots() { if (m_activeBullets >= 0) m_activeBullets--; }

private:
	int m_hp;
	int m_strength;
	int m_activeBullets = 0;
	//Keeps track of whether or not a user has shot (For aliens)
	bool m_HasShotAlready;
};
#endif // ACTOR_H
