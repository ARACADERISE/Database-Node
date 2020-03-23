/* 
	Keep Note:
		The Core Generated Errs/Types are for the err status,
		or the status of which the error occured which is
		represented by a number. The exit will then return
		the number, with printing what the error was.

		_CGE Is not used majorly in this file, but errors returned in other files are majorly dependent on _CGE
*/

#include <stdio.h>
#include <stdlib.h>

extern int _CGE;

#  define CoreConErr            2 // Starts at 2 since Failure is 1
#  define FileConErr            3
#  define NotDumped             4
#  define FoundInOtherFile      5
#  define DeclarationOfEraNun   6
#  define Failure               1
#  define Success               0

#define CTYPES() \
	printf("TYPES: \n%s",(_CGE == 0) ? "\tCoreConErr - Err Status 2\n\tFileConErr - Err Status 3\n\tNotDumped - Err Status 4\n\tFoundInOtherFile - Err Status 5" : "\tFailure - Exit Status 1\n\tSuccess - Exit Status 0");

#define RETURNERRINFO(TYPE) \
	if(TYPE == CoreConErr) \
		printf("Error connection with core. \n\tReturn Exit status %d",CoreConErr); \
	else if(TYPE == FileConErr) \
		printf("Error connecting/finding file. \n\tReturn Exit status %d",FileConErr); \
	else if(TYPE == FoundInOtherFile) \
		printf("The string/number/character was found in another file. \n\tReturn Exit status %d",FoundInOtherFile); \
	else if(TYPE == Failure) \
		printf("Failed to compile successfully. \n\tReturn Exit status %d",Failure); \
	else if(TYPE == Success) \
		printf("Program compiled successfully. \n\tReturn Exit status %d",Success); \
	else { \
		printf("Unknown return type"); \
	}
