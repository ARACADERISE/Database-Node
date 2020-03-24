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

extern int _CGE;

#  define CoreConErr                     2 // Starts at 2 since Failure is 1
#  define FileConErr                     3
#  define NotDumped                      4
#  define FoundInOtherFile               5
// ERA errors
#  define DeclarationOfEraNun            6
#  define DefaultNodeSetupNotFound       7
#  define DefaultNodeSetupEraTypeNotNun  8
#  define DefaultDbNodeNotFullySetup     9
#  define MoreThanOneDefaultNodeCreated  10
#  define DatabaseNodeAlreadyCreated     11
#  define NotAEraType                    12
#  define Failure                        1
#  define Success                        0

#define CTYPES() \
	printf("TYPES: \n%s",(_CGE == 0) ? "\tCoreConErr - Err Status 2\n\tFileConErr - Err Status 3\n\tNotDumped - Err Status 4\n\tFoundInOtherFile - Err Status 5" : "\tFailure - Exit Status 1\n\tSuccess - Exit Status 0")

#define RETURNERRINFO(COLOR,TYPE)                                                                                                       \
	if(TYPE == CoreConErr) {                                                                                                        \
		printf("%sError connection with core. \n\tReturn Exit status %d\n",COLOR,CoreConErr);                                   \
	}                                                                                                                               \
	else if(TYPE == FileConErr) {                                                                                                   \
		printf("%sError connecting/finding file. \n\tReturn Exit status %d\n",COLOR,FileConErr);                                \
	}                                                                                                                               \
	else if(TYPE == FoundInOtherFile) {                                                                                             \
		printf("%sThe string/number/character was found in another file. \n\tReturn Exit status %d\n",COLOR,FoundInOtherFile);  \
	}                                                                                                                               \
	else if(TYPE == DeclarationOfEraNun) {                                                                                          \
		printf("%sAttempt to set a Era type of NUN to your Database Node. \n\tERR_STATUS_%d",COLOR,DeclarationOfEraNun);        \
	}                                                                                                                               \
	else if(TYPE == Failure) {                                                                                                      \
		printf("%sFailed to compile successfully. \n\tReturn Exit status %d\n",COLOR,Failure);                                  \
	 }                                                                                                                              \
	else if(TYPE == Success) {                                                                                                      \
		printf("%sProgram compiled successfully. \n\tReturn Exit status %d\n",COLOR,Success);                                   \
	}                                                                                                                               \
	else {                                                                                                                          \
		printf("%s",COLOR);                                                                                                     \
		printf("Unknown return type\n");                                                                                        \
	}
