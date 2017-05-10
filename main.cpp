/*
Author: Scott Rainville
Class : CSI-240-03: Advanced Programming
Assignment : Final Inventory Project
Description : Main file

Certification of Authenticity :
I certify that this is entirely my own work, except where I have given
fully - documented references to the work of others.I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment :
-Reproduce this assignment and provide a copy to another member of
academic staff; and / or
-Communicate a copy of this assignment to a plagiarism checking
service(which may then retain a copy of this assignment)*/

using namespace std;
#include "header.h"

int Album::totalAlbums = 0;	//	Initialize static data members that keep track of item counts to zero.
int Candy::totalCandy = 0;	//
int Movie::totalMovies = 0;	//

int main()
{
	Inventory inv;	//make inventory object

	if (!inv.loadDBFromFile())	//open database files. If they don't open...
	{
		cout << "Failed to load one more more inventory files! Continuing with no data...\n";
		inv.purgeData();	//Purge the data that did load, if any
		system("PAUSE");
	}

	mainMenu(inv);	//load the main menu, which carries the user through until they exit. Passes the inventory object.

	return 0;
}