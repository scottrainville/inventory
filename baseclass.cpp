/*
Author: Scott Rainville
Class : CSI-240-03: Advanced Programming
Assignment : Final Inventory Project
Description : Class Functions

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

BaseItem::BaseItem()	//default BaseItem constructor
{
	//nothing needed here
}

//overloaded by derived classes
string BaseItem::getDescription()
{
	stringstream stream;
	stream << "Undefined item, costs " << price << ".";

	return stream.str();
}

/* ACCESSORS */

int BaseItem::getPrice() { return price; }