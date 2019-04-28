/*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*
Name: Astrid Lozano
Assignment: 05
Purpose: hashtable.h
Notes:
//REMEMBER TO CLOSE FILE BEFORE EXITING CODE
printList() should show the items were properly linked and collisions
were appropriately dealt with. After using the clear() method, and and empty list
should be displayed. randomAddGettest test adds random numbers and gets information of
last random number to demonstrate functioning of get. randomDeleteGet will create an array
with every 5th random element, these numbers will be deleted from hash table.
The collisionDelete test especifically test collision of items, getting an item beyond first
element and what happens when an item in a collision position is deleted.
*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

#include "main.h"

void randomAddGetTest(HashTable & table)
{
	int randomnumber;
	const int TESTINDEX = 50;
	const int SIZE = table.SIZE;

	//std::cout << "random #:\t" << randomnumber << std::endl;


	std::cout << "total count before adding: \t" << table.CountEntries() << std::endl;
	//random adding
	for (int j = 0; j < TESTINDEX; j++)
	{
		randomnumber = (0 + rand() % 1000);
		std::string loopstring = std::to_string(j);
		table.add(randomnumber, loopstring);
	}

	std::cout << "\n\n\n* * * * * * * * * * * * * * * * * *  * * * \n" << std::endl;
	std::cout << "\n\t\tADD TEST \n\n";
	std::cout << "* * * * * * * * * * * * * * * * * *  * * * \n" << std::endl;
	std::cout << "count after adding: \t" << table.CountEntries() << std::endl;
	table.printList();

	std::cout << "* * * * * * * * * * * * * * * * * *  * * * \n" << std::endl;
	std::cout << "GET EXISTING RANDOM ENTRY \n" << std::endl;
	std::cout << "number to get:\t" << randomnumber << std::endl;
	std::cout << "data:\t\t" << table.getData(randomnumber) << std::endl;
	std::cout << "contains?:\t" << table.contains(randomnumber) << std::endl;
}

void randomDeleteTest(HashTable & table)
{
	const int TESTINDEX = 30;
	const int ARRAYSIZE = TESTINDEX / 5;
	int h = 0;
	bool yesno;
	int randomnumber;
	int deleteArray[ARRAYSIZE];

	//to count succesful deletes (numbers that are not repeated)
	int deletecount = 0;
	int countbeforedelete;


	for (int j = 0; j < TESTINDEX; j++)
	{
		randomnumber = (0 + rand() % 1000);
		std::string loopstring = std::to_string(j);
		table.add(randomnumber, loopstring);

		if ((h < ARRAYSIZE) && (j % 5 == 0))
		{
			deleteArray[h] = randomnumber;
			h++;
		}
	}

	std::cout << "\n\n* * * * * * * * * * * * * * * * * *  * * * \n" << std::endl;
	std::cout << "\n\n\t\tDELETE TESTLIST\n";
	std::cout << "\n* * * * * * * * * * * * * * * * * *  * * * \n" << std::endl;
	table.printList();
	std::cout << "\n\nTOTAL NUMBER OF NODES BEFORE DELETE: \t" << table.CountEntries() << std::endl;
	countbeforedelete = table.CountEntries();

	//condition to avoid division by zero error
	for (int k = 0; k < ARRAYSIZE; k++)
	{
		std::cout << "* * * * * * * * * * * * * * * * * * * * * \n" << std::endl;
		std::cout << "item to be deleted:\t" << deleteArray[k] << std::endl;
		std::cout << "count before delete:\t\t" << table.CountEntries() << std::endl;
		yesno = table.remove(deleteArray[k]);
		std::cout << "deleted status:\t\t\t" << yesno << std::endl;
		std::cout << "count after delete attempt:\t" << table.CountEntries() << std::endl;

		if (yesno == true)
			deletecount = deletecount + 1;
		else
			deletecount = deletecount;

	}

	std::cout << "\n* * * * * * * * * * * * * * * * * * * * * \n" << std::endl;
	std::cout << "count before any delete:\t\t\t" << countbeforedelete << std::endl;
	std::cout << "successful deletes:\t\t\t\t" << deletecount << std::endl;

	std::cout << "TOTAL NUMBER OF NODES AFTER ALL DELETES: \t" << table.CountEntries() << std::endl;
	std::cout << "\nlist after deleted items\n";
	table.printList();

	//will try to delete last number in delete array, so it should not be in the list anymore
	//index is (h - 1) as the index was increased by one before exiting loop, so last index assinged should be h-1
	std::cout << "\n* * * * * * * * * * * * * * * * * *  * * * \n" << std::endl;
	std::cout << "GET NON-EXISTING RANDOM ENTRY & CONTAIN \n" << std::endl;
	std::cout << "number to get:\t" << deleteArray[h - 1] << std::endl;
	std::cout << "\tdata:\t" << table.getData(deleteArray[h - 1]) << std::endl;
	std::cout << "contains?:\t" << table.contains(deleteArray[h - 1]) << std::endl;

}

void readFileTest(std::ifstream &inputfile, std::string myfile)
{
	int linenumber;
	std::string textline;
	int count = 0;
	inputfile.open(myfile);

	if (inputfile.is_open())
	{
		//linenumber = countLines(inputfile);
		//puts file at the beginning again so it can be re-read
		//inputfile.clear();

		HashTable info;

		while (getline(inputfile, textline))
		{

			if (!textline.empty())
			{
				if (getInfo(textline, info) == true)
					count += 1;
				else
					count = count;
			}
			else
				count = count;
		}


		if (count == 0)
		{
			std::cout << "the file is empty\n\n";
		}


		info.printList();
		std::cout << "\n\ntotal entries:\t" << info.CountEntries() << std::endl;

	}
	else
	{
		std::cout << "the file you entered cannot be found or does not exist\n";
		std::cout << "please enter a correct filename\n";
	}

	inputfile.close();
}

bool getInfo(std::string extract, HashTable &extractinfo)
{
	int idconstruct; //used to check for alphabet characther and to convert string to int;
	bool returnvalue = false;
	const int LINESIZE = extract.size();

	std::string palabra = "";
	std::string numword = "";
	std::string otherdata = "";

	HashStruct getinfo;

	for (int i = 0; i < LINESIZE; i++)
	{
		if (extract[i] != ',')
		{
			//checks for alphabet characters in number input
			if ((extract[i] >= -1) && (extract[i] <= 255))
			{
				idconstruct = extract[i];
				if (!isalpha(idconstruct))
					numword += extract[i];
				else
					throw NOTINTEGER;
			}
			else
				numword += extract[i];
		}
		else
		{
			idconstruct = stoi(numword);
			getinfo.id = idconstruct;

			for (int j = (i + 1); j < LINESIZE; j++) //starts at next value of i, since i is a comma
			{
				i = LINESIZE; //to prevent loop from looking into other indexes

				if ((extract[j] != ',') && ((j + 1) != LINESIZE))
					palabra += extract[j];
				else if ((extract[j] != ',') && ((j + 1) == LINESIZE))
				{
					palabra += extract[j];
					getinfo.data = checkCharLimit(palabra);

					if (extractinfo.add(getinfo.id, getinfo.data))
						returnvalue = true;
					else
						returnvalue = false;

					return returnvalue; //code must be here to exit
				}
				else if (extract[j] == ',')
				{
					//the rest word has already been put together on if statement
					palabra = palabra;

					//this checks if word meets character limit requirement,
					//if not, it truncates word;
					getinfo.data = checkCharLimit(palabra);

					if (extractinfo.add(getinfo.id, getinfo.data))
						returnvalue = true;
					else
						returnvalue = false;

					//takes care of rest of string in files with no whitespace
					otherdata = "";
					for (int word = (j + 1); word < LINESIZE; word++)
					{
						otherdata += extract[word];
					}

					j = LINESIZE;
					getInfo(otherdata, extractinfo);
				}
			}
		}
	}

}

/*
int countLines(std::ifstream & file)
{
	int count = 0;
	std::string line;

	while (getline(file, line))
	{

		if (!line.empty())
			count += 1;
		else
			count = count;
	}
	return count;
}
*/

void testCollisionDelete()
{
	int count;
	HashTable collision;
	collision.add(824, "dog");
	collision.add(197, "cat");
	collision.add(976, "parrot");
	collision.add(159, "ant");
	collision.add(703, "colibri");
	collision.add(419, "whale");
	collision.add(665, "delfin");
	collision.add(897, "starfish");
	collision.add(921, "plankton");
	collision.add(542, "arbol");
	collision.add(173, "hongo");
	collision.add(692, "mango");
	collision.add(690, "snail");
	collision.add(169, "oruga");
	collision.add(989, "fern");
	collision.add(727, "elefante");
	collision.add(931, "bird");
	collision.add(483, "racoon");
	collision.add(759, "opossum");
	collision.add(732, "axolotl");
	collision.add(329, "cacao");
	collision.add(786, "buho");

	count = collision.CountEntries();

	std::cout << "\n\nTEST DEMONSTRATES WHAT HAPPENS WHEN ITEMS COLLIDE\n";
	std::cout << "OBTAINING AND ITEM BEYOND SECOND ELEMENT, AND WHAT HAPPENS\n";
	std::cout << "WHEN AN ITEM IS DELETED AND GETTING AN ITEM FROM LINKED LIST WHERE\n";
	std::cout << "ITEMS COLLIDED\n\n\n";

	if (count != 0)
	{
		// 197 and 824 have the same remainder (will be placed in same location by HF)
		collision.printList();
		std::string testgetdata;
		collision.remove(197);
		std::cout << "\n\ndoes the list contain id 197?\t" << collision.contains(197) << std::endl;
		std::cout << "data of node 824:\t" << collision.getData(824) << std::endl;
		std::cout << "\n\nList without item 197\n";
		collision.printList();
		collision.clear();
	}
	else
		std::cout << "the file is empty\n\n";
}

std::string checkCharLimit(std::string &charstring)
{
	if (charstring.size() <= CHARACTERLIMIT)
		charstring = charstring;
	else
	{
		std::string truncatedword = "";
		for (int limit = 0; limit <= CHARACTERLIMIT; limit++)
		{
			truncatedword += charstring[limit];
		}

		charstring = truncatedword;
	}

	return charstring;
}
