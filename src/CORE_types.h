/* 
	Keep Note:
		The Core Generated Errs/Types are for the err status,
		or the status of which the error occured which is
		represented by a number. The exit will then return
		the number, with printing what the error was.

		_CGE Is not used majorly depended on in this file, but errors returned in other files are 
		majorly dependent on _CGE
*/

#include <stdio.h>
#include <stdlib.h>

//extern int _CGE;

// Default Errors
#  define CoreConErr                        2 // Starts at 2 since Failure is 1
#  define FileConErr                        3
#  define NotDumped                         4
#  define FoundInOtherFile                  5
// ERA errors
#  define DeclarationOfEraNun               6
#  define DefaultNodeSetupEraTypeNotNun     7
#  define NotAEraType                       8
// Default Database Node errors
#  define DefaultNodeSetupNotFound          9
#  define DefaultDbNodeNotFullySetup        10
#  define MoreThanOneDefaultNodeCreated     11
// User created Database Node errors
#  define DatabaseNodeAlreadyCreated        12
// Storage Errors
#  define StorageAboveMax                   13
#  define StorageAddOverload                14
#  define AllocatingStorageWithSizeZero     15
#  define ResetingStorageOfSizeZero         16
#  define MaxedAboveTotalStorageAllowed     17 // STORAGE.c argument error
// Regular success/fail errors
#  define Failure                           1
#  define Success                           0

#define RETURNERRINFO(COLOR,TYPE)                                                                                                                     \
	if(TYPE == CoreConErr) {                                                                                                                      \
		printf("%sError connection with core. \n\tReturn Exit status %d\n",COLOR,CoreConErr);                                                 \
	}                                                                                                                                             \
	else if(TYPE == FileConErr) {                                                                                                                 \
		printf("%sError connecting/finding file. \n\tReturn Exit status %d\n",COLOR,FileConErr);                                              \
	}                                                                                                                                             \
	else if(TYPE == FoundInOtherFile) {                                                                                                           \
		printf("%sThe string/number/character was found in another file. \n\tReturn Exit status %d\n",COLOR,FoundInOtherFile);                \
	}                                                                                                                                             \
	else if(TYPE == MaxedAboveTotalStorageAllowed) { \
		printf("%sArgument Maxed cannot be set to any value above 40000000.\n\tERR_STATUS_%d",COLOR,MaxedAboveTotalStorageAllowed);\
	}\
	else if(TYPE == DeclarationOfEraNun) {                                                                                                        \
		printf("%sAttempt to set a Era type of NUN to your Database Node. \n\tERR_STATUS_%d\n",COLOR,DeclarationOfEraNun);                    \
	}                                                                                                                                             \
	else if(TYPE == DefaultNodeSetupNotFound) {                                                                                                   \
		printf("%sThe DefaultNodeSetup Database Node was not found.\n\tERR_STATUS_%d\n",COLOR,DefaultNodeSetupNotFound);                      \
	}                                                                                                                                             \
	else if(TYPE == DefaultNodeSetupEraTypeNotNun) {                                                                                              \
		printf("%sThe Era type of the Default Database Node is required to be NUN.\n\tERR_STATUS_%d\n",COLOR,DefaultNodeSetupEraTypeNotNun);  \
	}                                                                                                                                             \
	else if(TYPE == DefaultDbNodeNotFullySetup) {                                                                                                 \
		printf("%sThe Default Database Node is not fully set up yet.\n\tERR_STATUS_%d\n",COLOR,DefaultDbNodeNotFullySetup);                   \
	}                                                                                                                                             \
	else if(TYPE == MoreThanOneDefaultNodeCreated) {                                                                                              \
		printf("%sAttempted to create more than one Default Database Node.\n\tERR_STATUS_%d\n",COLOR,MoreThanOneDefaultNodeCreated);          \
	}                                                                                                                                             \
	else if(TYPE == DatabaseNodeAlreadyCreated) {                                                                                                 \
		printf("%sAttempted to create a already existing Database Node.\n\tERR_STATUS_%d\n",COLOR,DatabaseNodeAlreadyCreated);                \
	}                                                                                                                                             \
	else if(TYPE == NotAEraType) {                                                                                                                \
		printf("%sAttempted to assign an unexisting Era type to the Database node.\n\tERR_STATUS_%d\n",COLOR,NotAEraType);                    \
	}                                                                                                                                             \
	else if(TYPE == StorageAboveMax) {                                                                                                            \
		printf("%sTotal storage ammount reached for the Database Node.\n\tERR_STATUS_%d\nReallocating memory for the Database Nodes storage...",COLOR,StorageAboveMax);                              \
	}                                                                                                                                             \
	else if(TYPE == StorageAddOverload) {                                                                                                         \
		printf("%sAdding too much storage. Total of 50000 storage segments can be added at once.\n\tERR_STATUS_%d\n",COLOR,StorageAddOverload); \
	}                                                                                                                                             \
	else if(TYPE == AllocatingStorageWithSizeZero) {\
		printf("%sCannot allocate data of zero to your Database Node.\n\t\033[4;36m_WARNING_STATUS_%d\n\n\033[0;m",COLOR,AllocatingStorageWithSizeZero); \
	} \
	else if(TYPE == Failure) {                                                                                                                    \
		printf("%sFailed to compile successfully. \n\tReturn Exit status %d\n",COLOR,Failure);                                                \
	 }                                                                                                                                            \
	else if(TYPE == ResetingStorageOfSizeZero) {\
		printf("%sCannot reset a Database Nodes storage of size zero.\n\t\033[4;36m_WARNING_STATUS_%d\033[0;m",COLOR,ResetingStorageOfSizeZero); \
	} \
	else if(TYPE == Success) {                                                                                                                    \
		printf("%sProgram compiled successfully. \n\tReturn Exit status %d\n",COLOR,Success);                                                 \
	}                                                                                                                                             \
	else {                                                                                                                                        \
		printf("%s",COLOR);                                                                                                                   \
		printf("Unknown return type\n");                                                                                                      \
	}
