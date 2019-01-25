#ifndef PENTAGON_H
#define PENTAGON_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Pentagon : public Figure
{
public:
	Pentagon();
	Pentagon(size_t a);
	Pentagon(std::istream &is);

	double Square() override;
	void Print() override;

	virtual ~Pentagon();
private:
	size_t side;
};

#endif //PENTAGON_H