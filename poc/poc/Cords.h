#pragma once
#define CLOSE_PARAM 1
#include <iostream>
class Cords
{
public:
	Cords(int x,int y);
	Cords(int x, int y, int xRight, int yBottom);
	int x;
	int y;
	int xRight;
	int yBottom;
	bool operator==(const Cords& other);
	bool isCloseTo(Cords other);

private:
	
};



