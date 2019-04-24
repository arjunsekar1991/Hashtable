#pragma once
#include "Record.h"
#include "Slot.h"
#include <vector>
#define MAXHASH 1000
#include <array>
#include <string>
class HashTable {
public:
	HashTable();
	//~HashTable();
	bool insert(int , int , int& );
	bool remove(int);
	bool find(int, int&);
	float alpha();
	int getNumberOfSearchCollision();
	//adding this from previous project for easily tokenizing first and last name
	vector<string> stringSplit(const string& , const char* , bool );
	//this will fix slot after fixing 
	bool fixSlotAfterDelete(int, int);
private:
	//this will have probe sequence
	unsigned long probe(int, int);
	// not exposing hash
	unsigned int hash(const int);
	//hashtable 
	array<Slot, MAXHASH> hashTable;
	//number of hash table elements
	int numElts;
	//probe array will have 1 to 999 probe sequence array will not have 1000 elements to avoid 
	// sequence repeating
	array<int, MAXHASH-1> probeSequenceArray;
	int numberOfSearchCollision;
	
	friend ostream& operator<<(ostream&, const HashTable&);
	
};

