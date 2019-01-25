#ifndef TBINTREEITEM_H
#define TBINTREEITEM_H

#include "Pentagon.h"
#include "Hexagon.h"
#include "Octagon.h"
#include <memory>

class TBinTreeItem {
public:
	TBinTreeItem(const std::shared_ptr<Figure>& figure);
	TBinTreeItem(const TBinTreeItem& orig);

	friend std::ostream& operator<<(std::ostream& os, const TBinTreeItem& obj);

	std::shared_ptr<TBinTreeItem> SetLeft(std::shared_ptr<TBinTreeItem> left);
	std::shared_ptr<TBinTreeItem> SetRight(std::shared_ptr<TBinTreeItem> right);
	std::shared_ptr<TBinTreeItem> GetLeft();
	std::shared_ptr<TBinTreeItem> GetRight();
	std::shared_ptr<Figure> GetFigure();

	virtual ~TBinTreeItem();
private:
	std::shared_ptr<Figure> figure;

	std::shared_ptr<TBinTreeItem> left;
	std::shared_ptr<TBinTreeItem> right;
};

#endif /* TBINTREEITEM_H */