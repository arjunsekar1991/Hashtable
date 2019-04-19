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
	//bool remove(int key);
	//bool find(int key, int& value);
	//float alpha();
private:

	unsigned long probe(int, int);
	unsigned int hash(const int);
//	vector<Record> unsortedStudentRecord;
	array<Slot, MAXHASH> hashTable;
	int numElts;
	int collisions;
	array<int, MAXHASH> probeSequenceArray;
};