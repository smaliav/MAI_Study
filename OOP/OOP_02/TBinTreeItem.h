#ifndef TBINTREEITEM_H
#define TBINTREEITEM_H

#include "Pentagon.h"

class TBinTreeItem {
public:
	TBinTreeItem(const Pentagon& pentagon);
	TBinTreeItem(const TBinTreeItem& orig);

	friend std::ostream& operator<<(std::ostream& os, const TBinTreeItem& obj);

	TBinTreeItem* SetLeft(TBinTreeItem* left);
	TBinTreeItem* SetRight(TBinTreeItem* right);
	TBinTreeItem* GetLeft();
	TBinTreeItem* GetRight();
	Pentagon GetPentagon();

	virtual ~TBinTreeItem();
private:
	Pentagon pentagon;
	TBinTreeItem *left;
	TBinTreeItem *right;
};

#endif /* TBINTREEITEM_H */