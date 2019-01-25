#ifndef TBINTREEITEM_H
#define TBINTREEITEM_H

#include "Pentagon.h"
#include "Hexagon.h"
#include "Octagon.h"
#include "TAllocationBlock.h"
#include <memory>

template <class T>
class TBinTreeItem {
public:
	TBinTreeItem(const std::shared_ptr<T>& figure);
	TBinTreeItem(const TBinTreeItem<T>& orig);

	template <class A> friend std::ostream& operator<<(std::ostream& os, const TBinTreeItem<A>& obj);

	std::shared_ptr<TBinTreeItem<T>> SetLeft(std::shared_ptr<TBinTreeItem<T>> left);
	std::shared_ptr<TBinTreeItem<T>> SetRight(std::shared_ptr<TBinTreeItem<T>> right);
	std::shared_ptr<TBinTreeItem<T>> GetLeft();
	std::shared_ptr<TBinTreeItem<T>> GetRight();
	std::shared_ptr<T> GetFigure();
	void * operator new (size_t size);
	void operator delete(void *p);

	virtual ~TBinTreeItem();
private:
	std::shared_ptr<T> figure;

	std::shared_ptr<TBinTreeItem<T>> left;
	std::shared_ptr<TBinTreeItem<T>> right;

	static TAllocationBlock bintreeitem_allocator;
};

#endif /* TBINTREEITEM_H */