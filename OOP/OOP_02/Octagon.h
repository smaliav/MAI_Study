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

	friend std::ostream& operator<<(std::ostream& os, const Octagon& obj);
	friend std::istream& operator>>(std::istream& is, Octagon& obj);
	friend bool operator==(const Octagon& left, const Octagon& right);

	Octagon& operator=(const Octagon& right);

	double Square() override;
	void Print() override;

	virtual ~Octagon();
private:
	size_t side;
};

#endif //OCTAGON_H