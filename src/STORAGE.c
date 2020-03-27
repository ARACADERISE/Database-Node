/* 
	Source code of all storage of the Database Node
*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "CORE_types.h"

extern int _CGE;

int ErrStatus;

DatabaseNodeset *ResetStorage(DatabaseNodeset *Db) {

	// Checking allocated data
	if(Db->CoreInfo.AllocatedData) {
		
	}

	return 0;
}

DatabaseNodeset *
AllocateData(DatabaseNodeset *Db) {
	return Db;
}

DatabaseNodeset *
UpdateStorage(DatabaseNodeset *Db,int *ToChange,int changeBy, int Maxed, int SizeToIterate){

	*ToChange += changeBy;

	/*
	 * Maxed: Set the Database Nodes storage to a maximum, so if the new storage amount is anywhere near Maxed,
	 * it rounds it up. If it's above Maxed, it rounds it  down
	*/

	if(*ToChange > Maxed) {
		int All;
		for(int i = 0; i < SizeToIterate+1; i++) {
			All = Db->CoreInfo.NodeStorage.MaxFileSize[i] + Db->CoreInfo.NodeStorage.MaxStringSize[i] + Db->CoreInfo.NodeStorage.MaxIntegerSize[i];

			if(All > Db->CoreInfo.NodeStorage.MaxStorageTotal[i]) {
				ErrStatus = (_CGE == 0) ? StorageAboveMax : Failure;
				RETURNERRINFO("\033[1;33m", ErrStatus);

				Db->CoreInfo.NodeStorage.MaxFileSize[i] = 40000000/3;
				Db->CoreInfo.NodeStorage.MaxStringSize[i] = 40000000/3;
				Db->CoreInfo.NodeStorage.MaxIntegerSize[i]=40000000/3;

				system("clear"); // We don't want to keep all that information printed
			}
		}
		
		int Sub = Maxed-*ToChange;
		*ToChange = *ToChange + Sub;
	}
	else {
		int AmLeft;
		if(Maxed-*ToChange <= 500) {
			AmLeft = Maxed-*ToChange;
			*ToChange += AmLeft;
		}
	}

	return 0;
}

// A very simple function
DatabaseNodeset *
SetupNodeStorage(
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes,
	int SizeToIterate
) {

	// Storage is factored into the enum Storage in CORE.c, just not set to the Datbase Node
	for(int i = 0; i < SizeToIterate+1; i++) {
		DbNode->CoreInfo.NodeStorage.MaxFileSize[i] = Sizes->MaxFileSize;
		DbNode->CoreInfo.NodeStorage.MaxStringSize[i] = Sizes->MaxStringSize;
		DbNode->CoreInfo.NodeStorage.MaxIntegerSize[i] = Sizes->MaxIntegerSize;
	}
	DbNode->CoreInfo.NodeStorage.MaxStorageUpgrade=50000;
	for(int i = 0; i < SizeToIterate+1; i++) {
			/* 
		*	DbNode->CoreInfo.NodeStorage.MaxStorageTotal:
		*	This will be the total ammount of storage of all the   Storages combined
		*/
		DbNode->CoreInfo.NodeStorage.MaxStorageTotal[i]=Sizes->MaxStorageTotal;

		// This needs to be done in SetupNodeStorage, sets all of them to zero since no storage is being used as of thus far
		DbNode->CoreInfo.StorageUsed.TotalFileStorageUsed[i]=0;
		DbNode->CoreInfo.StorageUsed.TotalStringStorageUsed[i]=0;
		DbNode->CoreInfo.StorageUsed.TotalIntegerStorageUsed[i]=0;
	}

	// Sizes aren't needed anymore
	free(Sizes);

	return 0;
}
