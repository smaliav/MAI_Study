#include "figure.h"

void Figure::print(std::ostream & os) {
}

bool Figure::TypedEquals(std::shared_ptr<Figure> other) {
	return (this->Square() == other->Square() && typeid(*this) == typeid(*other.get()));
}

bool Figure::SquareLess(std::shared_ptr<Figure> other) {
	return (this->Square() < other->Square());
}

bool Figure::SquareGreater(std::shared_ptr<Figure> other) {
	return this->Square() > other->Square();
}

std::ostream & operator<<(std::ostream & os, Figure & obj) {
	obj.print(os);
	return os;
}
