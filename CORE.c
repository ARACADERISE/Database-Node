/* 
	Sets up the core of the users Database Nodes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char *DatabaseNodeName;
// This will append names created by the user
static char * DbNodeNames[] = {
	// DEFAULT NAMES(14-17)
	"Default01", // Default db, user can assign era type
	"Tyme7", // Default db, user can assign era type
	"FileReader", // Defaut db, can only read files
	"FileWriter" // Default db, can only write files

	// User defined Database Nodes defined from index 4+
};

typedef struct {
	int ResetId;
	char *DatabaseNode;
} Reset;

typedef struct {
	int NodeId;
	union {
		struct {
			// If true, can return error status other than 0 and 1
			// If false, can only return 10 for Core Failure Err
			bool Core_Generated_Errs;
			// If true, the Database Node can read files and print
			bool CanRead;
			// An Era type basically defines the whole use
			// of the Database Node
			// NOTE: The Database Node does not depend fully on
			// The era type
			char *EraType;
		} CoreInfo;
	} setup;
} DatabaseNodeset;

void SetupDatabaseNode(
	char *DatabaseNode,
	bool CoreGenereatedErrs,
	bool NodeCanRead,
	char *Era
) {
	static int InitId = 0;
	static int DefDb = 0;
	DatabaseNodeset * NodeSetup = (DatabaseNodeset *) malloc(sizeof(DatabaseNodeset));
	
	if(strcmp(DatabaseNode,"default "/*Space needed due to /0 at end of string*/)) {
		DatabaseNode = DbNodeNames[DefDb++];
		if(DefDb != 3)
			DefDb++;
		else
			DefDb = 0;
	}

	DatabaseNodeName = DatabaseNode;
	printf("%s",DatabaseNodeName);
}
