#ifndef TLISTITEM_H
#define TLISTITEM_H

#include <memory>

class TListItem {
public:
	TListItem(void *link);

	TListItem* SetNext(TListItem* next);
	TListItem* GetNext();
	void* GetBlock();

	virtual ~TListItem();
private:
	void* link;
	TListItem* next;
};

#endif /* TLISTITEM_H */