#include "stdafx.h"
#include "TStack.h"

TStack::TStack() : head(nullptr) {
}

std::ostream& operator<<(std::ostream& os, const TStack& stack) {
	std::shared_ptr<TStackItem> item = stack.head;
	while (item != nullptr) {
		os << *item;
		item = item->GetNext();
	}
	return os;
}

void TStack::Push(std::shared_ptr<TBinTreeItem<Figure>> &&item) {
	std::shared_ptr<TStackItem> other(new TStackItem(item));
	other->SetNext(head);
	head = other;
}

bool TStack::Empty() {
	return head == nullptr;
}

std::shared_ptr<TBinTreeItem<Figure>> TStack::Pop() {
	std::shared_ptr<TBinTreeItem<Figure>> result;
	if (head != nullptr) {
		result = head->GetFigure();
		head = head->GetNext();
	}
	return result;
}

TStack::~TStack() {
}

/*#include "Figure.h"
template class TStack<Figure>;
template std::ostream& operator<<(std::ostream& os, const TStack<Figure>& stack);*/