#include "Cords.h"

Cords::Cords(int x, int y)
{
	this->x = x;
	this->y = y;
}
bool Cords::isCloseTo(Cords other)
{
	return (this->x <= other.x + CLOSE_PARAM && this->x >= other.x - CLOSE_PARAM) && (this->y <= other.y + CLOSE_PARAM && this->y >= other.y - CLOSE_PARAM);
}
bool Cords::operator==(const Cords& other)
{
	return this->x == other.x && this->y == other.y;
}
Cords::Cords(int x, int y, int xRight, int yBottom)
{
	this->x = x;
	this->y = y;
	this->xRight = xRight;
	this->yBottom = yBottom;
}
