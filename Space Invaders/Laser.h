#ifndef LASER_H
#define LASER_H

#include "MovingObject.h"
class Actor;

class Laser : public MovingObject {
public:
	Laser(Actor * actor, bool isFriendly = false);
	virtual ~Laser();
	bool isFriendly() const;
	void collide(Actor* actor);
	Actor * getShooter() const;
	bool move(char key);
private:
	int m_speed;
	int m_strength;
	//true if Hero Shot
	bool m_isFreindly;
	//A pointer to whoever shot the laser
	Actor * m_shooter;
};

#endif // LASER_H
