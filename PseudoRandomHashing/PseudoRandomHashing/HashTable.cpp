#include "HashTable.h"
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include "Slot.h"
#include <vector>
using namespace std;
// constructor for hash table
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

//hash function given by professor
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

	return hash;
}

//probe function that will calc new home based on numberof collisions
unsigned long HashTable::probe(int homePosition, int collisions) {
	unsigned long newHomePosition = (homePosition + probeSequenceArray[collisions]);
	return newHomePosition;
}

//insert function with collision resolution
bool HashTable::insert(int key, int value, int& collisions) {
	if (numElts == 1000) { 
		return false;
	}
	unsigned int home;
	
	home = hash(key)%MAXHASH;
	//intially new home will be home later if a collision occurs new home = home + probe [number of collision] % maxhash
	unsigned int newHome=home;
	
	while(true){
		//insert in empty or tombstone spot
		if (hashTable[newHome].isEmpty() || hashTable[newHome].isTombstone()) {
			hashTable[newHome] = Slot(key, value);
			numElts++;
			return true;
		}
		// this will check for normal slot and find the insert location
		else 
			if (hashTable[newHome].isNormal()) {
				if (hashTable[newHome].getKey() == key) {
					return false;
				}
				else { 
				
				newHome = (home + probeSequenceArray[collisions]) % MAXHASH;
				collisions++;
				}
		

			}


	}
	return false;
}

// Inputs are key and value if collision occurs pseudo random sequence will be referrerd to calculate new home
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
		
		if (hashTable[newHome].isEmpty() ) {
			return false;
		}
		if (hashTable[newHome].isNormal() || hashTable[newHome].isTombstone()) {
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
// This method calculates num of elts / max hash
float HashTable::alpha() {
	float alphavalue;
	alphavalue  = (float)numElts / (float)MAXHASH;
	return alphavalue;

}

// remove the element based on the key passed and marks the slot as tombstone

bool HashTable::remove(int key) {
	
	unsigned long homePosition, deleteLocation;
	
	int collisions = 0;
	homePosition = hash(key) % MAXHASH;
	deleteLocation = homePosition;
	
	 Slot currentRecord = hashTable.at(deleteLocation);
	 
	while (!(currentRecord.isEmpty() || collisions >= MAXHASH - 1)) {
	
		
		if (currentRecord.getKey() == key && currentRecord.isNormal()) {
			numElts--;
			hashTable.at(deleteLocation).kill();
			return true;
		}
		
		deleteLocation = (homePosition + probeSequenceArray[collisions]) % MAXHASH;
		collisions++;
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
//from general tree project
vector<string> HashTable::stringSplit(const string &source,
	 const char *delimiter = " ",
	 bool keepEmpty = false)
 {
	 vector<string> results;

	 size_t prev = 0;
	 size_t next = 0;

	 while ((next = source.find_first_of(delimiter, prev)) != string::npos)
	 {
		 if (keepEmpty || (next - prev != 0))
		 {
			 results.push_back(source.substr(prev, next - prev));
		 }
		 prev = next + 1;
	 }

	 if (prev < source.size())
	 {
		 results.push_back(source.substr(prev));
	 }

	 return results;
 }
// This is an helper function that will fix the slot number for the item that is moved as a replacement for the deleted item
bool HashTable::fixSlotAfterDelete(int key, int newIndexValue) {
	int oldSlot;
	find(key, oldSlot);
	int collisions=0;

	unsigned long int home;
	home = hash(key) % MAXHASH;
	//intially new home will be home later if a collision occurs new home = home + probe [number of collision] % maxhash
	unsigned int newHome = home;

	while (true) {

		if (hashTable[newHome].getKey() == key) {
			hashTable[newHome] = Slot(key, newIndexValue);
			return true;


		}else{
			newHome = (home + probeSequenceArray[collisions]) % MAXHASH;
			collisions++;
		
			}


	}
	return false;
	
}