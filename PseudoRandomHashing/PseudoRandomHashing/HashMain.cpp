#pragma once
#include "Record.h"
#include "HashTable.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
/*
some of the testing used
cout << "hi";
	HashTable test;
	Record r("Firstname1", "Lastname1", 1, "Grad");
	Record r2("Firstname2", "Lastname2", 2, "Grad");
	Record r3("Firstname2", "Lastname2", 3, "Grad");
	vector<Record> unsortedStudentRecord;
	unsortedStudentRecord.push_back(r);
	int slotWhereInserted = unsortedStudentRecord.size() - 1;
	int collision = 0;
	test.insert(r.getUID(), slotWhereInserted, collision);
	unsortedStudentRecord.push_back(r2);
	slotWhereInserted = unsortedStudentRecord.size() - 1;
	test.insert(r2.getUID(), slotWhereInserted, collision);
	unsortedStudentRecord.push_back(r3);
	slotWhereInserted = unsortedStudentRecord.size() - 1;
	test.insert(r3.getUID(), slotWhereInserted, collision);
	//test.insert(r.getUID(), slotWhereInserted, collision);
	int foundValue;
	bool findResult = test.find(3, foundValue);
	cout << foundValue;
	cout << collision;
	cout << "done";
	float a = test.alpha();
	cout << "Alphavalue:" << test.alpha();

	
		HashTable hashTable2;
	vector<Record> unsortedStudentRecord2;


		int collision = 0;
		for (int i = 1; i < 1001; i++) {
			Record rec = Record( "Temp", "Temp", i, "Temp");
			unsortedStudentRecord2.push_back(rec);
			bool result =hashTable2.insert(i, unsortedStudentRecord2.size() - 1, collision);
			cout << result<<endl;
		}
		int y;
		hashTable2.find(1000,y);
		cout << hashTable2.getNumberOfSearchCollision();
		cout << "Alphavalue:" << hashTable2.alpha();;
*/
	

	
	vector<Record> unsortedStudentRecord;
	bool isQuitTriggered = false;

	string userInput;
	HashTable hashTable; 
	while (!isQuitTriggered) {
		cout << "Would you like to (I)nsert or (D)elete a record, or (S)earch for a record, or (Q)uit?" << endl;

		cout << "Enter action: ";
		cin >> userInput;

		if (userInput == "I") {

			
			cout << "Inserting a new record." << endl;
			cout << "Last name: ";
			string lastName, firstName, year;
			int uid, collisions = 0;
			cin >> lastName;
			cout << "First name: ";
			cin >> firstName;
			cout << "UID: ";
			cin >> uid; 
			while (cin.fail()) {
				cout << "UID entered was not an int value." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Re-enter UID: ";
				cin >> uid; 
			}
			cout << "Year: ";
			cin >> year; 
			Record record = Record(firstName, lastName, uid, year);

			unsortedStudentRecord.push_back(record);
			if (hashTable.insert(uid, unsortedStudentRecord.size() - 1, collisions)) {
				cout << "Record inserted." << endl;
			}
			else {
				cout << "Record insert failed possibly due to a duplicate key or hash table full" << endl;
			}
		}

		else if (userInput == "D") { 
			
			int uid, returnedRecordIndexInVector;

			cout << "Enter UID to delete: ";
			cin >> uid;
			while (cin.fail()) { 
				cout << "UID entered is not valid." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Enter UID again: ";
				cin >> uid;
			}
			cout << "Searching... ";
			if (hashTable.find(uid, returnedRecordIndexInVector)) {
			
			if (hashTable.remove(uid)) { 
				
				unsortedStudentRecord.erase(unsortedStudentRecord.begin() + returnedRecordIndexInVector);
				int sizeOfVector = unsortedStudentRecord.size();
				int lastElementIndex = sizeOfVector - 1;
				Record lastRecordInStudentRecord = unsortedStudentRecord[lastElementIndex];
				unsortedStudentRecord[returnedRecordIndexInVector] = lastRecordInStudentRecord;
				hashTable.fixSlotAfterDelete(lastRecordInStudentRecord.getUID(), returnedRecordIndexInVector);
				cout << "Record Found" << endl;
				cout << "Record Deleted Successfully" << endl;
			}
			else { 
				cout << "Record Not Found" << endl;
			}
			}
		}

		else if (userInput == "S") { 
			int uid;
			int returned;
			cout << "Enter UID to search for: ";
			cin >> uid; 
			while (cin.fail()) {
				cout << "UID entered was not an int value." << endl;
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Re-enter UID: ";
				cin >> uid;
			}
			cout << "Searching... ";
			if (hashTable.find(uid, returned)) { 
				cout << "record found" << endl;
				cout << "------------" << endl;
				Record currentRecord = unsortedStudentRecord.at(returned);
				vector<string> names =hashTable.stringSplit(currentRecord.getName(), ",", true);

				cout << "Last name: " << names[0] << endl;
				// this will remove additional space after comma from what the fullname method return
				cout << "First name: " << names[1].erase(0,1) << endl;
				cout << "UID: " << currentRecord.getUID() << endl;
				cout << "Year: " << currentRecord.getYear() << endl;
				cout << "Number of collisions: " << hashTable.getNumberOfSearchCollision() << endl;
				cout << "------------" << endl;
			}
			else { 
				cout << "record not found" << endl;
			}
		}
		
		else if (userInput == "P") {
			cout << "Print all Hash table content for testing" << endl;
			cout << hashTable << endl;
		}

		else if (userInput == "A") {
			cout << "Print alpha value for hash table" << endl;
			cout << "Alpha value is : " << hashTable.alpha() << endl;
		}
		
		else if (userInput == "Q") {
		cout << "Good Bye." << endl;
		isQuitTriggered = true;
		}

		else {
			cout << "Invalid Option" << endl;
		}
		
		cout << endl;
	}

	return 0;

}