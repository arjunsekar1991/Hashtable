#include "HashTable.h"
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "Slot.h"
using namespace std;

HashTable::HashTable()
{
	
	for(int i = 0; i < MAXHASH-1; i++) 
	{
		probeSequenceArray[i] = i+1;
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
	unsigned int home;
	
	home = hash(key)%MAXHASH;
	//intially new home will be home later if a collision occurs new home = home + probe [number of collision] % maxhash
	unsigned int newHome=home;
	
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


bool HashTable::find(int key, int& value) {
	numberOfSearchCollision = 0;
	unsigned int home;
	home = hash(key)%MAXHASH;
	unsigned int newHome = home;
	int numberOfIteration = 0;
	while (true) {
		
		if (hashTable[newHome].getKey() == key) { 
			value = hashTable[newHome].getValue();
			numberOfSearchCollision = numberOfIteration;
			return true;
		}
		//should i check tombstone ?
		if (hashTable[newHome].isEmpty() || hashTable[newHome].isTombstone()) {
			return false;
		}
		if (hashTable[newHome].isNormal()) {
			if (numberOfIteration == 1000) 
			{ 
				return false;
			}
			newHome = (home + probeSequenceArray[numberOfIteration]) % MAXHASH; 
			numberOfIteration++;
		}
	}
	return false;
}

float HashTable::alpha() {
	float alphavalue;
	alphavalue  = (float)numElts / (float)MAXHASH;
	return alphavalue;

}



bool HashTable::remove(int key) {
	
	unsigned long homePosition, deleteLocation;
	
	int collisions = 0;
	homePosition = hash(key) % MAXHASH;
	deleteLocation = homePosition;
	
	 Slot currentRecord = hashTable.at(deleteLocation);
	 
	while (!(currentRecord.isEmpty() || collisions >= MAXHASH - 1)) {
	
		collisions++;
		if (currentRecord.getKey() == key && currentRecord.isNormal()) {
			numElts--;
			hashTable.at(deleteLocation).kill();
			return true;
		}
		
		deleteLocation = (homePosition + probeSequenceArray[collisions]) % MAXHASH;
		
		currentRecord = hashTable.at(deleteLocation);
	}
	
	return false;
}

int HashTable::getNumberOfSearchCollision() {
	return numberOfSearchCollision;
}


 ostream& operator<<(ostream& os, const HashTable& hashTableObject) {
	for (int i = 0; i < MAXHASH; i++) {
		if (hashTableObject.hashTable[i].isNormal()) {
			os <<"Slot in HashTable" << i <<" Key: " << hashTableObject.hashTable[i].getKey() << " Value:" << hashTableObject.hashTable[i].getValue() << endl;
		}
	}
	return os;
}