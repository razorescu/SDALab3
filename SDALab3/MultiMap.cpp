#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>
#include <vector>

using namespace std;


MultiMap::MultiMap() { //O(dlla.cap*dlla.nodes.values.cap)
	dlla.cap = 10;
	dlla.head = -1;
	dlla.tail = -1;
	dlla.firstEmpty = 0;
	dlla.count = 0;
	dlla.nodes = new DLLANode[dlla.cap];
	for (int i = 0; i < dlla.cap; i++) {
		dlla.nodes[i].key = NULL_TVALUE;
		dlla.nodes[i].next = i + 1;
		dlla.nodes[i].previous = i - 1;
		dlla.nodes[i].values.cap = 10;
		dlla.nodes[i].values.head = -1;
		dlla.nodes[i].values.tail = -1;
		dlla.nodes[i].values.firstEmpty = 0;
		dlla.nodes[i].values.count = 0;
		dlla.nodes[i].values.nodes = new DLLAVNode[dlla.nodes[i].values.cap];
		for (int j = 0; j < dlla.nodes[i].values.cap; j++) {
			dlla.nodes[i].values.nodes[j].value = NULL_TVALUE;
			dlla.nodes[i].values.nodes[j].next = j + 1;
			dlla.nodes[i].values.nodes[j].previous = j - 1;
		}
	}
	length = 0;
}


void MultiMap::add(TKey c, TValue v) {
	/*
	Adds a value to a Key if the key is in the multimap, adds both if not
	Best - O(1)
	Average, worst - O(n*(2*n))
	*/
	if (dlla.head == -1) { //empty list
			dlla.head = 0;
			dlla.tail = 0;
			dlla.firstEmpty++;
			dlla.count++;
			dlla.nodes[0].key = c;
			dlla.nodes[0].values.head = 0;
			dlla.nodes[0].values.tail = 0;
			dlla.nodes[0].values.firstEmpty++;
			dlla.nodes[0].values.nodes[0].value = v;
			dlla.nodes[0].values.count++;
			length++;
			return;
		}
	for (int i = 0; i < dlla.cap; i++) { //checking if key exists in list
		if (dlla.nodes[i].key == c) { //found key in list 
			if (dlla.nodes[i].values.count == dlla.nodes[i].values.cap - 2) {//capacity increase
				/*DLLAVNode* newalloc;
				int size = 2 * dlla.nodes[i].values.cap;
				newalloc = new DLLAVNode[size];
				for (int x = 0; x < dlla.nodes[i].values.cap; x++) {
					newalloc[x].value = dlla.nodes[i].values.nodes[x].value;
					newalloc[x].next = dlla.nodes[i].values.nodes[x].next;
					newalloc[x].previous = dlla.nodes[i].values.nodes[x].previous;
				}
				for (int x = dlla.nodes[i].values.cap; x < size; x++) {
					newalloc[x].value = NULL_TVALUE;
					newalloc[x].next = x + 1;
					newalloc[x].previous = x - 1;
				}
				delete[] dlla.nodes[i].values.nodes;
				dlla.nodes[i].values.nodes = newalloc;
				dlla.nodes[i].values.cap = size;*/
				DLLAValues newalloc;
				int size = 5 * dlla.nodes[i].values.cap;
				newalloc.cap = dlla.nodes[i].values.cap;
				newalloc.count = dlla.nodes[i].values.count;
				newalloc.firstEmpty = dlla.nodes[i].values.firstEmpty;
				newalloc.head = dlla.nodes[i].values.head;
				newalloc.tail = dlla.nodes[i].values.tail;
				newalloc.nodes = new DLLAVNode[size];
				for (int x = 0; x < newalloc.cap; x++) {
					newalloc.nodes[x].value = dlla.nodes[i].values.nodes[x].value;
					newalloc.nodes[x].next = dlla.nodes[i].values.nodes[x].next;
					newalloc.nodes[x].previous = dlla.nodes[i].values.nodes[x].previous;
				}
				for (int x = newalloc.cap; x < size; x++) {
					newalloc.nodes[x].value = NULL_TVALUE;
					newalloc.nodes[x].next = x + 1;
					newalloc.nodes[x].previous = x - 1;
				}
				dlla.nodes[i].values = newalloc;
				dlla.nodes[i].values.cap = size;
			}
			dlla.nodes[i].values.nodes[dlla.nodes[i].values.firstEmpty].value = v; //setting the value to the new node
			dlla.nodes[i].values.nodes[dlla.nodes[i].values.firstEmpty].previous = dlla.nodes[i].values.tail; //setting previous node to previous tail
			dlla.nodes[i].values.tail = dlla.nodes[i].values.firstEmpty; //setting the new tail to the added node
			dlla.nodes[i].values.nodes[dlla.nodes[i].values.firstEmpty].next = dlla.nodes[i].values.nodes[dlla.nodes[i].values.firstEmpty].next; //setting added node's next to future firstempty
			dlla.nodes[i].values.firstEmpty = dlla.nodes[i].values.nodes[dlla.nodes[i].values.firstEmpty].next; //setting new firstempty
			dlla.nodes[i].values.count++;
			length++; //increasing the number of "pairs"
			return;
		}
	}
	//key not in list -> adding key
	if (dlla.count == dlla.cap - 2) {//capacity increase
		DLLANode* newalloc;
		int sized = 2 * dlla.cap;
		newalloc = new DLLANode[sized];
		for (int x = 0; x < dlla.cap; x++) {
			newalloc[x].key = dlla.nodes[x].key;
			newalloc[x].next = dlla.nodes[x].next;
			newalloc[x].previous = dlla.nodes[x].previous;
			newalloc[x].values = dlla.nodes[x].values;
		}
		for (int x = dlla.cap; x < sized; x++) {
			newalloc[x].key = NULL_TVALUE;
			newalloc[x].next = x + 1;
			newalloc[x].previous = x - 1;
			newalloc[x].values.cap = 10;
			newalloc[x].values.count = 0;
			newalloc[x].values.firstEmpty = 0;
			newalloc[x].values.head = -1;
			newalloc[x].values.tail = -1;
			newalloc[x].values.nodes = new DLLAVNode[newalloc[x].values.cap];
			for (int y = 0; y < newalloc[x].values.cap - 1; y++)
			{
				newalloc[x].values.nodes[y].value = NULL_TVALUE;
				newalloc[x].values.nodes[y].next = y + 1;
				newalloc[x].values.nodes[y].previous = y - 1;
			}
		}
		delete[] dlla.nodes;
		dlla.nodes = newalloc;
		dlla.cap = sized;
	}
	dlla.nodes[dlla.firstEmpty].key = c;
	dlla.nodes[dlla.firstEmpty].values.nodes[dlla.nodes[dlla.firstEmpty].values.firstEmpty].value = v;
	dlla.nodes[dlla.firstEmpty].values.firstEmpty = dlla.nodes[dlla.firstEmpty].values.nodes[dlla.nodes[dlla.firstEmpty].values.firstEmpty].next;
	dlla.nodes[dlla.firstEmpty].values.tail = 0;
	dlla.nodes[dlla.firstEmpty].values.head = 0;//add link to this key from the previous one
	dlla.nodes[dlla.firstEmpty].previous = dlla.tail;
	dlla.nodes[dlla.firstEmpty].values.count++;
	dlla.tail = dlla.firstEmpty;
	dlla.firstEmpty = dlla.nodes[dlla.firstEmpty].next;
	dlla.count++;
	length++; //increasing number of pairs

}


bool MultiMap::remove(TKey c, TValue v) {
	/*
	Removes a value from a Key if it's not the only value, removes a key if it only has 1 value
	Best case: O(n)
	Average, worst - O(n^2)
	*/
	for (int i = 0; i < dlla.cap; i++) {//searching for key
		if (dlla.nodes[i].key == c) {//key found
			if (dlla.nodes[i].values.head != dlla.nodes[i].values.tail) {//key has more than 1 value
				for (int j = 0; j < dlla.nodes[i].values.cap; j++) {
					if (dlla.nodes[i].values.nodes[j].value == v) {//value found
						if (j == dlla.nodes[i].values.head) {//removing the head of the values' DLLA
							dlla.nodes[i].values.head = dlla.nodes[i].values.nodes[j].next; //setting new head
							dlla.nodes[i].values.nodes[dlla.nodes[i].values.nodes[j].next].previous = -1; //setting new head's previous to -1
							dlla.nodes[i].values.nodes[j].next = dlla.nodes[i].values.firstEmpty; //setting the link to the next first empty spot
							dlla.nodes[i].values.firstEmpty = j; //setting first empty spot to be at the spot we removed the value from
							dlla.nodes[i].values.nodes[j].value = NULL_TVALUE;
							dlla.nodes[i].values.count--;
							length--;
							return true;
						}
						if (j == dlla.nodes[i].values.tail) {//removing the tail of the values' DLLA
							dlla.nodes[i].values.tail = dlla.nodes[i].values.nodes[j].previous;
							dlla.nodes[i].values.firstEmpty = j;
							dlla.nodes[i].values.nodes[j].value = NULL_TVALUE;
							dlla.nodes[i].values.count--;
							length--;
							return true;
						}
						//value is neither head nor tail
						dlla.nodes[i].values.nodes[dlla.nodes[i].values.nodes[j].previous].next = dlla.nodes[i].values.nodes[j].next; //setting previous node's next
						dlla.nodes[i].values.nodes[j].value = NULL_TVALUE;
						dlla.nodes[i].values.nodes[dlla.nodes[i].values.nodes[j].next].previous = dlla.nodes[i].values.nodes[j].previous; //setting next nodes's previous
						//preparing the node for eventual future add
						dlla.nodes[i].values.nodes[j].next = dlla.nodes[i].values.firstEmpty;
						dlla.nodes[i].values.firstEmpty = j; //setting firstempty to this position
						dlla.nodes[i].values.count--;
						return true;
					}
				}
			}
			//key only has 1 value -> deleting the key
			//3 scenarios: key is head, key is tail, neither
			if (i == dlla.head) {//key is head
				dlla.head = dlla.nodes[i].next;
				dlla.nodes[dlla.nodes[i].next].previous = -1;
				dlla.nodes[i].key = NULL_TVALUE; //setting key to invalid
				dlla.nodes[i].values.count--;
				dlla.nodes[i].values.nodes[dlla.nodes[i].values.head].value = NULL_TVALUE; //setting key's value to invalid
				dlla.nodes[i].next = dlla.firstEmpty;
				dlla.count--;

				dlla.firstEmpty = i;
				length--;
				return true;
			}
			if (i == dlla.tail) {//key is tail
				dlla.tail = dlla.nodes[i].previous;
				dlla.nodes[i].key = NULL_TVALUE; //setting key to invalid
				dlla.nodes[i].values.count--;
				dlla.nodes[i].values.nodes[dlla.nodes[i].values.head].value = NULL_TVALUE; //setting key's value to invalid
				dlla.nodes[i].next = dlla.firstEmpty;
				dlla.firstEmpty = i;
				dlla.count--;
				length--;
				return true;
			}
			//key is neither head nor tail
			dlla.nodes[dlla.nodes[i].previous].next = dlla.nodes[i].next;
			dlla.nodes[dlla.nodes[i].next].previous = dlla.nodes[i].previous;
			dlla.nodes[i].key = NULL_TVALUE; //setting key to invalid
			dlla.nodes[i].values.count--;
			dlla.nodes[i].values.nodes[dlla.nodes[i].values.head].value = NULL_TVALUE; //setting key's value to invalid
			dlla.nodes[i].next = dlla.firstEmpty;
			dlla.firstEmpty = i;
			dlla.count--;
			length--;
			return true;
		}
	}
	return false;
}


vector<TValue> MultiMap::search(TKey c) const {
	/*
	Returns a vector of TValue with all values of a key
	Best - O(n)
	Average, worst - O(n^2)
	*/
	vector<TValue> ret;
	for (int i = 0; i < dlla.cap; i++) {
		if (dlla.nodes[i].key == c) {
			for (int j = 0; j < dlla.nodes[i].values.cap - 1; j++)
				if(dlla.nodes[i].values.nodes[j].value != -11111) //if value not invalid
					ret.push_back(dlla.nodes[i].values.nodes[j].value);
		}
	}
	return ret;
}


int MultiMap::size() const {
	/*
	Returns the amount of elements in the MultiMap
	Best, average, worst - O(1)
	*/
	return length;
}


bool MultiMap::isEmpty() const {
	/*
	Returns true if the MultiMap is empty, false if not
	Best, average, worst - O(1)
	*/
	if (length == 0)
	{
		return true;
	}
	return false;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	//TODO - Implementation
}

