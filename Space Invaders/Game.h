#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Gameboard.h"
#include "UserInterface.h"
using namespace std;


class Board;
class Hero;
class Alien;
class Laser;

class Game {
public:
	Game(int numberOfStartingAliens, int width, int height);
	~Game();
	void play();
	bool playOneLevel();
	void displayPrompt(std::string s);
	void displayStatus();
	void initState();
	void addLaser(Laser*laser);
	int die(const char * msg);
	int getLevel() const { return m_level; }
	void incLevel() { m_level++; m_numberOfStartingAliens++; }
	int getScore() const { return m_score; }
	void setScore(int scoreToAdd) { m_score += scoreToAdd; }
	unsigned getTimePlayed() const { return m_timePlayed; }
	void setTimePlayed(unsigned timePlayed) { m_timePlayed = timePlayed; }
	Hero * getHero() { return m_hero; }

private:
	Gameboard m_board;
	Screen  m_screen;
	Hero* m_hero;
	vector<Alien*> m_aliens;
	vector<Laser*> m_lasers;
	int m_level = 1;
	int m_numberOfStartingAliens;
	int m_score = 0;
	unsigned m_timePlayed = 0;
};

#endif // GAME_H
