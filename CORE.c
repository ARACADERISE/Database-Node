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
int ErrStatus;
// This is Default db names
static char * DefDbNodeNames[] = {
	// DEFAULT NAMES
	"Default01", // Default db, user can assign era type
	"Tyme7", // Default db, user can assign era type
	"FileReader", // Defaut db, can only read files
	"FileWriter" // Default db, can only write files
};
// This is user created Database Node names
// This is needed due to the fact if we set calloc(500, sizeof(DefDbNodeNames)*80)
// To DefDbNodeNames, it appends all user created names
// To the begginning. So instead, we create a list of strings
// that can hold 500 Database Node names with a length of 100
static char DbNames[500][100];

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
	char ID[50];

	FileToSaveData = fopen(StoreInFile,"w");
	
	// This will write all data into seperate files about the added Database Node
	fputs(UpdateInfo,FileToSaveData);
	fputs("\n",FileToSaveData);
	sprintf(ID,"%d",AddId);
	fputs(ID,FileToSaveData);

	fclose(FileToSaveData);
	
	// We want to free up the memory for the next added Database Node
	free(AddedInfo);

	return 0;
};

// Finsishes setting up Default Database Node
static int
DefaultDbNode(DefaultMainDbNode *DefDbMainMode, const int MaxFileSize, const int MaxStringSize, const int MaxIntegerSize) {
	NodeSizes * Sizes = (NodeSizes *) malloc(sizeof(NodeSizes));

	Sizes->MaxFileSize = MaxFileSize;
	Sizes->MaxStringSize = MaxStringSize;
	Sizes->MaxIntegerSize = MaxIntegerSize;

	// Changing the value of the enum Storage
	enum Storage sir;
	sir=FileStorage;
	sir += Sizes->MaxFileSize;
	sir=StringStorage;
	sir += Sizes->MaxStringSize;
	sir=IntegerStorage;
	sir += Sizes->MaxIntegerSize;

	return 0;
}

// Opens a file and checks for certain names in it
static int
CheckFile(char *FileName, char *LookFor) {
	char Read[200];
	ErrStatus = (_CGE == 0) ? FoundInOtherFile : Failure;

	FILE *OpenCheck;
	OpenCheck = fopen(FileName,"r");
	if(OpenCheck == NULL) {
		printf("Error finding file %s",FileName);
	} else {
		fread(Read,1,sizeof(char)*40,OpenCheck);
		fclose(OpenCheck);

		if(strcmp(Read,LookFor) == 0) {
			printf("\033[1;31mERROR: %s found in file %s\nERR_STATUS_%d\n\n",LookFor,FileName,ErrStatus);
			exit(ErrStatus);
		}
	}

	return ErrStatus;
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
	DefaultMainDbNode * DefDbNode = (DefaultMainDbNode *) malloc(sizeof(DefaultMainDbNode));

	// Specifiers for functions
	char FileName[50];
	char DefaultDbNodeId[150];

	if(strcmp(DatabaseNode,"DefaultNodeSetup") == 0) {
		if(!(strcmp(Era,"NUN")==0)) {
			ErrStatus = (_CGE == 0) ? DefaultNodeSetupEraTypeNotNun : Failure;
			printf("\033[0;33mDefaultNodeSetup needs a Era of type NUN, not %s\n\tERR_STATUS_%d\n\n",Era,ErrStatus);
			exit(ErrStatus);
		}

		// Getting ideals for struct data
		sprintf(DefaultDbNodeId,"DEFDBNODEID[%d~%d~%d]",InitUpd+1,(_CGE),rand());
		strcpy(DefDbNode->Id,DefaultDbNodeId);
		// 4 default signals
		strcpy(DefDbNode->ERAS[0],"wro"); // Read/Write files
		strcpy(DefDbNode->ERAS[1],"ro"); // Read only type of Node
		strcpy(DefDbNode->ERAS[2],"wo"); // Write only type of node
		strcpy(DefDbNode->ERAS[3],"da"); // Checker type of Database. Read only type, but can do more with the data
		DefDbNode->NodeName = DatabaseNode;

		// Finishing up the Default Database Node
		// These are big sizes, but it'll be needed when the Database Nodes are put to work
		DefaultDbNode(DefDbNode,20000,15000,10000);
	} else {
		if(strcmp(Era,"NUN") == 0) {
			ErrStatus = (_CGE == 0) ? DeclarationOfEraNun : Failure;
			printf("\033[1;31mERROR: You're trying to assign Era type of NUN to your Database Node %s\nNUN Is defaultly assigned to DefaultNodeSetup.\n\tERR_STATUS_%d\n\n",DatabaseNode,ErrStatus);
			exit(ErrStatus);
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
			strcpy(DbNames[InitUpd],DatabaseNode);

			if(!(strcmp(DatabaseNode,"DefaultNodeSetup") == 0)) {
				int Times = 1;
				for(int i = 0; i < InitUpd; i++) {
					if(strcmp(DbNames[i],DatabaseNode) == 0) {
						++Times;
					}
				}
				if(Times > 1) {
					ErrStatus = (_CGE == 0) ? DatabaseNodeAlreadyCreated : Failure;
					printf("\033[1;31mERROR: You attempted to make the same Database Node.\n\tERR_STATUS_%d\n\n",ErrStatus);
					exit(ErrStatus);
				}
			} else {
				Created = fopen("CreateDefaultNode","w");
				fputs("Default Database Node created successfully\n",Created);
				fputs(DefDbNode->Id,Created);
				fclose(Created);

				// Instead of wasting lines in CORE.c, we're going to write a python file to easily do the work
				system("python Python/DefaultNode.py");
			}

			int TimesFound = 0;
			for(int i = 0; i < InitUpd; i++) {
				if(strcmp(DbNames[i],"DefaultNodeSetup") == 0) {
					++TimesFound;
				}
			}
			if(TimesFound > 1) {
				ErrStatus = (_CGE == 0) ? MoreThanOneDefaultNodeCreated : Failure;
				printf("\033[1;31mERROR: You attempted to make multiple Default Database Nodes.\n\tERR_STATUS_%d\n\n",ErrStatus);
				exit(ErrStatus);
			}

			// Add Info
			Add_Info->AddId = InitUpd+1;
			char AddDetails[150];
			sprintf(AddDetails,"Added Database Node %s",DbNames[InitUpd]);
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

	// Going through all the appended Database Node names to see if DefaultNodeSetup is in it
	static int times;
	for(int i = 0; i < InitUpd; i++) {
		if(strcmp(DbNames[i],"DefaultNodeSetup") == 0)
			times++;
	}
	if(times < 1) {
		if(times != 1) {
			ErrStatus = (_CGE == 0) ? DefaultNodeSetupNotFound : Failure;
			printf("\033[1;31mERROR: DefaultNodeSetup is needed for the application.\n\tERR_STATUS_%d\n\n",ErrStatus);
			FILE *Error;

			// Writing error to DefaultNodeSetup ERROR
			Error = fopen("DefaultNodeSetup ERROR","w");
			fputs("Error with setting up/finding Database Node: DatabaseNodeSetup",Error);
			fclose(Error);

			exit(ErrStatus);
		}
	}
}
