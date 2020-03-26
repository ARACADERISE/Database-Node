/* 
	Source code of the Database Nodes storage.

	Basically, the STORAGE.c file works with the Database Nodes storage, and handles it
*/

#include <stdio.h>
#include <stdlib.h>

// Updates the Database Nodes storage
int
UpdateStorage(DatabaseNodeset *Db,int *ToChange,int changeBy, int Maxed);

// A very simple function
void
SetupNodeStorage(
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes
);
