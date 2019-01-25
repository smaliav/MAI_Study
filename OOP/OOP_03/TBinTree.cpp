#include "stdafx.h"
#include "TBinTree.h"

TBinTree::TBinTree(): root(nullptr) {
	//std::cout << "BinTree: Created" << std::endl;
}

TBinTree::TBinTree(const TBinTree& orig) {
	root = orig.root;
}

/*std::ostream& operator<<(std::ostream& os, const TBinTree& binTree) {
	TBinTreeItem *item = binTree.root;

	while (item != nullptr) { //EDIT FOR BINTREE
		os << *item;
		item = item->GetNext(); //EDIT FOR BINTREE
	}

	return os;
}*/

void TBinTree::Insert(std::shared_ptr<Figure> &figure) {
	if (root == nullptr) {
		root = std::make_shared<TBinTreeItem>(figure);
	}
	else {
		std::shared_ptr<TBinTreeItem> node = root;
		this->InsertSearch(node, figure);
	}
}

void TBinTree::InsertSearch(std::shared_ptr<TBinTreeItem> node, std::shared_ptr<Figure> &figure) {
	if (node == NULL) {
		node = std::make_shared<TBinTreeItem>(figure);
		node->SetLeft(NULL);
		node->SetRight(NULL);
	}
	if (figure->GetSide() < node->GetFigure()->GetSide()) {
		if (node->GetLeft()) {
			this->InsertSearch(node->GetLeft(), figure);
		}
		else {
			node->SetLeft(std::make_shared<TBinTreeItem>(figure));
		}
	}
	else if (figure->GetSide() > node->GetFigure()->GetSide()) {
		if (node->GetRight()) {
			this->InsertSearch(node->GetRight(), figure);
		}
		else {
			node->SetRight(std::make_shared<TBinTreeItem>(figure));
		}
	}
}

void TBinTree::Print() {
	if (root == nullptr) {
		std::cout << "Tree is Empty" << std::endl;
	}
	else {
		std::shared_ptr<TBinTreeItem> node = root;
		PrintFurther(node);
	}
}

void TBinTree::PrintFurther(std::shared_ptr<TBinTreeItem> node) {
	static int l = 0;
	l++;
	if (node)
	{
		this->PrintFurther(node->GetRight());
		for (int i = 0; i < l; i++)
			std::cout << "    ";
		std::cout << "\\__" << node->GetFigure()->GetSide();
		std::cout << "(" <<node->GetFigure()->Square() << ")" << "\n";
		this->PrintFurther(node->GetLeft());
	}
	l--;
}

bool TBinTree::Empty() {
	return root == nullptr;
}

std::shared_ptr<TBinTreeItem> TBinTree::GetLeast() {
	if (root == NULL)
		std::cout << "BinTree is Empty" << std::endl;
	else
		return this->GetLeastFurther(root);
}

std::shared_ptr<TBinTreeItem> TBinTree::GetLeast(std::shared_ptr<TBinTreeItem> node) {
		return this->GetLeastFurther(node);
}

std::shared_ptr<TBinTreeItem> TBinTree::GetLeastFurther(std::shared_ptr<TBinTreeItem> node) {
	if (node->GetLeft())
		return GetLeastFurther(node->GetLeft());
	else
		//std::cout << "Least Element = ";
		return node;
}

void TBinTree::DeleteItem(size_t elem) {
	std::shared_ptr<TBinTreeItem> node = root;
	if (root == NULL)
		std::cout << "Tree is Empty" << std::endl;
	else if (elem == root->GetFigure()->GetSide()) {
		root = this->DeleteNode(root);
	}
	else {
		this->DeleteSearch(node, elem);
	}
}

void TBinTree::DeleteSearch(std::shared_ptr<TBinTreeItem> node, size_t elem) {
	if (node->GetLeft()) {
		if (elem == node->GetLeft()->GetFigure()->GetSide()) {
			//this->DeleteNode(node->GetLeft(), elem);
			node->SetLeft(this->DeleteNode(node->GetLeft()));
		}
		else {
			this->DeleteSearch(node->GetLeft(), elem);
		}
	}
	if (node->GetRight()) {
		if (elem == node->GetRight()->GetFigure()->GetSide()) {
			node->SetRight(this->DeleteNode(node->GetRight()));
		}
		else {
			this->DeleteSearch(node->GetRight(), elem);
		}
	}
}

std::shared_ptr<TBinTreeItem> TBinTree::DeleteNode(std::shared_ptr<TBinTreeItem> node) { //TBinTreeItem* TBinTree::DeleteNode(TBinTreeItem* node) {
	if (!(node->GetLeft() || node->GetRight())) {
		//delete node;
		node = nullptr;
		return node;
	}
	else if (node->GetLeft() == nullptr && node->GetRight() != nullptr) {
		node = node->GetRight();
		return node;
	}
	else if (node->GetLeft() != nullptr && node->GetRight() == nullptr) {
		node = node->GetLeft();
		return node;
	}
	else {
		std::shared_ptr<TBinTreeItem> newLeft = node->GetLeft(); //TBinTreeItem* newLeft = node->GetLeft();
		node = this->GetLeast(node->GetRight());
		node->SetLeft(newLeft);
		return node;
	}
}

TBinTree::~TBinTree() {
	//delete root;
	std::cout << "BinTree: Deleted" << std::endl;
}