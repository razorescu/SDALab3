#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
	//TODO - Representation

	MultiMapIterator(const MultiMap& c);
	int current, currentNode;

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void previous();
	void first();
	void last();
};

