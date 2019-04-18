#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

// There are three types of slots in a closed hash:
// Normal slots, empty slots, and tombstones
enum SlotType {normalSlot, emptySlot, tombstone};


// Each slot holds an integer key and an integer value.
// The integer value will be used as an index into the
// record store.

class Slot
{
private:
	int key;
	int value;
	SlotType type;

public:

	// The default constructor produces an empty slot.
	Slot()
	{
		key = 0;
		type = emptySlot;
	}

	// This constructor uses an initialization list
	// See "member initialization" at: http://www.cplusplus.com/doc/tutorial/classes/
	Slot(int newkey, int newvalue)
		: key(newkey), value(newvalue)
	{
		type = normalSlot;
	}

	// Convert a slot to a tombstone
	void kill() {
		type = tombstone;
	}

	// Get the integer key of a slot
	int getKey() const {
		return key;
	}

	// Get the value of a slot
	int getValue() const {
		return value;
	}

	// Check if a slot is empty
	bool isEmpty() const {
		return(type == emptySlot);
	}

	// Check if a slot is a normal slot
	bool isNormal() const {
		return(type == normalSlot);
	}

	// Check if a slot is a tombstone
	bool isTombstone() const {
		return (type == tombstone);
	}

	// Overload the << operator for printing slots
	friend ostream& operator<<(ostream& os, const Slot& me) {
		if (me.isTombstone())
			os << "<<Tombstone>>";
		else if (me.isEmpty())
			os << "<<Empty>>";
		else
			os << "Key: " << me.key << ", Value: " << me.value;
		return os;
	}

	// No destructor is needed as Slots don't use any dynamically
	// allocated memory
	~Slot()
	{
	}
};

