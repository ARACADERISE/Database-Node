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
	int MaxFileSize,
	int MaxStringSize,
	int MaxIntegerSize,
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes
) {

	int ammountLeft;
	// Reallocates the storage defaulty
	// If this wants to be done later on the function UpdateStorage will have to be used
	if(MaxFileSize < 10000) {
		ammountLeft = 10000 - MaxFileSize;
		MaxFileSize += ammountLeft;
	}
	if(MaxStringSize < 20000) {
		ammountLeft = 20000 - MaxStringSize;
		MaxStringSize += ammountLeft;
	}
	if(MaxIntegerSize < 20000) {
		ammountLeft = 20000 - MaxIntegerSize;
		MaxIntegerSize += ammountLeft;
	}

	DbNode->CoreInfo.NodeStorage.MaxFileSize = MaxFileSize;
	DbNode->CoreInfo.NodeStorage.MaxStringSize = MaxStringSize;
	DbNode->CoreInfo.NodeStorage.MaxIntegerSize = MaxIntegerSize;

	free(Sizes);
}
