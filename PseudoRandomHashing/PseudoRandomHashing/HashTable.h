#pragma once
#include "Record.h"
#include "Slot.h"
#include <vector>
#define MAXHASH 1000
#include <array>
class HashTable {
public:
	HashTable();
	//~HashTable();
	bool insert(int key, int value, int& collisions);
	bool remove(int key);
	bool find(int key, int& value);
	float alpha();
	int getNumberOfSearchCollision();
private:

	unsigned long probe(int, int);
	unsigned int hash(const int);
	array<Slot, MAXHASH> hashTable;
	int numElts;
	array<int, MAXHASH-1> probeSequenceArray;
	int numberOfSearchCollision;
	
	friend ostream& operator<<(ostream& os, const HashTable& hashTableObject);
	
};

