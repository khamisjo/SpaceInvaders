#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H
#include "Utilities.h"


class Board;

struct Position {
	Position(int row, int column) {
		this->row = row;
		this->column = column;
	}
	int row, column;
};

class MovingObject {
public:
	MovingObject(char symbol, int row, int position);
	virtual ~MovingObject();
	Position getPosition() const;
	void setPosition(int row, int column);
	char getSymbol() const;
	virtual bool move(char key) = 0;
private:
	char m_symbol;
	Position m_p;
	Board* m_board;
};
#endif // MOVING_OBJECT_H