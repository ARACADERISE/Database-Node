/* 
	Source code of the Database Nodes storage.

	Basically, the STORAGE.c file works with the Database Nodes storage, and handles it
*/

#include <stdio.h>
#include <stdlib.h>

// A very simple function
void
SetupNodeStorage(
	int MaxFileSize, // Size of 10000+
	int MaxStringSize, // Size of 20000+
	int MaxIntegerSize, // Size of 20000+
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes
);
