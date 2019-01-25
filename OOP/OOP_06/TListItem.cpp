#include "stdafx.h"
#include "TListItem.h"
#include <iostream>

TListItem::TListItem(void* link) {
	this->link = link;
	this->next = nullptr;
	//std::cout << "List item: created" << std::endl;
}

TListItem* TListItem::SetNext(TListItem* next) {
	TListItem* old = this->next;
	this->next = next;
	return old;
}

TListItem* TListItem::GetNext() {
	return this->next;
}

void* TListItem::GetBlock() {
	return this->link;
}

TListItem::~TListItem() {
}