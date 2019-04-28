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
getInfo reads a file's contents.
* if an alphabetic value is within id (integer) data, list will NOT processed and
an error message will display
*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*	*/

#include "main.h"

int main()
{


	try
	{
		const int MAINTESTINDEX = 10;
		srand(time(NULL));

		int variable;
		std::string alphacheck;
		alphacheck = "a";

		//initial test, just checking things work
		HashTable hashtabla;
		//variable = stoi(alphacheck);
		//variable = 'a';
		//if (!isalpha(variable))
		//	hashtabla.add(variable, "alpha");
		//else
			//throw NOTINTEGER;

		hashtabla.add(45, "stuff0");
		hashtabla.printList();
		hashtabla.add(89, "stuff1");
		hashtabla.add(25, "stuff2");
		hashtabla.add(117, "stuff3");
		hashtabla.add(78, "stuff4");
		hashtabla.add(4, "stuff5");
		hashtabla.printList();
		std::cout << "\n\ndata for number 45: \t " << hashtabla.getData(45) << std::endl;
		hashtabla.remove(117);
		hashtabla.remove(63);
		hashtabla.printList();


		//randomized loop tests
		for (int i = 0; i < MAINTESTINDEX; i++)
		{
			HashTable tabla;
			randomAddGetTest(tabla);

			std::cout << "\n* * * * * * * * * * * * * * * * * * * * * \n" << std::endl;
			std::cout << "* * * * * * * * * * * * * * * * * * * * * \n" << std::endl;
			tabla.clear();
			std::cout << " clear() & isEmtpy() test (table should print with no info):\n";
			std::cout << "isEmpty?:\t" << tabla.isEmpty() << std::endl;
			tabla.printList();

			std::cout << "\n\nDELETE TEST\n\n";
			randomDeleteTest(tabla);
			tabla.clear();
		}

		//collision and delete test, look at index 7
		testCollisionDelete();

		//getting file info
		std::string file = "finaltest.csv";
		std::ifstream inputfile;

		readFileTest(inputfile, file);


		hashtabla.clear();

	}
	catch (int NOTINTEGER)
	{
		std::cout << "\n\nERROR MESSAGE\n";
		std::cout << "\na noninteger value was in your data.\n";
	}
	catch (...)
	{
		std::cout << "\n\nERROR MESSAGE\n";
		std::cout << "an error has occurred while running. please check your file for appropriate format/values\n";
	}


	return 0;
}