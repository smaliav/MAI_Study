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

void TBinTree::Insert(Pentagon &pentagon) {
	if (root == nullptr) {
		root = new TBinTreeItem(pentagon);
	}
	else {
		TBinTreeItem *node = root;
		this->InsertSearch(node, pentagon);
	}
}

void TBinTree::InsertSearch(TBinTreeItem* node, Pentagon &pentagon) {
	if (node == NULL) {
		node = new TBinTreeItem(pentagon);
		node->SetLeft(NULL);
		node->SetRight(NULL);
	}
	if (pentagon.GetSide() < node->GetPentagon().GetSide()) {
		if (node->GetLeft()) {
			this->InsertSearch(node->GetLeft(), pentagon);
		}
		else {
			node->SetLeft(new TBinTreeItem(pentagon));
		}
	}
	else if (pentagon.GetSide() > node->GetPentagon().GetSide()) {
		if (node->GetRight()) {
			this->InsertSearch(node->GetRight(), pentagon);
		}
		else {
			node->SetRight(new TBinTreeItem(pentagon));
		}
	}
}

void TBinTree::Print() {
	if (root == nullptr) {
		std::cout << "Tree is Empty" << std::endl;
	}
	else {
		TBinTreeItem* node = root;
		PrintFurther(node);
	}
}

void TBinTree::PrintFurther(TBinTreeItem* node) {
	static int l = 0;
	l++;
	if (node)
	{
		this->PrintFurther(node->GetRight());
		for (int i = 0; i < l; i++)
			std::cout << "    ";//printf("    ");
		std::cout << "\\__" << node->GetPentagon();// << "\n";  //printf("\\__%c\n", t->data);
		std::cout << "(" <<node->GetPentagon().Square() << ")" << "\n";
		this->PrintFurther(node->GetLeft());
	}
	l--;
}

bool TBinTree::Empty() {
	return root == nullptr;
}

TBinTreeItem* TBinTree::GetLeast() {
	if (root == NULL)
		std::cout << "BinTree is Empty" << std::endl;
	else
		return this->GetLeastFurther(root);
}

TBinTreeItem* TBinTree::GetLeast(TBinTreeItem* node) {
		return this->GetLeastFurther(node);
}

TBinTreeItem* TBinTree::GetLeastFurther(TBinTreeItem* node) {
	if (node->GetLeft())
		return GetLeastFurther(node->GetLeft());
	else
		//std::cout << "Least Element = ";
		return node;
}

void TBinTree::DeleteItem(size_t elem) {
	TBinTreeItem* node = root;
	if (root == NULL)
		std::cout << "Tree is Empty" << std::endl;
	else if (elem == root->GetPentagon().GetSide()) {
		root = this->DeleteNode(root);
	}
	else {
		this->DeleteSearch(node, elem);
	}
}

void TBinTree::DeleteSearch(TBinTreeItem* node, size_t elem) {
	if (node->GetLeft()) {
		if (elem == node->GetLeft()->GetPentagon().GetSide()) {
			//this->DeleteNode(node->GetLeft(), elem);
			node->SetLeft(this->DeleteNode(node->GetLeft()));
		}
		else {
			this->DeleteSearch(node->GetLeft(), elem);
		}
	}
	if (node->GetRight()) {
		if (elem == node->GetRight()->GetPentagon().GetSide()) {
			node->SetRight(this->DeleteNode(node->GetRight()));
		}
		else {
			this->DeleteSearch(node->GetRight(), elem);
		}
	}
}

TBinTreeItem* TBinTree::DeleteNode(TBinTreeItem* node) {
	if (!(node->GetLeft() || node->GetRight())) {
		delete node;
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
		TBinTreeItem* newLeft = node->GetLeft();
		node = this->GetLeast(node->GetRight());
		node->SetLeft(newLeft);
		return node;
	}
}

TBinTree::~TBinTree() {
	delete root;
	//std::cout << "BinTree: Deleted" << std::endl;
}