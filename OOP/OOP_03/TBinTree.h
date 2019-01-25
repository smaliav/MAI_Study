#ifndef TBINTREE_H
#define TBINTREE_H

#include "Pentagon.h"
#include "Hexagon.h"
#include "Pentagon.h"
#include "TBinTreeItem.h"
#include <memory>

class TBinTree {
public:
	TBinTree();
	TBinTree(const TBinTree& orig);

	void Insert(std::shared_ptr<Figure>& figure);
	bool Empty();
	void Print();
	std::shared_ptr<TBinTreeItem> GetLeast();
	std::shared_ptr<TBinTreeItem> GetLeast(std::shared_ptr<TBinTreeItem> node);
	void DeleteItem(size_t elem);
	//friend std::ostream& operator<<(std::ostream& os, const TBinTree& binTree); //EDIT
	
	virtual ~TBinTree();
private:
	std::shared_ptr<TBinTreeItem> root;

	void InsertSearch(std::shared_ptr<TBinTreeItem> node, std::shared_ptr<Figure>& figure);
	void PrintFurther(std::shared_ptr<TBinTreeItem> node);
	std::shared_ptr<TBinTreeItem> GetLeastFurther(std::shared_ptr<TBinTreeItem> node);
	void DeleteSearch(std::shared_ptr<TBinTreeItem> node, size_t elem);
	std::shared_ptr<TBinTreeItem> DeleteNode(std::shared_ptr<TBinTreeItem> node);
};

#endif /* TBINTREE_H */