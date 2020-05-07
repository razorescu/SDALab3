#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	/*
	If multimap empty, sets current indexes to -1
	otherwise, sets the key index to the head of the dlla and the key's values index to the head of the key's values' dlla
	O(1) all cases
	*/
	if (c.length > 0) {
		currentNode = col.dlla.head;
		current = col.dlla.nodes[currentNode].values.head;
	}
	else {
		current = -1; currentNode = -1;
	}
}

TElem MultiMapIterator::getCurrent() const{
	/*
	Returns a TElem Pair of TKey and TValue
	O(1) all cases
	*/
	TElem rez;
	rez.first = col.dlla.nodes[currentNode].key;
	rez.second = col.dlla.nodes[currentNode].values.nodes[current].value;
	return rez;
}

bool MultiMapIterator::valid() const {
	/*
	if current indexes are lower than 0 or they are greater than the maximum capacity, returns false
	otherwise, returns true
	O(1) all cases
	*/
	if (currentNode != -1 && current != -1 && currentNode <= col.dlla.count && current <= col.dlla.nodes[currentNode].values.cap)
		return true;
	return false;
}

void MultiMapIterator::next() {
	/*
	Sets the current indexes to point to next position if it is valid

	Mentiune: n-am vazut in teste sa fie vreun catch asa ca n-am aruncat exceptii
	*/
	if(current != col.dlla.nodes[currentNode].values.tail)
		current = col.dlla.nodes[currentNode].values.nodes[current].next;
	else {
		if (valid()) {
		currentNode = col.dlla.nodes[currentNode].next;
		current = col.dlla.nodes[currentNode].values.head;
		}
	}
}

void MultiMapIterator::previous() {
	/*
	Sets the current indexes to point to previous position if it is valid
	*/
	if (current != col.dlla.nodes[currentNode].values.head)
		current = col.dlla.nodes[currentNode].values.nodes[current].previous;
	else {
		if (valid()) {
			currentNode = col.dlla.nodes[currentNode].previous;
			current = col.dlla.nodes[currentNode].values.tail;
		}
	}
}

void MultiMapIterator::first() {
	/*
	Sets the current indexes to point to the head of the dlla
	*/
	currentNode = col.dlla.head;
	current = col.dlla.nodes[currentNode].values.head;
}

void MultiMapIterator::last() {
	/*
	Sets the current indexes to point to the tail of the dlla
	*/
	currentNode = col.dlla.tail;
	current = col.dlla.nodes[currentNode].values.tail;

}

