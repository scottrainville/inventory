/*
Author: Scott Rainville
Class : CSI-240-03: Advanced Programming
Assignment : Final Inventory Project
Description : Header file

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
#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

const int PRICE_WIDTH = 6;	//standardized width for the price column when printing inv contents.
const int NUM_WIDTH = 4;	//same, but for the width of the number label column.

//Database file names.
const string ALBUM_FILE = "albums.txt";
const string CANDY_FILE = "candy.txt";
const string MOVIE_FILE = "movies.txt";
const string DB_INFO = "dbinfo.txt";

enum addRemove { ADD, REMOVE }; //for readability when making the function addRemoveMenu either add or remove.
enum objectTypes { ALBUM, CANDY, MOVIE };
enum albumTypes { NOALBUMTYPE = -1, CD, VINYL, DOWNLOAD };
enum movieTypes { NOMOVIETYPE = -1, DVD, BLURAY };

const string albumStrings[3] = { "CD", "VINYL", "DOWNLOAD" };
const string movieStrings[2] = { "DVD", "BLURAY" };

//Base item. All three item types inherit from this.
class BaseItem
{
public:
	BaseItem(); //default constructor
	virtual string getDescription() = 0; //pure virtual function to get item description
	int getPrice();

protected:
	double price;
};

//Unique variables: maker and weight
class Candy : public BaseItem
{
public:
	Candy(double, string, double);
	virtual string getDescription();	//Iteration of virtual function to get description.
	string getMaker();
	double getWeight();

	bool operator<(const Candy&);	//Overloader needed for sorting.
	void operator=(Candy&);			//Overloaded needed for copying.

	static void deIncTotal();	//Decreases total object count by one.
	static int totalCandy;

private:
	string maker;
	double weight;
};

//Unique variables: title, type, and duration
class Movie : public BaseItem
{
public:
	Movie(double, string, movieTypes, int);
	virtual string getDescription();	//Iteration of virtual function to get description.
	string getTitle();
	movieTypes getType();
	int getDuration();

	bool operator<(const Movie&);	//Overloader needed for sorting.
	void operator=(Movie&);			//Overloaded needed for copying.

	static void deIncTotal();	//Decreases total object count by one.
	static int totalMovies;

private:
	string title;
	movieTypes type;
	int duration;
};

//Unique variables: title, artist, type, and duration
class Album : public BaseItem
{
public:
	Album(double, string, string, albumTypes, int);

	virtual string getDescription();	//Iteration of virtual function to get description.
	string getTitle();
	string getArtist();
	albumTypes getType();
	int getDuration();

	bool operator<(const Album&);	//Overloader needed for sorting.
	void operator=(Album&);			//Overloader needed for copying.

	static void deIncTotal();	//Decreases total object count by one.
	static int totalAlbums;

private:
	string title, artist;
	albumTypes type;
	int duration;
};

//Inventory class. Acts as a container for all the objects created and abstracts/simplifies modifications.
class Inventory
{
public:
	Inventory();	//default constructor

	void addAlbum(double, string, string, albumTypes, int);	//	For adding items.
	void addCandy(double, string, double);					//
	void addMovie(double, string, movieTypes, int);			//

	void removeAlbum(int);	//	For removing items.
	void removeCandy(int);	//
	void removeMovie(int);	//

	void copyAlbum(int);	//	For copying items.
	void copyCandy(int);	//
	void copyMovie(int);	//

	void printAlbums();		//	For printing all objects of certain type.
	void printMovies();		//
	void printCandy();		//

	bool loadDBFromFile();			//	For loading database info from four files. LoadDBFromFile calls the three below.
	bool loadAlbumsFromFile(int);	//	int param is the number of items there are.
	bool loadCandyFromFile(int);	//
	bool loadMoviesFromFile(int);	//

	void writeToFile();	//	Writes out database to files. Overwrites anything in them.
	void sortVector(objectTypes);	//	Sorts vector of Albums, Candy, or Movies.
	void purgeData();	//Deletes all data from the program, but not from the data files.
	bool checkChoiceRange(objectTypes, unsigned int);	//checks if the item number the user choce exists for the object type.

														//ACCESSORS
	double getTotalInvValue();
	int getnumItems();

	bool unsavedChanges;	//whether or not there's changes that haven't been saved to the text files.

private:
	vector<Album> albumVec;	//	Vectors in which the objects are stored.
	vector<Candy> candyVec;	//
	vector<Movie> movieVec;	//

	double totalInvValue; //keeps track of total inventory value
	int numItems; //Keeps track of how many items we have total
};

/****** GENERAL USE FUNCTIONS ******/
bool validateInput(int, int, int);	//checks to see if the user's input is in range of the parameters specified.
double getPrice();			//make this return a double later
int getDuration();		//Gets the desired duration.
int getItemNumChoice();		//Gets the desired item number.
int newOrCopy();	//Get choice between new item or copying one.
bool continueToLoad();	//Asks the user if they want to continue to load from data files.
bool saveBeforeExit();	//Determines if the user wants to save changes or not.

/****** MAIN MENU FUNCTIONS ******/
void mainMenu(Inventory&);		//Main menu; loops until exit and calls respecive functions
void viewMenu(Inventory&);		//Menu for viewing items. Returns to main menu when done.
void addRemoveMenu(Inventory&, addRemove);		//Serves both the add menu and remove menu to save code.
void addAlbumMenu(Inventory&);		//Gets data for adding an album and add it to the program.
void addCandyMenu(Inventory&);		//Gets data for adding candy and add it to the program.
void addMovieMenu(Inventory&);		//Gets data for adding a movie and add it to the program.
void removeAlbumMenu(Inventory&);	//prints albums and deletes whichever the user chooses.
void removeCandyMenu(Inventory&);	//prints candy and deletes whichever the user chooses.
void removeMovieMenu(Inventory&);	//prints movies and deletes whichever the user chooses.
void copyAlbumMenu(Inventory&);		//prints albums and copies whichever the user chooses.
void copyCandyMenu(Inventory&);		//prints candy and copies whichever the user chooses.
void copyMovieMenu(Inventory&);		//prints movies and copies whichever the user chooses.
void sortMenu(Inventory&);		//Gets the user's choice for what to sort and does it.
//All take the inventory object created in main as an argument to perform actions upon it.