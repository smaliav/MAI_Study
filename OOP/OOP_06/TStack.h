#ifndef TSTACK_H
#define TSTACK_H

#include "Pentagon.h"
#include "Hexagon.h"
#include "Octagon.h"
#include "TStackItem.h"
#include <memory>

class TStack {
public:
	TStack();

	void Push(std::shared_ptr<TBinTreeItem<Figure>> &&item);
	bool Empty();
	std::shared_ptr<TBinTreeItem<Figure>> Pop();
	friend std::ostream& operator<<(std::ostream& os, const TStack& stack);

	virtual ~TStack();
private:
	std::shared_ptr<TStackItem> head;
};

#endif // TSTACK_H
