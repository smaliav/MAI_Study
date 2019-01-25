#ifndef HEXAGON_H
#define HEXAGON_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Hexagon : public Figure
{
public:
	Hexagon();
	Hexagon(size_t a);
	Hexagon(std::istream &is);

	double Square() override;
	void Print() override;

	virtual ~Hexagon();
private:
	size_t side;
};

#endif //HEXAGON_H