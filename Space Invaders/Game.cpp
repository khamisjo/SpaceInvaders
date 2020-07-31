#include "Game.h"
#include "Gameboard.h"
#include "UserInterface.h"
#include <iostream>
#include <string>
#include "Utilities.h"
#include "Actor.h"
#include "Alien.h"
#include "Hero.h"
#include "Laser.h"
#include <stdlib.h>
using namespace std;


Game::Game(int numberOfStartingAliens, int width, int height)
	: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT)
{
	m_numberOfStartingAliens = numberOfStartingAliens;
}

Game::~Game() {
	delete m_hero;
	//m_aliens.clear();
	m_aliens.~vector();
	m_lasers.~vector();
}

void Game::addLaser(Laser *laser) {
	m_lasers.push_back(laser);
}

void Game::initState() {
	m_hero = new Hero(BOARD_HEIGHT - 2, BOARD_WIDTH / 2);
	//For arrays we have default constructor
	//		BUT using an array of ptrs works since ptrs have a default constructor

	//CHANGE. POORLY MADE ALIENS 
	//CHANGE. POORLY MADE ALIENS 
	//CHANGE. POORLY MADE ALIENS 
	for (int i = 1; i < m_numberOfStartingAliens + 1; i++) {
		int column=1;
		if (column % BOARD_WIDTH == 0) {
			column = ((i * 5) % BOARD_WIDTH) + 1;
		}
		else {
			column = ((i * 5) % BOARD_WIDTH) - 3;
		}
		m_aliens.push_back(new Alien(3, column));
	}
}



void Game::play()
{
	unsigned tempo = 5000;
	char replayKey;
	Timer timePlayed;
	do {

		initState();
		/*
		// init everything
		// every 5s aliens move down a row // if collision: end game
		// if key pressed: perform action
		//	if ARROW_RIGHT: move right
		//	if SPACEBAR: shoot laser
		// every 1s lasers move/collide
		//

		*/


		displayPrompt("Press the Enter key to begin ENTER Space Invaders Lite\n");
		displayPrompt("Press Arrow Up key to shoot\n");
	//	displayPrompt("Press Arrow Left or Arrow Right keys to move");
		waitForEnter();  // [in UserInterface.h]


		m_screen.clear();
		m_board.drawFancyBorder(LIGHTCYAN,m_screen);
		//m_board.drawBorder(m_screen);
		m_board.drawActor(m_screen, m_hero);
		/*m_board.display(m_screen, BOARD_X, BOARD_Y);
		displayStatus();*/

		char keyPressed;
		Timer timer;
		Timer timerDown;
		timer.start();
		timerDown.start();
		while (m_hero->getHP() > 0) {
			m_screen.clear();
			m_board.drawBorder(m_screen);
			m_board.displayStats(m_screen, this);

			if (m_aliens.empty()) {
				tempo -= 600;
				incLevel();
				m_board.nextLevel(m_screen, this);
				for (int i = 1; i < m_numberOfStartingAliens + 1; i++) {
					m_aliens.push_back(new Alien(3, i * 5));
				}
				Timer waitTime;
				while (waitTime.elapsed() < 2000)
				{

				}

				continue;
			}

			if (getCharIfAny(keyPressed)) {
				//If the user moves
				if (keyPressed == ARROW_LEFT || keyPressed == ARROW_RIGHT) {
					m_hero->move(keyPressed);
				}
				//If user shoots laser
				if (keyPressed == ARROW_UP) {
					if (!m_hero->hasShotTooMany()) {
						m_hero->incrementActiveShots();
						m_hero->shootLaser(this);
					}
				}
			}//if(getChar)


			 //Draw Hero
			m_board.drawActor(m_screen, m_hero);

			//CHANGE. POORLY MADE ALIENS 
			//CHANGE. POORLY MADE ALIENS 
			//CHANGE. POORLY MADE ALIENS 

			//Draw aliens
			for (unsigned i = 0; i < m_aliens.size(); i++) {
				Alien * alienToDisplay = m_aliens.at(i);
				/*if (alienToDisplay->isSpecial()) {
					setColor(LIGHTMAGENTA);
				}
				else {
					setColor(GREEN);
				}*/
				m_board.drawActor(m_screen, alienToDisplay);
				setColor(WHITE);
			}

			//aliens shoot
			for (unsigned i = 0; i < m_aliens.size(); i++) {
				Alien *alienToShoot = m_aliens.at(i);
				if (!alienToShoot->hasShotAlready()) {
					alienToShoot->shootLaser(this);
				}
			}

			//Draw lasers if any
			for (unsigned i = 0; i < m_lasers.size(); i++) {
				Laser *laserToDisplay = m_lasers.at(i);
				m_board.drawLaser(m_screen, laserToDisplay);
			}

			//Move aliens left or right
			for (unsigned i = 0; i < m_aliens.size(); i++) {
				Alien *alienToMove = m_aliens.at(i);
				alienToMove->move('&');
			}
			//move aliens down when time elapses
			if (timerDown.elapsed() > tempo)
			{
				for (unsigned i = 0; i < m_aliens.size(); i++) {
					Alien * alien = m_aliens.at(i);
					alien->move('d');
				}
				if (m_aliens.front()->getPosition().row == m_hero->getPosition().row) {
					m_aliens.front()->collide(m_hero);
					m_aliens.clear();
				}
				timerDown.start();
			}

			//Move laser
			for (unsigned i = 0; i < m_lasers.size(); i++) {
				Laser *laserToDisplay = m_lasers.at(i);
				Actor * shooter = laserToDisplay->getShooter();
				bool isFriendly = laserToDisplay->isFriendly();
				bool laserMoved = laserToDisplay->move('^');
				//If this is false we deleted the laserToDisplay
				//The laser in the vector works as a temp. WRONG!!!
				if (!laserMoved) {
					if (isFriendly) {
						shooter->decrementActiveShots();
					}
					else {
						shooter->setHasShotAlready(false);
					}
					m_lasers.erase(m_lasers.begin() + i);
				}
			}

			//Check collisions
			for (unsigned i = 0; i < m_lasers.size(); i++) {
				Laser *laserToCheck = m_lasers.at(i);
				int laserRow = laserToCheck->getPosition().row;
				int laserColumn = laserToCheck->getPosition().column;

				//Check collision between aliens
				for (unsigned j = 0; j < m_aliens.size(); j++) {
					Alien *alienToCheck = m_aliens.at(j);
					int alienRow = alienToCheck->getPosition().row;
					int alienColumn = alienToCheck->getPosition().column;
					if ((abs(alienRow - laserRow) <= 1) && (abs(alienColumn - laserColumn) == 0) && laserToCheck->isFriendly()) {
						//We save hitvalue before collide potentially deletes actor
						int hitvalue = alienToCheck->getHitValue();
						bool isSpecialAlien = alienToCheck->isSpecial();
						laserToCheck->collide(alienToCheck);
						m_hero->decrementActiveShots();
						m_lasers.erase(m_lasers.begin() + i);
						if (alienToCheck->getHP() <= 0) {
							m_aliens.erase(m_aliens.begin() + j);
							if (isSpecialAlien) {
								int randNum = randInt(100);
								if (randNum < 33) {
									m_hero->incrementActorStrength();
								}
								else if (randNum >= 33 && randNum < 66) {
									m_hero->incrementHealth();
								}
								else {
									m_score += hitvalue;
								}
							}
						}
						m_score += hitvalue;
						//cout << "ALIEN HIT" << endl;
					}
				}

				//Check collision with hero
				//Shouldn't use absolute value
				//The logic checks if the laser is about to hit
				//In the beginning when the user or alien just shoots the laser will be close to the person that shot
				//Using absolute value ignores direction
				int heroRow = m_hero->getPosition().row;
				int heroColumn = m_hero->getPosition().column;

				if (abs(heroRow - laserRow <= 1) && abs(heroColumn - laserColumn == 0)) {
					if (!laserToCheck->isFriendly()) {
						//need to set has shot already to false since that controls whether or not an alien shoots
						laserToCheck->getShooter()->setHasShotAlready(false);
						laserToCheck->collide(m_hero);
						m_lasers.erase(m_lasers.begin() + i);
						if (m_hero->getHP() <= 0) {
							if (!m_aliens.empty()) {
								m_aliens.clear();
							}
						}
					}
				}
			}
			while (timer.elapsed() < 100) {
			}
			timer.start();
		}
		m_screen.clear();
		m_board.displayGameOver();
		cin >> replayKey;

	} while (replayKey == 'Y' || replayKey == 'y');
	//system("pause");
	m_screen.clear();
	setTimePlayed(timePlayed.elapsed());
	m_board.displayScore(m_screen, this);
	waitForEnter();
}


void Game::displayPrompt(std::string s)
{
	m_screen.gotoXY(0, PROMPT_Y);
	m_screen.printStringClearLine(s);   // overwrites previous text
	m_screen.refresh();
}


int Game::die(const char * msg)
{
	m_screen.gotoXY(0, 1);
	m_screen.printString("Fatal error: %s\n");
	exit(EXIT_FAILURE);
}
