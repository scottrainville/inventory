/*
Author: Scott Rainville
Class : CSI-240-03: Advanced Programming
Assignment : Final Inventory Project
Description : Inventory Class Functions

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

Inventory::Inventory()
{
	totalInvValue = 0;
	numItems = 0;
	unsavedChanges = false;
}

//for adding albums. Takes in the object attribute values and adds the object to the vector.
void Inventory::addAlbum(double initPrice, string initTitle, string initArtist, albumTypes initType, int initDuration)
{
	albumVec.push_back(Album(initPrice, initTitle, initArtist, initType, initDuration));
	numItems++;
	totalInvValue += initPrice;
}

//for adding candy. Takes in the object attribute values and adds the object to the vector.
void Inventory::addCandy(double initPrice, string initMaker, double initWeight)
{
	candyVec.push_back(Candy(initPrice, initMaker, initWeight));
	numItems++;
	totalInvValue += initPrice;
}

//for adding movies. Takes in the object attribute values and adds the object to the vector.
void Inventory::addMovie(double initPrice, string initTitle, movieTypes initType, int initDuration)
{
	movieVec.push_back(Movie(initPrice, initTitle, initType, initDuration));
	numItems++;
	totalInvValue += initPrice;
}

//removes album by its index, starting with 1 (not 0).
void Inventory::removeAlbum(int remove)
{
	if (!checkChoiceRange(ALBUM, remove))
		return;
	else
	{
		totalInvValue -= albumVec[remove - 1].getPrice();
		albumVec.erase(albumVec.begin() + (remove - 1));
		Album::deIncTotal();
		numItems--;
		unsavedChanges = true;
	}
}

//removes candy by its index, starting with 1 (not 0).
void Inventory::removeCandy(int remove)
{
	if (!checkChoiceRange(CANDY, remove))
		return;
	else
	{
		totalInvValue -= candyVec[remove - 1].getPrice();
		candyVec.erase(candyVec.begin() + (remove - 1));
		Candy::deIncTotal();
		numItems--;
		unsavedChanges = true;
	}
}

//removes movie by its index, starting with 1 (not 0).
void Inventory::removeMovie(int remove)
{
	if (!checkChoiceRange(MOVIE, remove))
		return;
	else
	{
		totalInvValue -= movieVec[remove - 1].getPrice();
		movieVec.erase(movieVec.begin() + (remove - 1));
		Movie::deIncTotal();
		numItems--;
		unsavedChanges = true;
	}
}

//copies album by its index, starting with 1 (not 0).
void Inventory::copyAlbum(int copy)
{
	if (!checkChoiceRange(ALBUM, copy))
		return;
	Album temp = albumVec[copy - 1];
	albumVec.push_back(temp);

	numItems++;
	Album::totalAlbums++;
	totalInvValue += temp.getPrice();
	unsavedChanges = true;
}

//copies candy by its index, starting with 1 (not 0).
void Inventory::copyCandy(int copy)
{
	if (!checkChoiceRange(CANDY, copy))
		return;
	Candy temp = candyVec[copy - 1];
	candyVec.push_back(temp);

	numItems++;
	Candy::totalCandy++;
	totalInvValue += temp.getPrice();
	unsavedChanges = true;
}

//copies movie by its index, starting with 1 (not 0).
void Inventory::copyMovie(int copy)
{
	if (!checkChoiceRange(MOVIE, copy))
		return;
	Movie temp = movieVec[copy - 1];
	movieVec.push_back(temp);

	numItems++;
	Movie::totalMovies++;
	totalInvValue += temp.getPrice();
	unsavedChanges = true;
}

//prints a formatted list of all albums
void Inventory::printAlbums()
{
	system("cls");
	cout << left << setw(NUM_WIDTH) << " " << setw(PRICE_WIDTH) << "PRICE" << setw(22) << "TITLE" << setw(15) << "ARTIST" << setw(15) << "TYPE" << setw(10) << "DURATION" << "DESCRIPTION" << endl;

	vector<Album>::iterator iter = albumVec.begin();
	int i = 1;
	while (iter != albumVec.end())
	{
		cout << setw(NUM_WIDTH) << i << left << setw(PRICE_WIDTH) << iter->getPrice() << setw(22) << iter->getTitle() << setw(15) << iter->getArtist() << setw(15) << albumStrings[iter->getType()] << setw(10) << iter->getDuration() << iter->getDescription() << endl;
		iter++; i++;
	}
	cout << endl << Album::totalAlbums << " total albums. " << endl;
}

//prints a formatted list of all movies
void Inventory::printMovies()
{
	system("cls");
	cout << left << setw(NUM_WIDTH) << " " << setw(PRICE_WIDTH) << "PRICE" << setw(25) << "TITLE" << setw(15) << "TYPE" << setw(10) << "DURATION" << "DESCRIPTION" << endl;

	vector<Movie>::iterator iter = movieVec.begin();
	int i = 1;
	while (iter != movieVec.end())
	{
		cout << left << setw(NUM_WIDTH) << i << setw(PRICE_WIDTH) << iter->getPrice() << setw(25) << iter->getTitle() << setw(15) << movieStrings[iter->getType()] << setw(10) << iter->getDuration() << iter->getDescription() << endl;
		iter++; i++;
	}
	cout << endl << Movie::totalMovies << " total movies. " << endl;
}

//prints a formatted list of all candy
void Inventory::printCandy()
{
	system("cls");
	cout << left << setw(NUM_WIDTH) << " " << setw(PRICE_WIDTH) << "PRICE" << setw(20) << "MAKER" << setw(15) << "WEIGHT" << "DESCRIPTION" << endl;

	vector<Candy>::iterator iter = candyVec.begin();
	int i = 1;
	while (iter != candyVec.end())
	{
		cout << left << setw(NUM_WIDTH) << i << setw(PRICE_WIDTH) << iter->getPrice() << setw(20) << iter->getMaker() << setw(15) << iter->getWeight() << iter->getDescription() << endl;
		iter++; i++;
	}
	cout << endl << Candy::totalCandy << " total candies. " << endl;
}

// For loading database info from four files. Calls the three below.
bool Inventory::loadDBFromFile()
{
	ifstream inputFile;
	int totalItems, albums, candy, movies;

	inputFile.open(DB_INFO);
	if (inputFile.fail())
	{
		return false;
	}
	else
	{
		inputFile >> totalItems >> albums >> candy >> movies;

		if (!loadAlbumsFromFile(albums))
			return false;
		if (!loadCandyFromFile(candy))
			return false;
		if (!loadMoviesFromFile(movies))
			return false;

		inputFile.close();
		return true;
	}
}

//int param is the number of items there are.
bool Inventory::loadAlbumsFromFile(int numAlbums)
{
	ifstream inputFile;
	string price, title, artist, typeString, duration, space;

	inputFile.open(ALBUM_FILE);
	if (inputFile.fail())
		return false;

	for (int i = 1; i <= numAlbums; i++)
	{
		getline(inputFile, price);
		getline(inputFile, title);
		getline(inputFile, artist);
		getline(inputFile, typeString);
		getline(inputFile, duration);
		getline(inputFile, space);

		addAlbum(atof(price.c_str()), title, artist, albumTypes(atoi(typeString.c_str())), atoi(duration.c_str()));
	}
	inputFile.close();
	return true;
}

//int param is the number of items there are.
bool Inventory::loadCandyFromFile(int numCandy)
{
	ifstream inputFile;
	string price, weight, maker, space;

	inputFile.open(CANDY_FILE);
	if (inputFile.fail())
		return false;

	for (int i = 1; i <= numCandy; i++)
	{
		getline(inputFile, price);
		getline(inputFile, maker);
		getline(inputFile, weight);
		getline(inputFile, space);

		addCandy(atof(price.c_str()), maker, atoi(weight.c_str()));
	}
	inputFile.close();
	return true;
}

//int param is the number of items there are.
bool Inventory::loadMoviesFromFile(int numMovies)
{
	ifstream inputFile;
	string price, title, typeString, duration, space;

	inputFile.open(MOVIE_FILE);
	if (inputFile.fail())
		return false;

	for (int i = 1; i <= numMovies; i++)
	{
		getline(inputFile, price);
		getline(inputFile, title);
		getline(inputFile, typeString);
		getline(inputFile, duration);
		getline(inputFile, space);

		addMovie(atof(price.c_str()), title, movieTypes(atoi(typeString.c_str())), atoi(duration.c_str()));
	}
	inputFile.close();
	return true;
}

//Writes out database to files. Overwrites anything in them.
void Inventory::writeToFile()
{
	//exit if there's nothing to save
	if (numItems < 1)
	{
		cout << "No data to save!\n";
		system("PAUSE");
		return;
	}

	//Write Albums
	ofstream outFile;
	outFile.open(ALBUM_FILE, ios::trunc);	//open file in trunc mode - removes pre-existing content

	vector<Album>::iterator albumIter = albumVec.begin();
	while (albumIter != albumVec.end())
	{
		outFile << albumIter->getPrice() << endl << albumIter->getTitle() << endl << albumIter->getArtist() << endl << albumStrings[albumIter->getType()] << endl << albumIter->getDuration() << endl << endl;
		albumIter++;
	}

	outFile.close();
	unsavedChanges = false;

	//Write Candy
	outFile.open(CANDY_FILE, ios::trunc);	//open file in trunc mode - removes pre-existing content
	vector<Candy>::iterator candyIter = candyVec.begin();
	while (candyIter != candyVec.end())
	{
		outFile << candyIter->getPrice() << endl << candyIter->getMaker() << endl << candyIter->getWeight() << endl << endl;
		candyIter++;
	}
	outFile.close();


	//Write Movies
	outFile.open(MOVIE_FILE, ios::trunc);	//open file in trunc mode - removes pre-existing content
	vector<Movie>::iterator movieIter = movieVec.begin();
	while (movieIter != movieVec.end())
	{
		outFile << movieIter->getPrice() << endl << movieIter->getTitle() << endl << movieStrings[movieIter->getType()] << endl << movieIter->getDuration() << endl << endl;
		movieIter++;
	}
	outFile.close();

	//write DB info to file
	outFile.open(DB_INFO, ios::trunc);
	outFile << numItems << endl << Album::totalAlbums << endl << Candy::totalCandy << endl << Movie::totalMovies;

	outFile.close();
}

//Sorts vector of Albums, Candy, or Movies.
void Inventory::sortVector(objectTypes type)
{
	if (type == ALBUM)
		sort(albumVec.begin(), albumVec.end());
	else if (type == CANDY)
		sort(candyVec.begin(), candyVec.end());
	else if (type == MOVIE)
		sort(movieVec.begin(), movieVec.end());
	unsavedChanges = true;
}

//Deletes all data from the program, but not from the data files.
void Inventory::purgeData()
{
	albumVec.clear();
	candyVec.clear();
	movieVec.clear();

	Album::totalAlbums = 0;
	Candy::totalCandy = 0;
	Movie::totalMovies = 0;

	totalInvValue = 0;
	numItems = 0;
}

//checks if the item number the user choce exists for the object type.
bool Inventory::checkChoiceRange(objectTypes type, unsigned int choice)
{
	bool success = true;

	if (type == ALBUM)
	{
		if ((choice > albumVec.size()) || (choice <= 0))
			success = false;
	}
	else if (type == CANDY)
	{
		if ((choice > candyVec.size()) || (choice <= 0))
			success = false;
	}
	else if (type == MOVIE)
	{
		if ((choice > movieVec.size()) || (choice <= 0))
			success = false;
	}

	if (!success)
	{
		cout << "Choice out of range!\n";
		system("PAUSE");
		return false;
	}
	else
		return true;
}

//ACCESSORS
double Inventory::getTotalInvValue()
{
	return totalInvValue;
}

int Inventory::getnumItems()
{
	return numItems;
}