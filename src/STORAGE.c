/* 
	Source code of all storage of the Database Node
*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "CORE_types.h"

extern int _CGE;
int ErrStatus;

int
UpdateStorage(DatabaseNodeset *Db,int *ToChange,int changeBy, int Maxed){

	*ToChange += changeBy;

	/*
	 * Maxed: Set the Database Nodes storage to a maximum, so if the new storage amount is anywhere near Maxed,
	 * it rounds it up. If it's above Maxed, it rounds it  down
	*/

	if(*ToChange > Maxed) {
		int All = Db->CoreInfo.NodeStorage.MaxFileSize + Db->CoreInfo.NodeStorage.MaxStringSize + Db->CoreInfo.NodeStorage.MaxIntegerSize;

		if(All > Db->CoreInfo.NodeStorage.MaxStorageTotal) {
			ErrStatus = (_CGE == 0) ? StorageAboveMax : Failure;
			RETURNERRINFO("\033[1;33m", ErrStatus);

			Db->CoreInfo.NodeStorage.MaxFileSize = 40000000/3;
			Db->CoreInfo.NodeStorage.MaxStringSize = 40000000/3;
			Db->CoreInfo.NodeStorage.MaxIntegerSize=40000000/3;
		}
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
void
SetupNodeStorage(
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes
) {

	// Storage is factored into the enum Storage in CORE.c, just not set to the Datbase Node
	DbNode->CoreInfo.NodeStorage.MaxFileSize = Sizes->MaxFileSize;
	DbNode->CoreInfo.NodeStorage.MaxStringSize = Sizes->MaxStringSize;
	DbNode->CoreInfo.NodeStorage.MaxIntegerSize = Sizes->MaxIntegerSize;
	DbNode->CoreInfo.NodeStorage.MaxStorageUpgrade=50000;
	/* 
	 *	DbNode->CoreInfo.NodeStorage.MaxStorageTotal:
	 *	This will be the total ammount of storage of all the   Storages combined
	 */
	DbNode->CoreInfo.NodeStorage.MaxStorageTotal=Sizes->MaxStorageTotal;

	// This needs to be done in SetupNodeStorage, sets all of them to zero since no storage is being used as of thus far
	DbNode->CoreInfo.StorageUsed.TotalFileStorageUsed=0;
	DbNode->CoreInfo.StorageUsed.TotalStringStorageUsed=0;
	DbNode->CoreInfo.StorageUsed.TotalIntegerStorageUsed=0;

	// Sizes aren't needed anymore
	free(Sizes);
}
