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
char DbNames[500];

// Opens a file and checks for certain names in it
static int
CheckFile(char *FileName, char *LookFor) {
	char Read[200];
	int ExitCode;

	FILE *OpenCheck;
	OpenCheck = fopen(FileName,"r");
	if(OpenCheck == NULL) {
		printf("Error finding file %s",FileName);
	} else {
		fread(Read,1,sizeof(char)*40,OpenCheck);
		fclose(OpenCheck);

		if(strcmp(Read,LookFor) == 0) {
			printf("%s found in file %s\n",LookFor,FileName);
			ExitCode = FoundInOtherFile;
		} else {
			ExitCode = 0;
		}
	}

	return ExitCode;
}

void SetupDatabaseNode(
	char *DatabaseNode,
	bool CoreGenereatedErrs,
	bool NodeCanRead,
	char *Era
) {
	static int InitId = 1;
	static int DefDb = 0;
	static int InitUpd = 0;
	static int upds = 1;
	AddInfo Add_Info;
	DatabaseNodeset * NodeSetup = (DatabaseNodeset *) malloc(sizeof(DatabaseNodeset));
	
	if(DefDb != -1) {
		if(strcmp(DatabaseNode,"default") == 0) {
			DatabaseNode = DefDbNodeNames[DefDb];
			if(DefDb != 3)
				DefDb++;
			else
				DefDb = -1;
			printf("Yep");
		} else {
			FILE *Created;
			if(InitUpd > 0) {
				if(CheckFile("CreatedNodeName",DatabaseNode) == 			FoundInOtherFile) {
					exit(FoundInOtherFile);
				}
			}

			Created = fopen("CreatedNodeName","w");
			fwrite(DatabaseNode,1,sizeof(char)*80,Created);
			fclose(Created);

			strcpy(&DbNames[InitUpd],DatabaseNode);

			// Add Info
			Add_Info.AddId = InitUpd+1;
			char AddDetails[150];
			sprintf(AddDetails,"Added Database Node %s",DatabaseNode);
			strcpy(Add_Info.NameOfNode[InitUpd],AddDetails);

			++InitUpd;
		}
	} else {
		printf("You can only assign 4 default Database Nodes\n");
		exit(EXIT_FAILURE);
	}

	DatabaseNodeName = DatabaseNode;
	_CGE = (CoreGenereatedErrs) ? 0:1;
	DatabaseNodeset * NodeSetup_ = (DatabaseNodeset *) malloc(sizeof(DatabaseNodeset));

	NodeSetup_->NodeId = InitUpd;
}
