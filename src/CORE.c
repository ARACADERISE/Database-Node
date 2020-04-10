/* 
	Sets up the core of the users Database Nodes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Library Needed for DefaultNodeSetup ID
#include <stdbool.h>
#include <dirent.h> // Library needed for SetupNode function
#include "types.h"
#include "CORE_types.h"
#include "SetupEra.h"
#include "STORAGE.h"

char *DatabaseNodeName;
int _CGE;
int ErrStatus;
bool AllocatedData;
// This is Default db names
static char * DefDbNodeNames[] = {
	// DEFAULT NAMES
	"DbNodeDef", // Default db, user can assign era type
	"Tyme", // Default db, user can assign era type
	"FileReader", // Defaut db, can only read files
	"FileWriter" // Default db, can only write files
};
// This is user created Database Node names
// This is needed due to the fact if we set calloc(1000, sizeof(DefDbNodeNames)*80)
// To DefDbNodeNames, it appends all user created names
// To the begginning. So instead, we create a list of strings
// that can hold 1000 Database Node names with a length of 100
char DbNames[1000][100];

// From types.h. Declared in types.h, given functionality
// in CORE.c.
// MEANT FOR AddInfo struct, nothing else
static inline void 
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
};

// Finsishes setting up Default Database Node
static inline void
SetupDbNodeStorage(
	//DefaultMainDbNode *DefDbMainMode, 
	size_t MaxFileSize, // INIT: 10000+
	size_t MaxStringSize, // INIT: 20000+
	size_t MaxIntegerSize, // INIT: 20000+
	NodeSizes *Sizes
 ) {
	
	// Refactoring the storage to its initial storage ammount if it's below its init value
	int ammountLeft;
	if(MaxFileSize < 10000) {
		ammountLeft = 10000-MaxFileSize;
		MaxFileSize += ammountLeft;
	}
	if(MaxStringSize < 20000) {
		ammountLeft = 20000 - MaxStringSize;
		MaxStringSize += ammountLeft;
	}
	if(MaxIntegerSize < 20000) {
		ammountLeft = 20000 - MaxIntegerSize;
		MaxIntegerSize += ammountLeft;
	}

	Sizes->MaxFileSize = MaxFileSize;
	Sizes->MaxStringSize = MaxStringSize;
	Sizes->MaxIntegerSize = MaxIntegerSize;
	Sizes->MaxStorageTotal = MaxFileSize + MaxStringSize + MaxIntegerSize;
	Sizes->MaxStorageAllowed = 40000000; // 40 million! For ONE Database Node
}

// Opens a file and checks for certain names in it
static inline int
CheckFile(char *FileName, char *LookFor) {
	char Read[1000];
	ErrStatus = (_CGE == 0) ? FoundInOtherFile : Failure;

	FILE *OpenCheck;
	OpenCheck = fopen(FileName,"r");
	if(OpenCheck == NULL) {
		fprintf(stderr,"Error finding file %s",FileName);
	} else {
		fread(Read,1,sizeof(char)*40,OpenCheck);
		fclose(OpenCheck);

		if(strcmp(Read,LookFor) == 0) {
			RETURNERRINFO("\033[1;31m", ErrStatus);
			exit(ErrStatus);
		}
	}

	return ErrStatus;
}

void SetupDatabaseNode(
	char *DatabaseNode,
	bool CoreGenereatedErrs,
	bool NodeCanRead,
	bool AllocateData_,
	char *Era,
	size_t FileSize,
	size_t StringSize,
	size_t IntegerSize
) {
	static int InitId = 0;
	static int DefDb = 0;
	static int InitUpd = 0;

	// Struct ideals for the application
	AddInfo * Add_Info = (AddInfo *) malloc(sizeof(AddInfo));
	DatabaseNodeset *NodeSetup = (DatabaseNodeset *) malloc(sizeof(DatabaseNodeset));
	DefaultMainDbNode * DefDbNode = (DefaultMainDbNode *) malloc(sizeof(DefaultMainDbNode));
	NodeSizes * Sizes = (NodeSizes *) malloc(sizeof(NodeSizes));

	// 4 default ERAS
	strcpy(DefDbNode->ERAS[0],"wro"); // Read/Write files
	strcpy(DefDbNode->ERAS[1],"ro"); // Read only type of Node
	strcpy(DefDbNode->ERAS[2],"wo"); // Write only type of node
	strcpy(DefDbNode->ERAS[3],"da"); // Checker type of Database. Read only type, but can do more with the data


	// Default values
	SETDEFAULT(NodeSetup);

	// Specifiers for functions
	char FileName[50];
	char DefaultDbNodeId[150];

	if(strcmp(DatabaseNode,"DefaultNodeSetup") == 0) {

		/* Going through DbNames to see if DefaultNodeSetup is in it more than once.
		*/
		int timesFound = 1;
		for(int i = 0; i < InitUpd; i++) {
			if(strcmp(DbNames[i],"DefaultNodeSetup") == 0)
				timesFound++;
			break;
		}
		if(timesFound > 1) {
			ErrStatus = (_CGE == 0) ? MoreThanOneDefaultNodeCreated : Failure;
			RETURNERRINFO("\033[1;31m", ErrStatus);
			exit(ErrStatus);
		}

		if(!(strcmp(Era,"NUN")==0)) {
			ErrStatus = (_CGE == 0) ? DefaultNodeSetupEraTypeNotNun : Failure;
			RETURNERRINFO("\033[1;33m", ErrStatus);
			exit(ErrStatus);
			}

		srand(time(0));
		// Getting ideals for struct data
		sprintf(DefaultDbNodeId,"DEFDBNODEID[%d~%d~%d]",InitUpd+1,(_CGE),rand());
		strcpy(DefDbNode->Id,DefaultDbNodeId);
		
		DefDbNode->NodeName = DatabaseNode;
	} else {
		if(strcmp(Era,"NUN") == 0) {
			ErrStatus = (_CGE == 0) ? DeclarationOfEraNun : Failure;
			RETURNERRINFO("\033[1;31m", ErrStatus);
			exit(ErrStatus);
		}
		int EraNotFound = 0;
		for(int i = 0; i < 4/*Only 4 types of ERAS*/; i++) {
			if(!(strcmp(Era,DefDbNode->ERAS[i]) == 0)) {
				EraNotFound++;
			}
		}
		if(EraNotFound == 4/*Meaning the Era assigned to the Database Node doesn't exist*/) {
			ErrStatus = (_CGE == 0) ? NotAEraType : Failure;
			RETURNERRINFO("\033[1;31m",ErrStatus);
			exit(ErrStatus);
		}
	}
	
	if(DefDb!=-1) {
		if(strcmp(DatabaseNode,"default") == 0) {
	
			DatabaseNode = DefDbNodeNames[DefDb];
			if(!(DefDb == 4))DefDb++;
			else {
				fprintf(stderr,"\033[0;31mYou can only assign 4 default Database Nodes\n");
				exit(EXIT_FAILURE);
			}
			
			InitUpd++;
			InitId++;

			strcpy(DbNames[InitUpd],DatabaseNode);
		} else {
			FILE *Created;
			strcpy(DbNames[InitUpd],DatabaseNode);

			if(!(strcmp(DatabaseNode,"DefaultNodeSetup") == 0)) {
				static int Times = 1;
				for(int i = 0; i < InitUpd; i++) {
					if(strcmp(DbNames[i],DatabaseNode) == 0) {
						++Times;
					}
				}
				if(Times > 1) {
					ErrStatus = (_CGE == 0) ? DatabaseNodeAlreadyCreated : Failure;
					RETURNERRINFO("\033[1;31m", ErrStatus);
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

			/* Original code for catching more than one DefaultNodeSetup
			 * int TimesFound = 0;
			 * for(int i = 0; i <= InitUpd; i++) {
			 *	if(strcmp(DbNames[i],"DefaultNodeSetup") == 0) {
			 *		TimesFound++;
			 *	}
			 * }
			 * if(TimesFound > 1) {
			 *	ErrStatus = (_CGE == 0) ?  *MoreThanOneDefaultNodeCreated : Failure;
			 *	RETURNERRINFO("\033[1;31m", ErrStatus);
			 *	exit(ErrStatus);
			 * }
			 */

			InitUpd++;
			InitId++;
		}
	}

	if(!(strcmp(DatabaseNode,"DefaultNodeSetup")==0)) {

		// Add Info
		Add_Info->AddId = InitUpd;
		char AddDetails[150];
		sprintf(AddDetails,"Added Database Node %s",DbNames[InitUpd]);
		strcpy(&Add_Info->Action,AddDetails);
		strcpy(&Add_Info->NameOfNode, DatabaseNode);

		DatabaseNodeName = DatabaseNode;
		_CGE = (CoreGenereatedErrs) ? 0:1;

		// Setting the Node Id, DefaultNodeSetup does not get one
		NodeSetup->NodeId[InitId] = InitId;

		sprintf(FileName,"Node Information #%d",InitUpd);
		StoreInFile(Add_Info->AddId,&Add_Info->NameOfNode,FileName,Add_Info);

		// Going through all the appended Database Node names to see if DefaultNodeSetup is in it
		// Other errors will be raised before this, such as "Assigning Database Node to Era type NUN"
		static int times=0;
		for(int i = 0; i < InitUpd; i++) {
			if(strcmp(DbNames[i],"DefaultNodeSetup")==0)
				times++;
			break;
		}
		if(times < 1) {
			if(times != 1) {
				ErrStatus = (_CGE == 0) ? DefaultNodeSetupNotFound : Failure;
				RETURNERRINFO("\033[1;31m", ErrStatus);
				FILE *Error;

				// Writing error to DefaultNodeSetup ERROR
				Error = fopen("DefaultNodeSetup ERROR","w");
				fputs("Error with setting up/finding Database Node: DatabaseNodeSetup",Error);
				fclose(Error);

				exit(ErrStatus);
			}
		}
	}

	// The default Database Node doesn't need storage
	if(!(strcmp(DatabaseNode,"DefaultNodeSetup") == 0)) {
		// Giving meaning to the Era
		GatherEra(Era, DefDbNode, NodeSetup/*We give meaning to each ideal of the struct bit by bit*/);

		// Finishing up the Default Database Node
		SetupDbNodeStorage(FileSize,StringSize,IntegerSize, Sizes);

		//Sets up the storage
		if(InitUpd > 1) {
		  //InitUpd--;
		}

		NodeSetup->CoreInfo.StorageUsed.Total[InitUpd]=3000000+InitId;
		NodeSetup->CoreInfo.StorageUsed.TotalFileStorageUsed[InitUpd]=10000+InitId;
		NodeSetup->CoreInfo.StorageUsed.TotalStringStorageUsed[InitUpd]=20000+InitId;
		NodeSetup->CoreInfo.StorageUsed.TotalIntegerStorageUsed[InitUpd]=500000+InitId;

		/* 
			* DefaultNodeSetup has an NodeId of 1, meaning if the Nodes Id is 2, and AllocateData_ is true
		 	* we print a error to the terminal, and set AllocateData_ to false
		*/
		if(NodeSetup->NodeId[InitUpd]==2 && AllocateData_) {
			fprintf(stderr,"\033[0;43mCannot allocate from DefaultNodeSetup\n\tError on %s\t\033[0;32mReassigned\n\033[0;0m",DatabaseNode);
			AllocateData_=false;
		}
		
		// Allocating storage if true
		if(!(strcmp(DatabaseNode,"DefaultNodeSetup") == 0) &&AllocateData_) {
			NodeSetup->CoreInfo.Allocatedata=true;
			if(AllocatedData==true) {
				fprintf(stderr,"\033[0;43mCannot allocate storage from allocated storage.\n\tError on %s\t\033[0;32mReassigned\033[0;0m\n",DatabaseNode);
				AllocatedData=false;
			}
			else {
				AllocatedData = true;
			}
		} else {AllocatedData=false;/*Needs to be set to false else it will stay at true*/}

		SetupNodeStorage(NodeSetup, Sizes, DbNames, DatabaseNode,InitUpd);

		CheckStorage(NodeSetup, InitUpd,DatabaseNode);
	}
}

/* 
	I hate these types of function where it is pure input.
	Don't know why, just do, but this is needed, otherwise we would waist another 200 lines of code in CORE.c
	figuring out how to add another Database Node. So this is overall the easier choice
*/
void
SetupNode() {
	char NodeName[150], EraType[4];
	char AllocData[4], CanRead[4], CGE[4];
	bool AlocData, CanRead_, __CGE;
	size_t FileSize, StringSize, IntegerSize;

	//scanf("%s %s %s %s %s %d %d %d",NodeName,CGE,CanRead,AllocData,EraType,&FileSize, &StringSize, &IntegerSize);
	printf("Node Name: "); scanf("%s",NodeName);
	printf("Core Generated Errors(yes/no): "); scanf("%s",CGE);
	printf("Can Read(yes/no): "); scanf("%s",CanRead);
	printf("Allocate Data(yes/no): "); scanf("%s",AllocData);
	printf("Era Type(wro(Write/read), ro(Read only) wo (Write Only), da(Works with the information)): "); scanf("%s",EraType);
	printf("FileSize(must be 10000+): "); scanf("%ld",&FileSize);
	printf("StringSize(must be 20000+): "); scanf("%ld",&StringSize);
	printf("IntegerSize(must be 20000+): "); scanf("%ld",&IntegerSize);
	system("clear");

	if(strcmp(AllocData,"yes")==0)AlocData=true;
	else AlocData=false;
	if(strcmp(CanRead,"YES")==0)CanRead_=true;
	else CanRead_=false;
	if(strcmp(CGE,"yes")==0)__CGE=true;
	else __CGE=false;

	SetupDatabaseNode(NodeName,__CGE,CanRead_,AlocData,EraType,FileSize,StringSize,IntegerSize);
}
