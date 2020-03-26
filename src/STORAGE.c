/* 
	Source code of all storage of the Database Node
*/

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int
UpdateStorage(int *ToChange,int changeBy){return 0;}

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

	// Sizes aren't needed anymore
	free(Sizes);
}
