#include "stdafx.h"
#include "Octagon.h"
#include <iostream>
#include <cmath>

Octagon::Octagon() : Octagon(0) {}

Octagon::Octagon(size_t a) : side(a) {
	//std::cout << "Octagon: Created" << std::endl;
}

Octagon::Octagon(std::istream &is)
{
	std::cout << "Enter Side: ";
	is >> side;
	//std::cout << "Octagon: Created" << std::endl;
}

double Octagon::Square()
{
	return 2.0*side*side*(1.0 + sqrt(2.0));
}

void Octagon::Print() {
	std::cout << "Side = " << side << std::endl;
}

Octagon& Octagon::operator=(const Octagon& right) {

	if (this == &right) return *this;

	//std::cout << "Octagon Copied" << std::endl;
	side = right.side;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Octagon& obj) {
	os << "Side = " << obj.side << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Octagon& obj) {
	std::cout << "Enter Side: ";
	is >> obj.side;
	return is;
}

bool operator==(const Octagon& left, const Octagon& right) {
	return left.side == right.side;
}

Octagon::~Octagon()
{
	//std::cout << "Octagon: Deleted" << std::endl;
}