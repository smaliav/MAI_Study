#include "stdafx.h"
#include "Pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon() : Pentagon(0) {}

Pentagon::Pentagon(size_t a) : side(a) {}

Pentagon::Pentagon(std::istream &is)
{
	is >> side;
}

double Pentagon::Square()
{
	return side*side / 4.0*sqrt(25.0 + 10.0*sqrt(5.0));
}

void Pentagon::Print()
{
	std::cout << "Side = " << side << std::endl;
}

Pentagon::~Pentagon()
{
	std::cout << "Pentagon deleted" << std::endl;
}