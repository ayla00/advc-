/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
Name: Astrid Lozano
Assignment: 05
Purpose: hashtable.h
Notes:
*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <iomanip> //for setw
#include <stdlib.h> //library where rand is located
#include <time.h>  //needed for seed of random number generator (srand)

struct HashStruct
{
	int id;
	std::string data;
	HashStruct * forward;
	HashStruct * backward;
};


class HashTable
{
public:
	HashTable();
	~HashTable();
	bool add(int hnum, std::string hstring);
	bool remove(int hnum);
	bool contains(int hnum);
	std::string getData(int hnum); //look at alternate declaration
	void printList();
	int rowCountEntries(int row); //counts entries per index
	int CountEntries(); //counts all entries
	int nodenum;
	void clear();
	bool isEmpty();
	const int SIZE = 19;


private:
	int hashCount[19];
	int hashIndex;
	HashStruct * hashArray[19]; //array of pointer to structs = hash table
	HashStruct * hashSearch(HashStruct *low, HashStruct * high, int hnum);
	HashStruct * startptr[19];
	HashStruct * endptr[19];
	HashStruct * newhashptr[19];
	HashStruct * searchptr[19];
	HashStruct * addHead(int hnum, std::string hstring);
	void removeHead(int hnum);
	HashStruct * addTail(int hnum, std::string hstring);
	void removeTail(int hnum);
	HashStruct * addMiddle(int hnum, std::string hstring);
	void removeMiddle(int hnum);
	int moduloHash(int hnum);

};

#endif //HASHTABLE_H
