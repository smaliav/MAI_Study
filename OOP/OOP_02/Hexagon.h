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

	friend std::ostream& operator<<(std::ostream& os, const Hexagon& obj);
	friend std::istream& operator>>(std::istream& is, Hexagon& obj);
	friend bool operator==(const Hexagon& left, const Hexagon& right);
	
	Hexagon& operator=(const Hexagon& right);

	double Square() override;
	void Print() override;

	virtual ~Hexagon();
private:
	size_t side;
};

#endif //HEXAGON_H