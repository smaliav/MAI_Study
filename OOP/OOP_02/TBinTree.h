#ifndef TBINTREE_H
#define TBINTREE_H

#include "Pentagon.h"
#include "TBinTreeItem.h"

class TBinTree {
public:
	TBinTree();
	TBinTree(const TBinTree& orig);

	void Insert(Pentagon &pentagon);
	bool Empty();
	void Print();
	TBinTreeItem* GetLeast();
	TBinTreeItem* GetLeast(TBinTreeItem* node);
	void DeleteItem(size_t elem);
	//friend std::ostream& operator<<(std::ostream& os, const TBinTree& binTree); //EDIT
	
	virtual ~TBinTree();
private:
	TBinTreeItem *root;

	void InsertSearch(TBinTreeItem* node, Pentagon &pentagon);
	void PrintFurther(TBinTreeItem* node);
	TBinTreeItem* GetLeastFurther(TBinTreeItem* node);
	void DeleteSearch(TBinTreeItem* node, size_t elem);
	TBinTreeItem* DeleteNode(TBinTreeItem* node);
};

#endif /* TBINTREE_H */