/*
Author: Scott Rainville
Class : CSI-240-03: Advanced Programming
Assignment : Final Inventory Project
Description : Candy functions

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

//Constructor
Candy::Candy(double initPrice, string initMaker, double initWeight)
{
	price = initPrice;
	maker = initMaker;
	weight = initWeight;

	totalCandy++;
}

//decreases total count by 1
void Candy::deIncTotal()
{
	totalCandy--;
}

//Overloader needed for sorting.
bool Candy::operator<(const Candy& comp)
{
	if (this->maker < comp.maker)
		return true;
	else
		return false;
}

//Overloader needed for copying.
void Candy::operator=(Candy& src)
{
	price = src.getPrice();
	maker = src.getMaker();
	weight = src.getWeight();
}

//overridden function that returns a custom description
string Candy::getDescription()
{
	stringstream stream;
	stream << "Candy made by " << maker << ". Weighs " << weight << ", costs " << price << ". ";

	return stream.str();
}

/* ACCESSORS */
string Candy::getMaker() { return maker; }
double Candy::getWeight() { return weight; }