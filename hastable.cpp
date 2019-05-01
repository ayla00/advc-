/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
Name: Astrid Lozano
Assignment: 0
Purpose: hashtable.cpp
Notes: if line is empty, it will be skipped. if file is emtpy, data won't be
added to struct nor a hash table be produced and an message will be displayed.
if the id is not an integer, that particular line won't be processed.
*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

#include "hashtable.h"



HashTable::HashTable()
{

	for (int index = 0; index < SIZE; index++)
	{
		startptr[index] = nullptr;
		searchptr[index] = nullptr;
		hashCount[index] = 0;
	}

}

HashTable::~HashTable()
{
	for (int index = 0; index < SIZE; index++)
	{
		hashCount[index] = 0;
	}
}


bool HashTable::add(int hnum, std::string hstring)
{

	hashIndex = moduloHash(hnum);
	searchptr[hashIndex] = startptr[hashIndex];

	hashSearch(startptr[hashIndex], hnum);

	if ((hashCount[hashIndex] < 1) || (hnum < startptr[hashIndex]->id))
		hashArray[hashIndex] = addHead(hnum, hstring);
	else if ((searchptr[hashIndex]->id == hnum) && (hashCount[hashIndex] > 1))
		return false;
	else if ((searchptr[hashIndex]->id > hnum)) //|| ((hashCount[hashIndex] == 1) && (searchptr[hashIndex]->id < hnum)))
		hashArray[hashIndex] = addMiddle(hnum, hstring);
	else if (searchptr[hashIndex]->id < hnum)
		hashArray[hashIndex] = addTail(hnum, hstring);

	return true;
}


bool HashTable::remove(int hnum)
{
	hashIndex = moduloHash(hnum);
	searchptr[hashIndex] = startptr[hashIndex];

	if (hashCount[hashIndex] > 0)
	{
		searchptr[hashIndex] = startptr[hashIndex];
		//this function changes the value of the startptr[hashIndex]
		hashSearch(startptr[hashIndex], hnum); //replacing this function with searchptr[hashIndex]

		if ((searchptr[hashIndex]->id == hnum) && (searchptr[hashIndex] == startptr[hashIndex]))
		{
			removeHead(hnum);
			return true;
		}
		else if ((searchptr[hashIndex]->id == hnum) && (searchptr[hashIndex]->forward == nullptr))
		{
			removeTail(hnum);
			return true;
		}
		else if (searchptr[hashIndex]->id == hnum) 
		{
			removeMiddle(hnum);
			return true;
		}
		else
			return false;
	}
	else
	{
		//hash table is empty, do not return message to user, just return false
		return false;
	}

}

bool HashTable::contains(int hnum)
{
	hashIndex = moduloHash(hnum);
	searchptr[hashIndex] = hashSearch(startptr[hashIndex], hnum);

	if (searchptr[hashIndex] == nullptr)
		return false;
	else if (searchptr[hashIndex]->id == hnum)
		return true;
	else
		return false;
}

std::string HashTable::getData(int hnum)
{
	//function will give appropriate value for index
	hashIndex = moduloHash(hnum);
	searchptr[hashIndex] = startptr[hashIndex];
	hashSearch(startptr[hashIndex], hnum);

	if ((startptr[hashIndex] == nullptr) || (searchptr[hashIndex] == nullptr))
	{
		std::cout << "the number you requested is NOT on the list\n" << std::endl;
		return "";
	}
	else if (searchptr[hashIndex]->id == hnum) //((hashSearch(startptr[hashIndex], endptr[hashIndex], hnum)->id) == hnum) //(searchptr[hashIndex]->id == hnum)
		return searchptr[hashIndex]->data;
	else
	{
		std::cout << "the HashStruct you requested is NOT on the list\n" << std::endl;
		searchptr[hashIndex] = nullptr;
		return "";
	}
}

void HashTable::printList()
{
	std::cout << "\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
	std::cout << "\n\n\t\t h a s h   t a b l e\n";
	std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";

	int modulus;

	for (int h = 0; h < SIZE; h++)
	{
		searchptr[h] = startptr[h];

		std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *";
		std::cout << "* * * * * * * * * * * * *\n";
		std::cout << "index:\t" << h << "\t\t\t\t\t\t\t\t\trow count: " << rowCountEntries(h) << std::endl;
		std::cout << " \t\tid \t" << " data \t\t" << " backward\t";
		std::cout << " forward\t" << " address\t" << " mod \t" << std::endl;

		while (searchptr[h] != nullptr)
		{
			modulus = ((searchptr[h]->id) % 19);
			std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  \n";
			std::cout << "\t\t" << searchptr[h]->id << "\t" << searchptr[h]->data;
			std::cout << "\t\t" << searchptr[h]->backward << "\t" << searchptr[h]->forward;
			std::cout << "\t" << searchptr[h] << "\t" << modulus << std::endl;

			searchptr[h] = searchptr[h]->forward;
		}
	}
}

HashStruct *HashTable::hashSearch(HashStruct *search, int hnum)
{
	hashIndex = moduloHash(hnum);


	if (hashCount[hashIndex] < 2)
		searchptr[hashIndex] = startptr[hashIndex];
	else if (searchptr[hashIndex] == nullptr)
		searchptr[hashIndex] == searchptr[hashIndex];
	else if (hnum < (startptr[hashIndex]->id))
		searchptr[hashIndex] = startptr[hashIndex];
	else if ((hnum == search->id) || (hnum == searchptr[hashIndex]->id))
		searchptr[hashIndex] = searchptr[hashIndex];
	else if (searchptr[hashIndex]->id < hnum)//(high->id >= low->id) //(searchptr[hashIndex]->id <= hnum) //old version (high->id >= low->id)
	{
		if ((hnum > search->id) && (hashCount[hashIndex] >= 2) && (search->forward != nullptr))
		{
			searchptr[hashIndex] = searchptr[hashIndex]->forward;
			hashSearch(searchptr[hashIndex], hnum);
		}
		else if (hnum < search->id)
			searchptr[hashIndex] = searchptr[hashIndex];
	}
	else
		searchptr[hashIndex] = searchptr[hashIndex];

	return searchptr[hashIndex];

}

HashStruct * HashTable::addHead(int hnum, std::string hstring)
{

	hashIndex = moduloHash(hnum);


	if (hashCount[hashIndex] == 0)
	{
		startptr[hashIndex] = new HashStruct;
		hashCount[hashIndex]++;

		searchptr[hashIndex] = startptr[hashIndex];

		startptr[hashIndex]->id = hnum;
		startptr[hashIndex]->data = hstring;
		startptr[hashIndex]->forward = nullptr;
		startptr[hashIndex]->backward = nullptr;
	}
	else if ((hashCount[hashIndex] == 1) && (searchptr[hashIndex]->id > hnum)) //new HashStruct is the starting point
	{
		searchptr[hashIndex] = startptr[hashIndex];

		startptr[hashIndex] = new HashStruct;
		hashCount[hashIndex]++;

		startptr[hashIndex]->id = hnum;
		startptr[hashIndex]->data = hstring;
		startptr[hashIndex]->forward = searchptr[hashIndex];
		startptr[hashIndex]->backward = nullptr;

		searchptr[hashIndex]->forward = nullptr;
		searchptr[hashIndex]->backward = startptr[hashIndex];

	}
	else if ((hashCount[hashIndex] > 1) && (hnum < startptr[hashIndex]->id)) //new HashStruct is the start
	{
		searchptr[hashIndex] = startptr[hashIndex];
		startptr[hashIndex] = new HashStruct;
		hashCount[hashIndex]++;

		//new HashStruct
		startptr[hashIndex]->id = hnum;
		startptr[hashIndex]->data = hstring;
		startptr[hashIndex]->forward = searchptr[hashIndex];
		startptr[hashIndex]->backward = nullptr;

		//old HashStruct
		searchptr[hashIndex]->forward = searchptr[hashIndex]->forward;
		searchptr[hashIndex]->backward = startptr[hashIndex];
	}

	return startptr[hashIndex];
}

void HashTable::removeHead(int hnum)
{
	hashIndex = moduloHash(hnum);

	if (hashCount[hashIndex] == 1)
	{
		startptr[hashIndex]->id = 0;
		startptr[hashIndex]->data = "";

		startptr[hashIndex]->forward = nullptr;
		startptr[hashIndex]->backward = nullptr;
		
		delete startptr[hashIndex];//this is dif for github version
		startptr[hashIndex] = nullptr;

		hashCount[hashIndex]--;
	}
	else
	{
		startptr[hashIndex]->id = 0;
		startptr[hashIndex]->data = "";

		startptr[hashIndex] = startptr[hashIndex]->forward;
		startptr[hashIndex]->forward = startptr[hashIndex]->forward;
		startptr[hashIndex]->backward = nullptr;

		//get rid of pointer pointing to struct
		delete searchptr[hashIndex];
		searchptr[hashIndex] = nullptr;
		hashCount[hashIndex]--;
	}

}

HashStruct * HashTable::addTail(int hnum, std::string hstring)
{
	hashIndex = moduloHash(hnum);

	searchptr[hashIndex]->forward = new HashStruct;
	hashCount[hashIndex]++;

	(searchptr[hashIndex]->forward)->id = hnum;
	(searchptr[hashIndex]->forward)->data = hstring;
	(searchptr[hashIndex]->forward)->forward = nullptr;
	(searchptr[hashIndex]->forward)->backward = searchptr[hashIndex];

	return searchptr[hashIndex]->forward;
}


void HashTable::removeTail(int hnum)
{
	hashIndex = moduloHash(hnum);

	if (hashCount[hashIndex] > 2)
	{
		searchptr[hashIndex]->id = 0;
		searchptr[hashIndex]->data = "";

		searchptr[hashIndex] = searchptr[hashIndex]->backward;
		(searchptr[hashIndex]->forward)->backward = nullptr;
		//searchptr[hashIndex]->backward = (searchptr[hashIndex]->backward); , check this line if problems
		searchptr[hashIndex]->forward = nullptr;
	}
	else if (hashCount[hashIndex] == 2)
	{
		searchptr[hashIndex]->id = 0;
		searchptr[hashIndex]->data = "";

		searchptr[hashIndex] = searchptr[hashIndex]->backward;

		(searchptr[hashIndex]->forward)->backward = nullptr;
		searchptr[hashIndex]->backward = nullptr; //check this if problems
	}
	else
	{
		searchptr[hashIndex]->id = 0;
		searchptr[hashIndex]->data = "";

		searchptr[hashIndex] = searchptr[hashIndex]->backward;
		searchptr[hashIndex]->forward = nullptr;
		searchptr[hashIndex]->backward = nullptr;

	}
	delete searchptr[hashIndex]->forward;  
	searchptr[hashIndex]->forward= nullptr;
	hashCount[hashIndex]--;
}

HashStruct * HashTable::addMiddle(int hnum, std::string hstring)
{
	hashIndex = moduloHash(hnum);

	if (searchptr[hashIndex]->id > hnum)
	{
		(searchptr[hashIndex]->backward)->forward = new HashStruct;
		(hashCount[hashIndex])++;

		((searchptr[hashIndex]->backward)->forward)->id = hnum;
		((searchptr[hashIndex]->backward)->forward)->data = hstring;
		((searchptr[hashIndex]->backward)->forward)->forward = searchptr[hashIndex]; //index
		((searchptr[hashIndex]->backward)->forward)->backward = searchptr[hashIndex]->backward; //index

		searchptr[hashIndex]->backward = (searchptr[hashIndex]->backward)->forward;
		searchptr[hashIndex] = searchptr[hashIndex]->backward;
	}

	return searchptr[hashIndex]; //definetely check this if issues
}


void HashTable::removeMiddle(int hnum)
{
	hashIndex = moduloHash(hnum);

	(searchptr[hashIndex]->forward)->backward = searchptr[hashIndex]->backward;
	(searchptr[hashIndex]->backward)->forward = searchptr[hashIndex]->forward;

	searchptr[hashIndex]->id = 0;
	searchptr[hashIndex]->data = "";
	searchptr[hashIndex]->forward = nullptr;
	searchptr[hashIndex]->backward = nullptr;

	//get rid of pointer pointing to struct
	delete searchptr[hashIndex];
	searchptr[hashIndex] = nullptr;
	hashCount[hashIndex]--;
}

int HashTable::moduloHash(int hnum)
{
	return hnum % SIZE;
}


int HashTable::rowCountEntries(int row)
{
	return hashCount[row];
}


int HashTable::CountEntries()
{
	int sum = 0;

	for (int s = 0; s < SIZE; s++)
	{
		sum += hashCount[s];
	}

	return sum;
}


void HashTable::clear()
{
	for (int h = 0; h < SIZE; h++)
	{
		searchptr[h] = startptr[h];

		if (hashCount[h] > 1)
		{
			while (searchptr[h]->forward != nullptr)
			{
				searchptr[h] = searchptr[h]->forward;
			}

			while (searchptr[h] != startptr[h])
			{
				searchptr[h]->id = 0;
				searchptr[h]->data = "";
				searchptr[h] = searchptr[h]->backward;

				delete searchptr[h]->forward;
				searchptr[h]->forward = nullptr;
				hashCount[h]--;
			}
		}
		else if (hashCount[h] == 0)
			hashCount[h] = 0;
		else
		{
			startptr[h]->id = 0;
			startptr[h]->data = "";
			delete startptr[h];
			startptr[h] = nullptr;
			hashCount[h]--;

		}

		delete startptr[h];
		startptr[h] = nullptr;
		hashCount[h] = 0;
	}
}


bool HashTable::isEmpty()
{
	bool empty = true;

	for (int h = 0; h < SIZE; h++)
	{
		if (hashCount[hashIndex] == 0)
			empty = empty;
		else
			empty = false;
	}

	return empty;
}