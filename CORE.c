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
// This is Default db names
static char * DefDbNodeNames[] = {
	// DEFAULT NAMES
	"Default01", // Default db, user can assign era type
	"Tyme7", // Default db, user can assign era type
	"FileReader", // Defaut db, can only read files
	"FileWriter" // Default db, can only write files
};
// This is user created name
// This is needed due to the fact if we set calloc(500, sizeof(DefDbNodeNames)*80)
// To DefDbNodeNames, it appends all user created names
// To the begginning
char *DbNames;

void SetupDatabaseNode(
	char *DatabaseNode,
	bool CoreGenereatedErrs,
	bool NodeCanRead,
	char *Era
) {
	static int InitId = 0;
	static int DefDb = 0;
	static int InitUpd = 0;
	DatabaseNodeset * NodeSetup = (DatabaseNodeset *) malloc(sizeof(DatabaseNodeset));
	
	if(DefDb != -1) {
		if(strcmp(DatabaseNode,"default" /*Space needed due to /0 at end of string*/) == 0) {
			DatabaseNode = DefDbNodeNames[DefDb];
			if(DefDb != 3)
				DefDb ++;
			else
				DefDb = -1;
			printf("Yep");
		} else {
			DbNames = calloc(500, sizeof(DbNames)*80);
			strcpy(&DbNames[InitUpd],DatabaseNode);
			InitUpd++;
		}
	} else {
		printf("You can only assign 4 default Database Nodes\n");
		exit(EXIT_FAILURE);
	}

	DatabaseNodeName = DatabaseNode;
	_CGE = (CoreGenereatedErrs) ? 0:1;
}
