#include "stdafx.h"
#include "TBinTree.h"

template <class T>
TBinTree<T>::TBinTree(): root(nullptr) {
	std::cout << "BinTree: Created" << std::endl;
}

template <class T>
TBinTree<T>::TBinTree(const TBinTree<T>& orig) {
	root = orig.root;
}

/*template <class T>
std::ostream& operator<<(std::ostream& os, const TBinTree<T>& binTree) {
	TBinTreeItem<T> item = binTree.root;

	while (item != nullptr) { //EDIT FOR BINTREE
		os << *item;
		item = item->GetNext(); //EDIT FOR BINTREE
	}

	return os;
}*/

template <class T>
void TBinTree<T>::Insert(std::shared_ptr<T> &figure) {
	if (root == nullptr) {
		std::shared_ptr<TBinTreeItem<T>> newNode(new TBinTreeItem<T>(figure)); // TEST
		root = newNode; //root = std::make_shared<TBinTreeItem<T>>(figure);
	}
	else {
		std::shared_ptr<TBinTreeItem<T>> node = root;
		this->InsertSearch(node, figure);
	}
}

template <class T>
void TBinTree<T>::InsertSearch(std::shared_ptr<TBinTreeItem<T>> node, std::shared_ptr<T> &figure) {
	if (node == NULL) {
		std::shared_ptr<TBinTreeItem<T>> newNode(new TBinTreeItem<T>(figure)); // TEST
		node = newNode;//node = std::make_shared<TBinTreeItem<T>>(figure);
		node->SetLeft(NULL);
		node->SetRight(NULL);
	}
	if (figure->GetSide() < node->GetFigure()->GetSide()) {
		if (node->GetLeft()) {
			this->InsertSearch(node->GetLeft(), figure);
		}
		else {
			std::shared_ptr<TBinTreeItem<T>> newNode(new TBinTreeItem<T>(figure)); // TEST
			node->SetLeft(newNode); //node->SetLeft(std::make_shared<TBinTreeItem<T>>(figure));
		}
	}
	else if (figure->GetSide() > node->GetFigure()->GetSide()) {
		if (node->GetRight()) {
			this->InsertSearch(node->GetRight(), figure);
		}
		else {
			std::shared_ptr<TBinTreeItem<T>> newNode(new TBinTreeItem<T>(figure)); // TEST
			node->SetRight(newNode); //node->SetRight(std::make_shared<TBinTreeItem<T>>(figure));
		}
	}
}

template <class T>
void TBinTree<T>::Print() {
	if (root == nullptr) {
		std::cout << "Tree is Empty" << std::endl;
	}
	else {
		std::shared_ptr<TBinTreeItem<T>> node = root;
		PrintFurther(node);
	}
}

template <class T>
void TBinTree<T>::PrintFurther(std::shared_ptr<TBinTreeItem<T>> node) {
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

template <class T>
bool TBinTree<T>::Empty() {
	return root == nullptr;
}

template <class T>
std::shared_ptr<TBinTreeItem<T>> TBinTree<T>::GetLeast() {
	if (root == NULL)
		std::cout << "BinTree is Empty" << std::endl;
	else
		return this->GetLeastFurther(root);
}

template <class T>
std::shared_ptr<TBinTreeItem<T>> TBinTree<T>::GetLeast(std::shared_ptr<TBinTreeItem<T>> node) {
		return this->GetLeastFurther(node);
}

template <class T>
std::shared_ptr<TBinTreeItem<T>> TBinTree<T>::GetLeastFurther(std::shared_ptr<TBinTreeItem<T>> node) {
	if (node->GetLeft())
		return GetLeastFurther(node->GetLeft());
	else
		//std::cout << "Least Element = ";
		return node;
}

template <class T>
void TBinTree<T>::DeleteItem(size_t elem) {
	std::shared_ptr<TBinTreeItem<T>> node = root;
	if (root == NULL)
		std::cout << "Tree is Empty" << std::endl;
	else if (elem == root->GetFigure()->GetSide()) {
		root = this->DeleteNode(root);
	}
	else {
		this->DeleteSearch(node, elem);
	}
}

template <class T>
void TBinTree<T>::DeleteSearch(std::shared_ptr<TBinTreeItem<T>> node, size_t elem) {
	if (node->GetLeft()) {
		if (elem == node->GetLeft()->GetFigure()->GetSide()) {
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

template <class T>
std::shared_ptr<TBinTreeItem<T>> TBinTree<T>::DeleteNode(std::shared_ptr<TBinTreeItem<T>> node) {
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
		std::shared_ptr<TBinTreeItem<T>> newLeft = node->GetLeft();
		node = this->GetLeast(node->GetRight());
		node->SetLeft(newLeft);
		return node;
	}
}

template <class T>
TIterator<TBinTreeItem<T>, T> TBinTree<T>::begin() {
	return TIterator<TBinTreeItem<T>, T>(this->root);
}

template <class T>
TIterator<TBinTreeItem<T>, T> TBinTree<T>::end() {
	return TIterator<TBinTreeItem<T>, T>(nullptr); //WHY NULLPTR?
}

template <class T>
TBinTree<T>::~TBinTree() {
	//delete root;
	std::cout << "BinTree: Deleted" << std::endl;
}

#include "Figure.h"
template class TBinTree<Figure>;
template std::ostream& operator<<(std::ostream& os, const TBinTree<Figure>& figure);