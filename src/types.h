/* 
	structs and other data structures needed for
	the project
*/

#include <stdbool.h>

// This enum stores the storage ammount of each Database Node
// Asscociated with NodeSizes
// enum Storage {FileStorage=0,StringStorage=0,IntegerStorage=0};

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
	int MaxStorageTotal;
	int MaxStorageAllowed;
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

// This will be for SetupEra.c
typedef struct {
	char *Era;
	char *Action;
} EraSetup;

// Sets up primal storage for the Nodes
static int
SetupDbNodeStorage(/*DefaultMainDbNode *DefDbMainNode,*/ const int MaxFileSize, const int MaxStringSize, const int MaxIntegerSize, NodeSizes *Sizes);

// This is for AddedInfo
static inline int
StoreInFile(int AddId, char UpdateInfo[500], char *StoreInFile, AddInfo *AddedInfo);

// Used to keep track of reset information
typedef struct {
	int ResetId;
	char *DatabaseNode;
} Reset;

// Used when setting up the core of the Database Node
// All data stored before this struct will be freed after being assigned to in this struct
typedef struct {
	int NodeId[1000];
	struct {
		bool Core_Generated_Errs;
		bool CanRead;
		struct {
			char *EraType;
			char *EraAction; // We need this so we don't waste code in other files
		} NodeEra;
		struct {
			int MaxFileSize[1000];
			int MaxStringSize[1000];
			int MaxIntegerSize[1000];
			int MaxStorageTotal[1000];
			/* 
				* Sizes is freed in SetupNodeStorage, so we have to store the max storage allowed somewhere
				* It will ALWAYS be 40000000
			*/
			int MaxStorageAllowed;
			int MaxStorageUpgrade;
		} NodeStorage;
		bool Allocatedata;
		// This is used to allocate data;
		struct {
			int AllocatedMaxFileSize[1000];
			int AllocatedMaxStringSize[1000];
			int AllocatedMaxIntegerSize[1000];
			int AllocatedTotal[1000];
		} AllocatedStorage;
		struct {
			int TotalFileStorageUsed[1000];
			int TotalStringStorageUsed[1000];
			int TotalIntegerStorageUsed[1000];
			int Total[1000];
		} StorageUsed;
		char NodeName[1000][100]; // Storing a thousand Node Names
	} CoreInfo;
} DatabaseNodeset;
