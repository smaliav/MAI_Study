#include "stdafx.h"
#include "Pentagon.h"
#include <iostream>
#include <cmath>

Pentagon::Pentagon() : Pentagon(0) {}

Pentagon::Pentagon(size_t a) : side(a) {
	//std::cout << "Pentagon: Created" << std::endl;
}

Pentagon::Pentagon(std::istream &is)
{
	std::cout << "Enter Side: ";
	is >> side;
	//std::cout << "Pentagon: Created" << std::endl;
}

Pentagon::Pentagon(const Pentagon& orig) {
	//std::cout << "Pentagon Copy Created" << std::endl;
	side = orig.side;
}

double Pentagon::Square() {
	return side*side / 4.0*sqrt(25.0 + 10.0*sqrt(5.0));
}

size_t Pentagon::GetSide() { //EDIT
	return this->side;
}

void Pentagon::Print() {
	std::cout << "Side = " << side << std::endl;
}

Pentagon& Pentagon::operator=(const Pentagon& right) {

	if (this == &right) return *this;

	//std::cout << "Pentagon Copied" << std::endl;
	side = right.side;

	return *this;
}

Pentagon& Pentagon::operator++() {
	side++;

	return *this;
}

/*Pentagon operator+(const Pentagon& left, const Pentagon& right) { //FIX IT
	return Pentagon(left.side + right.side);
}*/

std::ostream& operator<<(std::ostream& os, const Pentagon& obj) {
	os << obj.side;// << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Pentagon& obj) {
	std::cout << "Enter Side: ";
	is >> obj.side;
	return is;
}

bool operator==(const Pentagon& left, const Pentagon& right) {
	return left.side == right.side;
}

bool operator<(Pentagon& left, Pentagon& right) {
	return left.GetSide() < right.GetSide();
}

bool operator>(Pentagon& left, Pentagon& right) {
	return left.GetSide() > right.GetSide();
}

Pentagon::~Pentagon()
{
	//std::cout << "Pentagon: Deleted" << std::endl;
}