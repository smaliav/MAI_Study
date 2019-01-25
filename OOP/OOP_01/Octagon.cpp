#include "stdafx.h"
#include "Octagon.h"
#include <iostream>
#include <cmath>

Octagon::Octagon() : Octagon(0) {}

Octagon::Octagon(size_t a) : side(a) {}

Octagon::Octagon(std::istream &is)
{
	is >> side;
}

double Octagon::Square()
{
	return 2.0*side*side*(1.0 + sqrt(2.0));
}

void Octagon::Print()
{
	std::cout << "Side = " << side << std::endl;
}

Octagon::~Octagon()
{
	std::cout << "Octagon deleted" << std::endl;
}