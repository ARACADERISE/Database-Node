/* 
	Sets up the core of the users Database Nodes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"
#include "CORE_types.h"

char *DatabaseNodeName;
int _CGE;
// This will append names created by the user
static char * DbNodeNames[] = {
	// DEFAULT NAMES(14-17)
	"Default01", // Default db, user can assign era type
	"Tyme7", // Default db, user can assign era type
	"FileReader", // Defaut db, can only read files
	"FileWriter" // Default db, can only write files

	// User defined Database Nodes defined from index 4+
};

void SetupDatabaseNode(
	char *DatabaseNode,
	bool CoreGenereatedErrs,
	bool NodeCanRead,
	char *Era
) {
	static int InitId = 0;
	static int DefDb = 0;
	DatabaseNodeset * NodeSetup = (DatabaseNodeset *) malloc(sizeof(DatabaseNodeset));
	
	if(DefDb != -1) {
		if(strcmp(DatabaseNode,"default "/*Space needed due to /0 at end of string*/)) {
			DatabaseNode = DbNodeNames[DefDb];
			if(DefDb != 3) {
				DefDb++;
			}
			else {
				DefDb = -1;
			}
		}
	} else {
		printf("You can only assign 4 default Database Nodes\n");
		exit(EXIT_FAILURE);
	}

	DatabaseNodeName = DatabaseNode;
	_CGE = (CoreGenereatedErrs) ? 0:1;
}
