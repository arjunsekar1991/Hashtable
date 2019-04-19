#pragma once
#include "Record.h"
#include "HashTable.h"
#include <iostream>
using namespace std;

int main() {
	cout << "hi";
	HashTable test;
	Record r("Firstname1", "Lastname1", 1, "Grad");
	Record r2("Firstname2", "Lastname2", 2, "Grad");
	vector<Record> unsortedStudentRecord;
	unsortedStudentRecord.push_back(r);
	int slotWhereInserted = unsortedStudentRecord.size() - 1;
	int collision = 0;
	test.insert(r.getUID(), slotWhereInserted, collision);
	unsortedStudentRecord.push_back(r2);
	slotWhereInserted = unsortedStudentRecord.size() - 1;
	test.insert(r2.getUID(), slotWhereInserted, collision);
	//test.insert(r.getUID(), slotWhereInserted, collision);
	cout << collision;
	cout << "done";
}