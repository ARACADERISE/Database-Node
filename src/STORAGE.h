/* 
	Source code of the Database Nodes storage.

	Basically, the STORAGE.c file works with the Database Nodes storage, and handles it
*/

#include <stdio.h>
#include <stdlib.h>

// Updates the Database Nodes storage
DatabaseNodeset *
UpdateStorage(DatabaseNodeset *Db,int *ToChange,int changeBy, int Maxed, int SizeToIterate);

DatabaseNodeset *
AllocateData(DatabaseNodeset *Db);

DatabaseNodeset *ResetStorage(DatabaseNodeset *Db);

// A very simple function
DatabaseNodeset *
SetupNodeStorage(
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes,
	int SizeToIterate
);
