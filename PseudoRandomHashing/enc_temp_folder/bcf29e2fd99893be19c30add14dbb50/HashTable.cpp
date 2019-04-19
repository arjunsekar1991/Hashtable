#include "HashTable.h"
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "Slot.h"
using namespace std;

HashTable::HashTable()
{
	
	for(int i = 0; i < MAXHASH; i++) 
	{
		probeSequenceArray[i] = i;
	}

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	numElts = 0;
	
	shuffle(probeSequenceArray.begin(), probeSequenceArray.end(), default_random_engine(seed));
}


unsigned int HashTable::hash(const int key)
{
	const char* kptr = (char *)&key;
	unsigned int length = sizeof(int);
	unsigned int hash = 1315423911;
	unsigned int i = 0;

	for (i = 0; i < length; ++kptr, ++i)
	{
		hash ^= ((hash << 5) + (*kptr) + (hash >> 2));
	}

	return 5;
}


unsigned long HashTable::probe(int homePosition, int collisions) {
	unsigned long newHomePosition = (homePosition + probeSequenceArray[collisions]);
	return newHomePosition;
}


bool HashTable::insert(int key, int value, int& collisions) {
	if (numElts == 1000) { 
		return false;
	}
	unsigned long home;
	
	home = hash(key)%MAXHASH;
	unsigned long newHome=home;
	
	while(true){
		
		if (hashTable[newHome].isEmpty() || hashTable[newHome].isTombstone()) {
			hashTable[newHome] = Slot(key, value);
			numElts++;
			return true;
		}
		else 
			if (hashTable[newHome].isNormal()) {
				if (hashTable[newHome].getKey() == key) {
					return false;
				}
				else { 
				
				newHome = (home + probeSequenceArray[collisions]) % MAXHASH;
				collisions++;
//				hashTable[newHome] = Slot(key, value);
				}
		

			}


	}
	return false;
}