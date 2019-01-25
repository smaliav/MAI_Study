#include "stdafx.h"
#include "TList.h"

TList::TList() {
	first = nullptr;
}

int TList::Length() {
	int i = 0;
	TListItem* item = this->first;
	while (item != nullptr)
	{
		item = item->GetNext();
		i++;
	}
	return i;
}

void TList::AddFirst(void* link) {
	TListItem *other = new TListItem(link);

	other->SetNext(first);
	first = other;
}

void TList::Insert(int index, void *link) {
	TListItem *iter = this->first;
	TListItem *other = new TListItem(link);
	if (index == 1) {
		other->SetNext(iter);
		this->first = other;
	}
	else {
		if (index <= this->Length()) {
			int i = 1;
			for (i = 1; i < index - 1; ++i) {
				iter = iter->GetNext();
			}
			other->SetNext(iter->GetNext());
			iter->SetNext(other);
		}
		else {
			std::cout << "error" << std::endl;
		}
	}
}

void TList::AddLast(void *link) {
	TListItem *other = new TListItem(link);
	TListItem *iter = this->first;
	if (first != nullptr) {
		while (iter->GetNext() != nullptr) {
			iter = iter->SetNext(iter->GetNext());
		}
		iter->SetNext(other);// little bit strange
		other->SetNext(nullptr);
	}
	else {
		first = other;
	}
}

bool TList::Empty() {
	return first == nullptr;
}

void TList::DelElement(int &index)
{
	TListItem *iter = this->first;
	//std::shared_ptr<TListItem> other = std::make_shared<TListItem>(figure);
	//int i = 0;
	if (index <= this->Length()) {
		if (index == 1) {
			this->first = iter->GetNext();
		}
		else {
			int i = 1;
			for (i = 1; i < index - 1; ++i) {
				iter = iter->GetNext();
			}
			iter->SetNext(iter->GetNext()->GetNext());
		}

	}
	else {
		std::cout << "error" << std::endl;
	}
}

void TList::EraseList() {
	first = nullptr;
}

void* TList::GetBlock() { // TESTING
	return this->first->GetBlock();
}

TList::~TList() {
	//std::cout << "List deleted!" << std::endl;
	delete first;
}