#include "MovingObject.h"
#include "Utilities.h"
#include "Assert.h"

//Asserts are there to throw an error if we try to make an object that is outside the screen size
MovingObject::MovingObject(char symbol, int row, int column) : m_symbol(symbol), m_p(row, column) {
	assert(row <= BOARD_HEIGHT && row >= 0);
	assert(column <= BOARD_WIDTH && column >= 0);
}


MovingObject::~MovingObject() {

}

Position MovingObject::getPosition() const {
	return m_p;
}


char MovingObject::getSymbol() const {
	return m_symbol;
}

void MovingObject::setPosition(int row, int column) {
	Position p(row, column);
	m_p.row = row;
	m_p.column = column;
	//m_p = p;
}