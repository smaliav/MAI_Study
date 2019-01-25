#include "stdafx.h"
#include "TBinTreeItem.h"
#include <iostream>

TBinTreeItem::TBinTreeItem(const std::shared_ptr<Figure>& figure) {
	this->figure = figure;
	this->left = nullptr;
	this->right = nullptr;
	//std::cout << "BinTree Item: Created" << std::endl;
}

TBinTreeItem::TBinTreeItem(const TBinTreeItem& orig) {
	this->figure = orig.figure;
	this->left = orig.left;
	this->right = orig.right;
	//std::cout << "BinTree Item: Copied" << std::endl;
}

std::shared_ptr<TBinTreeItem> TBinTreeItem::SetLeft(std::shared_ptr<TBinTreeItem> left) {
	std::shared_ptr<TBinTreeItem> oldLeft = this->left;
	this->left = left;
	return oldLeft;
}

std::shared_ptr<TBinTreeItem> TBinTreeItem::SetRight(std::shared_ptr<TBinTreeItem> right) {
	std::shared_ptr<TBinTreeItem> oldRight = this->right;
	this->right = right;
	return oldRight;
}

std::shared_ptr<Figure> TBinTreeItem::GetFigure() {
	return this->figure;
}

std::shared_ptr<TBinTreeItem> TBinTreeItem::GetLeft() { //TBinTreeItem* TBinTreeItem::GetLeft() {
	return this->left;
}

std::shared_ptr<TBinTreeItem> TBinTreeItem::GetRight() { //TBinTreeItem* TBinTreeItem::GetRight() {
	return this->right;
}

TBinTreeItem::~TBinTreeItem() {
	//std::cout << "BinTree Item: Deleted" << std::endl;
	//delete left;
	//delete right;
}

std::ostream& operator<<(std::ostream& os, const TBinTreeItem& obj) {
	os << "[" << obj.figure << "]" << std::endl;
	return os;
}