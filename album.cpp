/*
Author: Scott Rainville
Class : CSI-240-03: Advanced Programming
Assignment : Final Inventory Project
Description : album functions

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
Album::Album(double initPrice, string initTitle, string initArtist, albumTypes initType, int initDuration)
{
	price = initPrice;
	title = initTitle;
	artist = initArtist;
	type = initType;
	duration = initDuration;

	totalAlbums++;
}

//overridden function that returns a custom description
string Album::getDescription()
{
	stringstream stream;
	stream << "'" << title << "' by " << artist << ". " << albumStrings[type] << ", " << duration << " minutes.";

	return stream.str();
}

//decreases total count by 1
void Album::deIncTotal()
{
	totalAlbums--;
}

//Overloader needed for sorting.
bool Album::operator<(const Album& comp)
{
	if (this->title < comp.title)
		return true;
	else
		return false;
}

//Overloader needed for copying.
void Album::operator=(Album& src)
{
	price = src.getPrice();
	title = src.getTitle();
	artist = src.getArtist();
	type = src.getType();
	duration = src.getDuration();
}

/* ACCESSORS */
string Album::getTitle() { return title; }
string Album::getArtist() { return artist; }
albumTypes Album::getType() { return type; }
int Album::getDuration() { return duration; }