Database program by Scott Rainville, Advanced Programming spring 2017

What is it?
	Database program that keeps inventory of albums, candy, and movies.

How to run it?
	Take all the source files and compile. Place the text files in the working directory of the program
	if you want the default database loaded. Without them, the program will make the files if you manually
	add items and save the database.

How does it work?
	Loading database:
	The program checks to see if the database files there. If so, each item in the text files
	will be loaded into objects in the program. If not, the program starts with no pre-loaded data.

	Saving database:
	Pre-existing files are overwritten with the data currently loaded into the program.

	Containerization:
	There is an inventory class with a single instance created that has three vectors, one for each item
	type. Functions are made for modifying these vectors of objects, and data members exist for keeping track
	of inventory information.

	Objects:
	There is one class for each item type. Each is a derived version of a generic base class and has unique
	data types and accessors, mutators, etc as well as an overridden description function that returns a
	specically formatted description string. Overloaded = and < for the sorting and copying of items by
	the inventory class.

	Menu:
	The menu functions are standalone. In main, an inventory object is created. This object is passed to
	the main menu function, which passes it around to the sub-functions to perform modifications as the
	user chooses.

How to use
	Viewing inventory:
	This is the first option from the main menu. It brings up another menu that lists the total number of items
	in the database and the total value and gives the option to view items of the three types separately, in which
	it will list the total objects of that type with the item number on the left. This number is for viewing
	reference and is not stored in object data.

	Removing items:
	The user can choose to remove any of the three types, after which all objects of that type are listed. Entering
	the number ofthe item to be removed deletes it. If the user's choice is out of range, an error is printed and
	they are put back into the main menu.

	Adding items:
	The user is given the choice to copy or add a completely new item.
		New:
		  User is prompted for every needed value. Object is created and added to the inventory when done.
		Copy:
		  All items of the chosen type are printed. User enters item number and it is added to the end of
		  the inventory for that type.

	Sorting items:
	User is brought to a menu where they can sort any of the three types. Albums and movies are sorted by title,
	candy sorted by maker.

	Loading database:
	The program loads the database from the files. If not all the files open, any information that did load is discarded.

	Saving database:
	Any data in the database is written to the files, overwriting any pre-existent data.

	Exiting:
	If the user attempts to exit the program with unsaved changes, they will be prompted to save the database.