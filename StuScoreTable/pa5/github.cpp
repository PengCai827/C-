// Table.cpp  Table class implementation
// CSCI 455 PA5
// Name: Yanni Wang
// Loginid: 7540834851

/*
 * Modified 11/22/11 by CMB
 *   changed name of constructor formal parameter to match .h file
 */

#include "Table.h"

#include <iostream>
#include <string>
#include <cassert>

//*************************************************************************
// Node class definition and member functions
//     You don't need to add or change anything in this section

// Note: we define the Node in the implementation file, because it's only
// used by the Table class; not by any Table client code.

struct Node {
  string key;
  int value;

  Node *next;

  Node(const string &theKey, int theValue);

  Node(const string &theKey, int theValue, Node *n);
};

Node::Node(const string &theKey, int theValue) {
  key = theKey;
  value = theValue;
  next = NULL;
}

Node::Node(const string &theKey, int theValue, Node *n) {
  key = theKey;
  value = theValue;
  next = n;
}

typedef Node * ListType;

//*************************************************************************


Table::Table() {
	list = new ListType[HASH_SIZE];
	numEntry = 0;
	nonBucket = 0;
	longestChain = 0;
	hashSize = HASH_SIZE;

	for(int i = 0; i < hashSize; i++) {
		list[i] = NULL;
	}
}


Table::Table(unsigned int hSize) {
	hashSize = hSize;
	numEntry = 0;
	nonBucket = 0;
	longestChain = 0;
	list = new ListType[hashSize];

	for(int i = 0; i < hashSize; i++) {
			list[i] = NULL;
	}

}


int * Table::lookup(const string &key) {
	int code = hashCode(key);
	if(list[code] == NULL) {
		return NULL;
	}

	ListType p = list[code];
	while(p != NULL){
		if(p->key == key) {
			return &(p->value);
		}
		p = p->next;
	}

	return NULL;
}

bool Table::remove(const string &key) {
	int code = hashCode(key);
	if (list[code] == NULL) {  // if the key does not exist
		return false;
	}

	ListType p = list[code];
	if(p->key == key) {   // if a bucket contains the key and it is at the first place
		list[code] = p->next;
		delete p;
		if(p->next == NULL) {
			nonBucket--;
		}
		numEntry--;
		findLongest();
		return true;
	}
	else { // the key is not at the first place of a bucket
		ListType pNext = p->next;
		while(pNext != NULL) {
			if(pNext->key == key) {
				p->next = pNext->next;
				delete pNext;
				numEntry--;
				findLongest();
				return true;
			}
			p = p->next;
			pNext = pNext->next;
		}
	}

	return false;
}

bool Table::insert(const string &key, int value) {
	int code = hashCode(key);
	ListType p = list[code];
	if(p == NULL) {
		list[code] = new Node(key,value);
		nonBucket++;
		numEntry++;
		if(longestChain == 0) {
			longestChain = 1;
		}
		return true;
	}

	while(p->next != NULL) {
		if(p->key == key) {
			return false;
		}
		p = p->next;
	}
	if(p->key == key) {
		return false;
	}
	p->next = new Node(key,value);
	numEntry++;
	findLongest();

	return true;
}

bool Table::newscore(const string &key, int value) {
	int code = hashCode(key);
	ListType p = list[code];

	while(p != NULL) {
		if(p->key == key) {
			p->value = value;
			return true;
		}
	}

	if(p == NULL) {
		return false;
	}
	return true;
}

int Table::numEntries() const {
	return numEntry;
}


void Table::printAll() const {
	for(int i = 0; i < hashSize; i++) {
		ListType p = list[i];
		while(p != NULL) {
			cout << "[" << p->key << ", " << p->value << "] ";
			p = p->next;
		}
	}
	cout << endl;
}

void Table::hashStats(ostream &out) const {
	out << "number of buckets: " << hashSize << endl;
	out << "number of entries: " << numEntry << endl;
	out << "number of non-empty buckets: " << nonBucket << endl;
	out << "longest chain: " << longestChain << endl;

}

// add definitions for your private methods here
void Table::findLongest() {
	longestChain = 0;
	for(int i = 0; i < hashSize; i++) {
		int temp = 0;
		ListType p = list[i];
		if(list[i] != NULL) {
			while(p != NULL) {
				temp++;
				p = p->next;
			}
			if(temp > longestChain) {
				longestChain = temp;
			}
		}
	}
}