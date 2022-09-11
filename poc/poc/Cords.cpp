#include "Cords.h"

Cords::Cords(int x, int y)
{
	this->x = x;
	this->y = y;
	this->xMax = x;
	this->yMax = y;
}
bool Cords::isCloseTo(Cords other)
{
	return (this->x <= other.x + CLOSE_PARAM && this->x >= other.x - CLOSE_PARAM) && (this->y <= other.y + CLOSE_PARAM && this->y >= other.y - CLOSE_PARAM);
}
bool Cords::operator==(const Cords& other)
{
	return this->x == other.x && this->y == other.y;
}
Cords::Cords(int x, int y, int xMax, int yMax)
{
	this->x = x;
	this->y = y;
	this->xMax = xMax;
	this->yMax = yMax;
}
bool Cords::isCloseToArea(Cords area)
{
	//inside area
	if (this->x >= area.x && this->y >= area.y && this->x <= area.xMax && this->y <= area.yMax) { return true; }
	//toching sides
	return (this->x >= area.x - CLOSE_PARAM && this->x <= area.xMax + CLOSE_PARAM && this->y >= area.y - CLOSE_PARAM && this->y <= area.yMax + CLOSE_PARAM);
}
bool Cords::isInArea(Cords area)
{
	//inside area
	return this->x >= area.x && this->y >= area.y && this->x <= area.xMax && this->y <= area.yMax;
}
bool Cords::isAreaCloseToArea(Cords area)
{
	if (this->y >= area.y && this->y <= area.yMax || this->yMax >= area.y && this->yMax <= area.yMax)
	{
		if (this->x >= area.x && this->x <= area.xMax || this->xMax >= area.x && this->xMax <= area.xMax) { return true; }
		if (this->xMax == area.x - CLOSE_PARAM) { return true; }
		if (this->x == area.xMax + CLOSE_PARAM) { return true; }
	}
	if (this->x >= area.x && this->x <= area.xMax || this->xMax >= area.x && this->xMax <= area.xMax)
	{
		if (this->y >= area.y && this->y <= area.yMax || this->yMax >= area.y && this->yMax <= area.yMax) { return true; }
		if (this->yMax == area.y - CLOSE_PARAM) { return true; }
		if (this->y == area.yMax + CLOSE_PARAM) { return true; }
	}
	return false;
}



//adds point to area
void Cords::addToArea(Cords point)
{
	if (this->x > point.x) { this->x = point.x; }
	if (this->y > point.y) { this->y = point.y; }
	if (this->xMax < point.x) { this->xMax = point.x; }
	if (this->yMax < point.y) { this->yMax = point.y; }
}
//adds area to area
void Cords::addAreaToArea(Cords area)
{
	if (this->x > area.x) { this->x = area.x; }
	if (this->y > area.y) { this->y = area.y; }
	if (this->xMax < area.xMax) { this->xMax = area.xMax; }
	if (this->yMax < area.yMax) { this->yMax = area.yMax; }
}

bool  Cords::operator<(const Cords& other)
{
	return(this->yMax < other.y - 1) || (this->yMax == other.y -1 && this->xMax < other.x - 1);
}
bool  Cords::operator>(const Cords& other)
{
	return(this->y < other.y + 1) || (this->y == other.y && this->x < other.x + 1);
}