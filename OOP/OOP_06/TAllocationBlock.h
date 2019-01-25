#ifndef TALLOCATIONBLOCK_H
#define TALLOCATIONBLOCK_H

#include <iostream>
#include <cstdlib>
#include "TList.h"

class TAllocationBlock {
public:
	TAllocationBlock(int32_t size, int32_t count);

	void *Allocate();
	void Deallocate(void *pointer);
	bool Empty();
	int32_t Size();

	virtual ~TAllocationBlock();

private:
	char *_used_blocks;
	TList _free_blocks;
};

#endif /* TALLOCATIONBLOCK_H */