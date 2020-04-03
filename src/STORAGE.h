/* 
	Source code of the Database Nodes storage.
	Basically, the STORAGE.c file works with the Database Nodes storage, and handles it
*/

#include <stdio.h>
#include <stdlib.h>

// Updates the Database Nodes storage
DatabaseNodeset *
UpdateStorage(DatabaseNodeset *Db,size_t *ToChange,size_t changeBy, size_t Maxed, int SizeToIterate, char *StorageType);

DatabaseNodeset *
AllocateData(DatabaseNodeset *Db, int SizeToIterate /*const char *NodeName*/);

DatabaseNodeset *ResetStorage(DatabaseNodeset *Db, int SizeToIterate);

// A very simple function
DatabaseNodeset *
SetupNodeStorage(
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes,
	char DbNames[1000][100],
	char *RecentNodeName,
	int SizeToIterate
);

void CheckStorage(DatabaseNodeset *Db, int SizeToIterate, char *NodeName);
