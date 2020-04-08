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
	char Action;
	char NameOfNode;
} AddInfo;

// This will store sizes the Database Nodes have
typedef struct {
	size_t MaxFileSize;
	size_t MaxStringSize;
	size_t MaxIntegerSize;
	size_t MaxStorageTotal;
	size_t MaxStorageAllowed;
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
			size_t MaxFileSize[1000];
			size_t MaxStringSize[1000];
			size_t MaxIntegerSize[1000];
			size_t MaxStorageTotal[1000];
			/* 
				* Sizes is freed in SetupNodeStorage, so we have to store the max storage allowed somewhere
				* It will ALWAYS be 40000000
			*/
			size_t MaxStorageAllowed;
			size_t MaxStorageUpgrade;
		} NodeStorage;
		bool Allocatedata;
		// This is used to allocate data;
		struct {
			size_t AllocatedMaxFileSize[1000];
			size_t AllocatedMaxStringSize[1000];
			size_t AllocatedMaxIntegerSize[1000];
			size_t AllocatedTotal[1000];
		} AllocatedStorage;
		struct {
			size_t TotalFileStorageUsed[1000];
			size_t TotalStringStorageUsed[1000];
			size_t TotalIntegerStorageUsed[1000];
			size_t Total[1000];
		} StorageUsed;
		char NodeName[1000][100]; // Storing a thousand Node Names
	} CoreInfo;

	// This will lead to using ExtraDatabaseNodeSet
	bool ExtraNodeSetNeeded;
} DatabaseNodeset;

/* 
	* Secondary holder for node information 
	* a thousand more of pretty much everything
*/
typedef struct {
	DatabaseNodeset *ExtraDb;
} ExtraDatabaseNodeSet;
