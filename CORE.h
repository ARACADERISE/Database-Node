/* 
	Sets up the core of the users Database Node.

	Basically, it does all of the backend work of setting
	up what the Database Node does, what it can and cannot
	do, and the functionalities going into it
*/

#include <stdio.h>
#include <stdbool.h>

char *DatabaseNodeName;
bool _CGE;
static char * DbNodeNames[] = {
	// DEFAULT NAMES(12-15)
	"Default01", // Default db, user can assign era type
	"Tyme7", // Default db, user can assign era type
	"FileReader", // Defaut db, can only read files
	"FileWriter" // Default db, can only write files

	// User defined Database Nodes defined from index 4+
};

typedef struct {
	int ResetIt;
	char *DatabaseNode;
} Reset;

typedef struct {
	int NodeId;
	struct {
		bool Core_Generated_Errs;
		bool CanRead;
		char *EraType;
	} CoreInfo;
} DatabaseNodeset;

void SetupDatabaseNode(
	char *DatabaseNode,
	bool CoreGenereatedErrs,
	bool NodeCanRead,
	char *Era
);
