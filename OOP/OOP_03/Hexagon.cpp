#include "stdafx.h"
#include "Hexagon.h"
#include <iostream>
#include <cmath>

Hexagon::Hexagon() : Hexagon(0) {}

Hexagon::Hexagon(size_t a) : side(a) {
	//std::cout << "Hexagon: Created" << std::endl;
}

Hexagon::Hexagon(std::istream &is)
{
	std::cout << "Enter Side: ";
	is >> side;
	//std::cout << "Hexagon: Created" << std::endl;
}

double Hexagon::Square()
{
	return 3.0 / 2.0*side*side*sqrt(3.0);
}

void Hexagon::Print() {
	std::cout << "Side = " << side << std::endl;
}

size_t Hexagon::GetSide() {
	return this->side;
}

Hexagon& Hexagon::operator=(const Hexagon& right) {

	if (this == &right) return *this;

	//std::cout << "Hexagon Copied" << std::endl;
	side = right.side;

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Hexagon& obj) {
	os << "Side = " << obj.side << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Hexagon& obj) {
	std::cout << "Enter Side: ";
	is >> obj.side;
	return is;
}

bool operator==(const Hexagon& left, const Hexagon& right) {
	return left.side == right.side;
}

Hexagon::~Hexagon()
{
	//std::cout << "Hexagon: Deleted" << std::endl;
}