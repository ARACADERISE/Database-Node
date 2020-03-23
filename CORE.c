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
static int ExitCode = 0;
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

// From types.h. Declared in types.h, given functionality
// in CORE.c.
// MEANT FOR AddInfo struct, nothing else
static int 
StoreInFile(
	int AddId, 
	char UpdateInfo[500], 
	char *StoreInFile,
	AddInfo *AddedInfo
){
	FILE *FileToSaveData;

	FileToSaveData = fopen(StoreInFile,"w");
	
	// This will write all data into seperate files about the added Database Node
	fputs("\n",FileToSaveData);
	fwrite(&AddId,1,sizeof(int),FileToSaveData);
	fputs("\n",FileToSaveData);
	fputs(UpdateInfo,FileToSaveData);

	fclose(FileToSaveData);
	
	// We want to free up the memory for the next added Database Node
	free(AddedInfo);

	return 0;
};

// Opens a file and checks for certain names in it
static int
CheckFile(char *FileName, char *LookFor) {
	char Read[200];
	int ErrStatus = (_CGE == 0) ? FoundInOtherFile : Failure;

	FILE *OpenCheck;
	OpenCheck = fopen(FileName,"r");
	if(OpenCheck == NULL) {
		printf("Error finding file %s",FileName);
	} else {
		fread(Read,1,sizeof(char)*40,OpenCheck);
		fclose(OpenCheck);

		if(strcmp(Read,LookFor) == 0) {
			printf("\033[1;31mERROR: %s found in file %s\nERR_STATUS_%d\n\n",LookFor,FileName,ErrStatus);
			ExitCode = ErrStatus;
			exit(ExitCode);
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
	AddInfo * Add_Info = (AddInfo *) malloc(sizeof(AddInfo));
	DatabaseNodeset * NodeSetup = (DatabaseNodeset *) malloc(sizeof(DatabaseNodeset));

	// Specifiers for functions
	char FileName[50];
	char DefaultDbNodeId[150];

	if(strcmp(DatabaseNode,"DefaultNodeSetup") == 0) {
		DefaultMainDbNode * DefDbNode = (DefaultMainDbNode *) malloc(sizeof(DefaultMainDbNode));

		// Getting ideals for struct data
		sprintf(DefaultDbNodeId,"DEFDBNODEID[%d~%d]",InitUpd,(_CGE));
		strcpy(DefDbNode->Id,DefaultDbNodeId);
		// 4 default signals
		strcpy(DefDbNode->ERAS[0],"wro"); // Read/Write files
		strcpy(DefDbNode->ERAS[1],"ro"); // Read only type of Node
		strcpy(DefDbNode->ERAS[2],"wo"); // Write only type of node
		strcpy(DefDbNode->ERAS[3],"da"); // Checker type of Database. Read only type, but can do more with the data
	} else {
		if(strcmp(Era,"NUN") == 0) {
			printf("\033[1;31mERROR: You're trying to assign Era type of NUN to your Database Node\nNUN Is defaultly assigned to DefaultNodeSetup.\n");
			exit(DeclarationOfEraNun);
		}
	}
	
	if(DefDb != -1) {
		if(strcmp(DatabaseNode,"default") == 0) {
			DatabaseNode = DefDbNodeNames[DefDb];
			if(DefDb != 3)
				DefDb++;
			else
				DefDb = -1;
		} else {
			FILE *Created;
			if(InitUpd > 0) {
				CheckFile("CreatedNodeName",DatabaseNode);
			}

			Created = fopen("CreatedNodeName","w");
			fwrite(DatabaseNode,1,sizeof(char)*40,Created);
			fclose(Created);

			strcpy(&DbNames[InitUpd],DatabaseNode);

			// Add Info
			Add_Info->AddId = InitUpd+1;
			char AddDetails[150];
			sprintf(AddDetails,"Added Database Node %s",&DbNames[InitUpd]);
			strcpy(*Add_Info->NameOfNode,AddDetails);

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
	sprintf(FileName,"Node Information #%d",InitUpd);
	StoreInFile(Add_Info->AddId,*Add_Info->NameOfNode,FileName,Add_Info);
}
