/* 
	structs and other data structures needed for
	the project
*/

#include <stdio.h>

// This enum stores the storage ammount of each Database Node
// Asscociated with NodeSizes
enum Storage {FileStorage=0,StringStorage=0,IntegerStorage=0};

// Keeps track of Database Nodes added
typedef struct {
	int AddId;
	char NameOfNode[500][100];
} AddInfo;

// This will store sizes the Database Nodes have
typedef struct {
	int MaxFileSize;
	int MaxStringSize;
	int MaxIntegerSize;
} NodeSizes;

// This will be for the Main Database Node, or for the Database Node that sets up the whole application
/* 
	The DefaultNodeSetup is set with Era "NUN" because there is no era types when the DefaultDatabaseNode is setup
*/
typedef struct {
	// We want to keep the name
	char *NodeName;
	// Has a different type of id
	char Id[150];
	// ERAS it will set up
	// 4 default ERAS, needs no more than 20 characters
	char ERAS[4][20];
} DefaultMainDbNode;

// Will continue the work upon the DefaultMainDbNode
// Return 0 if it is fully setup, else 1
static int
DefaultDbNode(DefaultMainDbNode *DefDbMainNode, int MaxFileSize, int MaxStringSize, int MaxIntegerSize);

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
