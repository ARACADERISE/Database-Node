/* 
	structs and other data structures needed for
	the project
*/

#include <stdio.h>


// Keeps track of Database Nodes added
typedef struct {
	int AddId;
	char NameOfNode[500][100];
} AddInfo;

static int
StoreInFile(int AddId, char UpdateInfo[500], char *StoreInFile, AddInfo *AddedInfo);

// Used to keep track of reset information
typedef struct {
	int ResetId;
	char *DatabaseNode;
} Reset;

// Used when setting up the core of the Database Node
typedef struct {
	int NodeId;
	struct {
		bool Core_Generated_Errs;
		bool CanRead;
		char *EraType;
		char *NodeName;
	} CoreInfo;
} DatabaseNodeset;
