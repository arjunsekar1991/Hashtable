#pragma once
#include "Record.h"
#include <vector>
#define MAXHASH 1000
#include <array>
class HashTable {
public:
	HashTable();
	//~HashTable();
	//bool insert(int key, int value, int& collisions);
	//bool remove(int key);
	//bool find(int key, int& value);
	//float alpha();
private:

	unsigned long probe(int, int);
	unsigned int hash(const int);
	vector<Record> unsortedStudentRecord;
	int numElts;
	array<int, MAXHASH> probeSequence;
};