#ifndef TSTACKITEM_H
#define TSTACKITEM_H

#include <memory>
#include "TBinTreeItem.h"

class TStackItem {
public:
	TStackItem(const std::shared_ptr<TBinTreeItem<Figure>>& item);
	friend std::ostream& operator<<(std::ostream& os, const TStackItem& obj);
	std::shared_ptr<TStackItem> SetNext(std::shared_ptr<TStackItem> &next);
	std::shared_ptr<TStackItem> GetNext();
	std::shared_ptr<TBinTreeItem<Figure>> GetFigure() const;

	virtual ~TStackItem();
private:
	std::shared_ptr<TBinTreeItem<Figure>> item;
	std::shared_ptr<TStackItem> next;
};
#endif /* TSTACKITEM_H */