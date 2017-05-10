/*
Author: Scott Rainville
Class : CSI-240-03: Advanced Programming
Assignment : Final Inventory Project
Description : Movie functions

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

//constructor
Movie::Movie(double initPrice, string initTitle, movieTypes initType, int initDuration)
{
	price = initPrice;
	title = initTitle;
	type = initType;
	duration = initDuration;

	totalMovies++;
}

//overridden function that returns a custom description
string Movie::getDescription()
{
	stringstream stream;
	stream << "Movie titled " << title << ". " << movieStrings[type] << ". " << duration << " minutes.";

	return stream.str();
}

//Overloader needed for sorting.
bool Movie::operator<(const Movie& comp)
{
	if (this->title < comp.title)
		return true;
	else
		return false;
}

//Overloader needed for copying.
void Movie::operator=(Movie& src)
{
	price = src.getPrice();
	title = src.getTitle();
	type = src.getType();
	duration = src.getDuration();
}

//decreases total count by 1
void Movie::deIncTotal() { totalMovies--; }

/* ACCESSORS */
string Movie::getTitle() { return title; }
movieTypes Movie::getType() { return type; }
int Movie::getDuration() { return duration; }