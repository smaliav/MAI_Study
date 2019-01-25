#ifndef OCTAGON_H
#define OCTAGON_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Octagon : public Figure
{
public:
	Octagon();
	Octagon(size_t a);
	Octagon(std::istream &is);

	double Square() override;
	void Print() override;

	virtual ~Octagon();
private:
	size_t side;
};

#endif //OCTAGON_H