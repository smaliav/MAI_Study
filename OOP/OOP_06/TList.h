#ifndef TLIST_H
#define TLIST_H

#include "TListItem.h"
#include <memory>
#include <iostream>

class TList {
public:
	TList();

	int Length();

	void AddFirst(void *link);
	void Insert(int index, void *link);
	void AddLast(void *link);
	bool Empty();
	void DelElement(int &index);
	void EraseList();

	void* GetBlock();

	virtual ~TList();
private:

	TListItem* first;
};

#endif /* TLIST_H */