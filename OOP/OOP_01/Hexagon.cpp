#include "stdafx.h"
#include "Hexagon.h"
#include <iostream>
#include <cmath>

Hexagon::Hexagon() : Hexagon(0) {}

Hexagon::Hexagon(size_t a) : side(a) {}

Hexagon::Hexagon(std::istream &is)
{
	is >> side;
}

double Hexagon::Square()
{
	return 3.0 / 2.0*side*side*sqrt(3.0);
}

void Hexagon::Print()
{
	std::cout << "Side = " << side << std::endl;
}

Hexagon::~Hexagon()
{
	std::cout << "Hexagon deleted" << std::endl;
}