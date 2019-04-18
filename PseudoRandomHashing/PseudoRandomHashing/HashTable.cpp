#include "HashTable.h"
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

HashTable::HashTable()
{
	
	for(int i = 0; i < MAXHASH; i++) 
	{
		probeSequence[i] = i;
	}

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();

	
	shuffle(probeSequence.begin(), probeSequence.end(), default_random_engine(seed));
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

	return hash;
}


unsigned long HashTable::probe(int homePosition, int collisions) {
	unsigned long newHomePosition = (homePosition + probeSequence[collisions]) % MAXHASH;
	return newHomePosition;
}
