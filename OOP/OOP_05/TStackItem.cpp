#include "stdafx.h"
#include "TStackItem.h"
#include <iostream>

TStackItem::TStackItem(const std::shared_ptr<TBinTreeItem<Figure>>& item)
{
	this->item = item;
	this->next = nullptr;
	//std::cout << "Stack item: created" << std::endl;
}

std::shared_ptr<TStackItem> TStackItem::SetNext(std::shared_ptr<TStackItem> &next) {
		std::shared_ptr<TStackItem> old = this->next;
		this->next = next;
		return old;
}

std::shared_ptr<TBinTreeItem<Figure>> TStackItem::GetFigure() const {
		return this->item;
}

std::shared_ptr<TStackItem> TStackItem::GetNext() {
		return this->next;
}
	
TStackItem::~TStackItem() {
		//std::cout << "Stack item: deleted" << std::endl;
}
	
std::ostream& operator<<(std::ostream& os, const TStackItem& obj) {
		os << "[" << obj.item << "]" << std::endl;
		return os;
}

/*
#include "Figure.h"
template class TStackItem<Figure>;
template std::ostream& operator<<(std::ostream& os, const TStackItem<Figure>& obj);*/