#pragma once
#define CLOSE_PARAM 1
#include <iostream>
class Cords
{
public:
	Cords(int x,int y);
	Cords(int x, int y, int xMax, int yMax);
	int x;
	int y;
	int xMax;
	int yMax;
	bool operator==(const Cords& other);
	bool operator<(const Cords& other);
	bool operator>(const Cords& other);
	bool isCloseTo(Cords other);
	bool isCloseToArea(Cords area);
	bool isInArea(Cords area);
	bool isAreaCloseToArea(Cords area);
	void addToArea(Cords point);
	void addAreaToArea(Cords area);

private:
	
};



