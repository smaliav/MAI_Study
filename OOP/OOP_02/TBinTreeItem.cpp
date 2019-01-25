#include "stdafx.h"
#include "TBinTreeItem.h"
#include <iostream>

TBinTreeItem::TBinTreeItem(const Pentagon& pentagon) {
	this->pentagon = pentagon;
	this->left = nullptr;
	this->right = nullptr;
	//std::cout << "BinTree Item: Created" << std::endl;
}

TBinTreeItem::TBinTreeItem(const TBinTreeItem& orig) {
	this->pentagon = orig.pentagon;
	this->left = orig.left;
	this->right = orig.right;
	//std::cout << "BinTree Item: Copied" << std::endl;
}

TBinTreeItem* TBinTreeItem::SetLeft(TBinTreeItem* left) {
	TBinTreeItem* oldLeft = this->left;
	this->left = left;
	return oldLeft;
}

TBinTreeItem* TBinTreeItem::SetRight(TBinTreeItem* right) {
	TBinTreeItem* oldRight = this->right;
	this->right = right;
	return oldRight;
}

Pentagon TBinTreeItem::GetPentagon() {
	return this->pentagon;
}

TBinTreeItem* TBinTreeItem::GetLeft() {
	return this->left;
}

TBinTreeItem* TBinTreeItem::GetRight() {
	return this->right;
}

TBinTreeItem::~TBinTreeItem() {
	//std::cout << "BinTree Item: Deleted" << std::endl;
	delete left;
	delete right;
}

std::ostream& operator<<(std::ostream& os, const TBinTreeItem& obj) {
	os << "[" << obj.pentagon << "]" << std::endl;
	return os;
}