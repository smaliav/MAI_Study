#ifndef PENTAGON_H
#define PENTAGON_H

#include <cstdlib>
#include <iostream>
#include "Figure.h"

class Pentagon: public Figure {
public:
	Pentagon();
	Pentagon(size_t a);
	Pentagon(const Pentagon& orig);
	Pentagon(std::istream &is); //DO I NEED THIS?

	Pentagon& operator++();

	double Square() override;
	void Print() override;
	size_t GetSide() override;
	
	//friend Pentagon operator+(const Pentagon& left, const Pentagon& right); //

	friend std::ostream& operator<<(std::ostream& os, const Pentagon& obj);
	friend std::istream& operator>>(std::istream& is, Pentagon& obj);

	friend bool operator==(const Pentagon& left, const Pentagon& right);
	friend bool operator<(const Pentagon& left, const Pentagon& right); //DO I NEED THIS?
	friend bool operator>(const Pentagon& left, const Pentagon& right); //DO I NEED THIS?

	Pentagon& operator=(const Pentagon& right);

	virtual ~Pentagon();
private:
	size_t side;
};

#endif /* PENTAGON_H */