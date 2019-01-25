#include "stdafx.h"
#include "TAllocationBlock.h"

TAllocationBlock::TAllocationBlock(int32_t size, int32_t count) {
	_used_blocks = (char *)malloc(size * count);

	for (int32_t i = 0; i < count; ++i) {
		void *ptr = (void *)malloc(sizeof(void *)); // Зачем мы приводим к типу?
		ptr = _used_blocks + i * size;
		_free_blocks.AddLast(ptr);
	}
	std::cout << "Allocator: Constructor" << std::endl;
}

void *TAllocationBlock::Allocate() {
	if (!_free_blocks.Empty()) {
		void *res = _free_blocks.GetBlock();
		int first = 1;					// FIX 
		_free_blocks.DelElement(first); // FIX _free_blocks.DelElement(1);
		std::cout << "Allocator: Allocate" << std::endl;
		return res;
	}
	//else {
	//	throw std::bad_alloc();
	//}
}

void TAllocationBlock::Deallocate(void *ptr) {
	_free_blocks.AddFirst(ptr);
	std::cout << "Allocator: Deallocate" << std::endl;
}

bool TAllocationBlock::Empty() {
	return _free_blocks.Empty();
}

int32_t TAllocationBlock::Size() {
	return _free_blocks.Length();
}

TAllocationBlock::~TAllocationBlock() {
	while (!_free_blocks.Empty()) {
		int first = 1;					// FIX
		_free_blocks.DelElement(first);	// FIX _free_blocks.DelElement(1);
	}
	free(_used_blocks);
	//delete _free_blocks;
	//delete _used_blocks;
}