/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
Name: Astrid Lozano
Assignment: 05
Purpose: hashtable.h
Notes: printList() should show the items were properly linked and collisions
were appropriately dealt with. After using the clear() method, and and empty list
should be displayed. randomAddGettest test adds random numbers and gets information of
last random number to demonstrate functioning of get. randomDeleteGet will create an array
with every 5th random element, these numbers will be deleted from hash table.
The collisionDelete test especifically test collision of items, getting an item beyond first
element and what happens when an item in a collision position is deleted.
getInfo reads file.
*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

#ifndef MAIN_H
#define MAIN_H

#include "hashtable.h"
#include <fstream>
//#include <iomanip>
//#include <iostream>
#include <stdlib.h> //library where rand is located
#include <stdio.h>
#include <time.h>  //needed for seed of random number generator (srand)
//#include <string>

void randomAddGetTest(HashTable & table);
void randomDeleteTest(HashTable & table);
void readFileTest(std::ifstream &file, std::string myfile);
bool getInfo(std::string extract, HashTable &extractinfo);
//int countLines(std::ifstream &file);
void testCollisionDelete();
const int NOTINTEGER = -99999999;
const int CHARACTERLIMIT = 32;
std::string checkCharLimit(std::string& charstring);

#endif //MAIN_H
