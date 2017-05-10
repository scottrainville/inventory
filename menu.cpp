/*
Author: Scott Rainville
Class : CSI-240-03: Advanced Programming
Assignment : Final Inventory Project
Description : Menu functions

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

//checks to see if the user's input is in range of the parameters specified.
bool validateInput(int min, int max, int choice)
{
	if ((choice > max) || (choice < min))
	{
		cout << "Invalid choice\n";
		system("PAUSE");
		return false;
	}
	return true;
}

//make this return a double later
double getPrice()
{
	string price;

	cout << "Enter the price: ";
	getline(cin, price);
	return atof(price.c_str());
}

//Gets the desired duration.
int getDuration()
{
	string duration;
	cout << "Enter the duration in minutes: ";
	getline(cin, duration);
	return atoi(duration.c_str());
}

//Gets the desired item number.
int getItemNumChoice()
{
	string choice;
	cout << "Enter the item number: ";
	cin >> choice;
	return atoi(choice.c_str());
}

//Get choice between new item or copying one.
int newOrCopy()
{
	string choice;
	cin.ignore();
	cout << "Add new (1) or copy (2)? [1]: ";
	cin >> choice;
	if (choice == "2")
		return 2;
	else
		return 1;
}

//Asks the user if they want to continue to load from data files.
bool continueToLoad()
{
	string input;
	cout << "Warning: Current changes will be lost! Type 'y' to continue.\n";
	cin >> input;
	if (input == "y")
		return true;
	else
	{
		cout << "Canceled.\n";
		system("PAUSE");
		return false;
	}
}

//Determines if the user wants to save changes or not.
bool saveBeforeExit()
{
	string choice;
	cout << "Save changes before exiting? 'n' for no. [y] :";
	cin.ignore();
	getline(cin, choice);

	while ((choice != "y") && (choice != "n") && !choice.empty())
	{
		cout << "Please enter 'y' or 'n'. ";
		getline(cin, choice);
	}

	if (choice == "n")
		return false;
	else
		return true;
}


/******************************/
/*    MAIN MENU FUNCTIONS     */
/******************************/

//Main menu; loops until exit and calls respecive functions
void mainMenu(Inventory& inv)
{
	string input;
	int choice;
	bool exit = false;

	do
	{
		do
		{
			system("cls");
			cout << "**** MAIN MENU ****" << endl;
			cout << "1. View Inventory\n";
			cout << "2. Remove items\n";
			cout << "3. Add items\n";
			cout << "4. Sort Items\n";
			cout << endl;
			cout << "5. Load Database From Files\n";
			cout << "6. Save Database to Files\n";
			cout << "7. Exit\n";
			cout << endl;

			cin >> input;
			choice = atoi(input.c_str());

		} while (!validateInput(1, 7, choice));

		switch (choice) {
		case 1:
			viewMenu(inv);
			break;
		case 2:
			addRemoveMenu(inv, REMOVE);
			break;
		case 3:
			addRemoveMenu(inv, ADD);
			break;
		case 4:
			sortMenu(inv);
			break;
		case 5:
			if (continueToLoad())
			{
				inv.purgeData();
				if (!inv.loadDBFromFile())	//open database files. If they don't open...
				{
					cout << "Failed to load one more more inventory files! Continuing with no data...\n";
					inv.purgeData();	//Purge the data that did load, if any
					system("PAUSE");
				}
			}
			break;
		case 6:
			inv.writeToFile();
			break;
		case 7:
			exit = true;
			if (inv.unsavedChanges)
			{
				if (saveBeforeExit())
					inv.writeToFile();
			}
			break;
		}
	} while (!exit);
}

//Menu for viewing items. Returns to main menu when done.
void viewMenu(Inventory& inv)
{
	string input;
	int choice;
	bool exit = false;

	do
	{
		do
		{
			system("cls");
			cout << "**** VIEW MENU ****" << endl;
			cout << "1. View Albums\n";
			cout << "2. View Candy\n";
			cout << "3. View Movies\n";
			cout << "4. Back\n";
			cout << endl;

			//print basic inv statistics
			cout << "Total Items: " << inv.getnumItems() << endl;
			cout << "Total Value: " << inv.getTotalInvValue() << endl;

			cin >> input;
			choice = atoi(input.c_str());

		} while (!validateInput(1, 7, choice));

		switch (choice) {
		case 1:
			inv.printAlbums();
			break;
		case 2:
			inv.printCandy();
			break;
		case 3:
			inv.printMovies();
			break;
		case 4:
			exit = true;
			return;
		}
		system("PAUSE");
	} while (!exit);
}

//Serves both the add menu and remove menu to save code.
void addRemoveMenu(Inventory& inv, addRemove addremove)
{
	string input, addOrRemove;
	int choice;

	if (addremove == ADD)
		addOrRemove = "ADD";
	else if (addremove == REMOVE)
		addOrRemove = "REMOVE";

	do
	{
		system("cls");
		cout << "**** " << addOrRemove << " ITEM MENU ****" << endl;
		cout << "1. Album\n";
		cout << "2. Candy\n";
		cout << "3. Movie\n";
		cout << "4. Back to Main Menu\n";
		cout << endl;

		cin >> input;
		choice = atoi(input.c_str());

	} while (!validateInput(1, 4, choice));

	switch (choice) {
	case 1:
		if (addremove == ADD)
			addAlbumMenu(inv);
		else
			removeAlbumMenu(inv);
		break;
	case 2:
		if (addremove == ADD)
			addCandyMenu(inv);
		else
			removeCandyMenu(inv);
		break;
	case 3:
		if (addremove == ADD)
			addMovieMenu(inv);
		else
			removeMovieMenu(inv);
		break;
	case 4:
		break;
	}
}

//Gets data for adding an album and add it to the program.
void addAlbumMenu(Inventory& inv)
{
	if (newOrCopy() == 2)
	{
		copyAlbumMenu(inv);
		return;
	}

	string title, artist, type;
	double price;
	int intType, duration;
	albumTypes albumtype;

	cin.ignore();

	price = getPrice();

	cout << "Enter the title: ";
	getline(cin, title);

	cout << "Enter the artist: ";
	getline(cin, artist);

	do {
		cout << "Enter 1 for CD, 2 for Vinyl, or 3 for Download: ";
		getline(cin, type);
		intType = atoi(type.c_str());
	} while (!validateInput(1, 3, intType));

	intType -= 1;
	albumtype = (albumTypes)intType;

	duration = getDuration();

	inv.addAlbum(price, title, artist, albumtype, duration);
	inv.unsavedChanges = true;
}

//Gets data for adding a movie and add it to the program.
void addMovieMenu(Inventory& inv)
{

	if (newOrCopy() == 2)
	{
		copyMovieMenu(inv);
		return;
	}
	string title, type;
	double price;
	int duration, intType;
	movieTypes movietype;

	cin.ignore();

	price = getPrice();

	cout << "Enter the title: ";
	getline(cin, title);

	do
	{
		cout << "Enter 1 for DVD, 2 for Blu-Ray: ";
		getline(cin, type);
		intType = atoi(type.c_str());
	} while (!validateInput(1, 2, intType));

	intType -= 1;
	movietype = (movieTypes)intType;

	duration = getDuration();

	inv.addMovie(price, title, movietype, duration);
	inv.unsavedChanges = true;
}

//Gets data for adding candy and add it to the program.
void addCandyMenu(Inventory& inv)
{
	if (newOrCopy() == 2)
	{
		copyCandyMenu(inv);
		return;
	}

	double price, weightD;
	string maker, weight;

	cin.ignore();

	price = getPrice();

	cout << "Enter the maker: ";
	getline(cin, maker);

	cout << "Enter the weight: ";
	getline(cin, weight);

	weightD = atof(weight.c_str());

	inv.addCandy(price, maker, weightD);
	inv.unsavedChanges = true;
}

//prints albums and deletes whichever the user chooses.
void removeAlbumMenu(Inventory& inv)
{
	inv.printAlbums();
	inv.removeAlbum(getItemNumChoice());
}

//prints candy and deletes whichever the user chooses.
void removeCandyMenu(Inventory& inv)
{
	inv.printCandy();
	inv.removeCandy(getItemNumChoice());
}

//prints movies and deletes whichever the user chooses.
void removeMovieMenu(Inventory& inv)
{
	inv.printMovies();
	inv.removeMovie(getItemNumChoice());
}

//prints albums and copies whichever the user chooses.
void copyAlbumMenu(Inventory& inv)
{
	inv.printAlbums();
	inv.copyAlbum(getItemNumChoice());
}

//prints candy and copies whichever the user chooses.
void copyCandyMenu(Inventory& inv)
{
	inv.printCandy();
	inv.copyCandy(getItemNumChoice());
}

//prints movies and copies whichever the user chooses.
void copyMovieMenu(Inventory& inv)
{
	inv.printMovies();
	inv.copyMovie(getItemNumChoice());
}

//Gets the user's choice for what to sort and does it.
void sortMenu(Inventory& inv)
{
	string input;
	int choice;

	do
	{
		system("cls");
		cout << "**** SORT MENU ****" << endl;
		cout << "1. Sort Albums\n";
		cout << "2. Sort Candy\n";
		cout << "3. Sort Movies\n";
		cout << "4. Back\n";
		cout << endl;

		cin >> input;
		choice = atoi(input.c_str());
	} while (!validateInput(1, 4, choice));

	switch (choice)
	{
	case 1:
		inv.sortVector(ALBUM);
		break;
	case 2:
		inv.sortVector(CANDY);
		break;
	case 3:
		inv.sortVector(MOVIE);
		break;
	case 4:
		break;
	}
}