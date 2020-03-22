/* 
	Keep Note:
		The Core Generated Errs/Types are for the err status,
		or the status of which the error occured which is
		represented by a number. The exit will then return
		the number, with printing what the error was.

		_CGE Is nto used majorly in this file, but errors returned in other files are majorly dependent on _CGE
*/

#include <stdio.h>

extern int _CGE;

#  define CoreConErr         2 // Starts at 2 since Failure is 1
#  define FileConErr         3
#  define NotDumped          4
#  define SameNameErr        5
#  define FoundInOtherFile   6
#  define Failure            1
#  define Success            0

#define CTYPES() \
	printf("TYPES: \n%s",(_CGE == 0) ? "\tCoreConErr - Err Status 1\n\tFileConErr - Err Status 2\n\tNotDumped - Err Status 3\n" : "\tFailure - Exit Status 1\n\tSuccess - Exit Status 0");

#define RETURNERR(TYPE) \
	printf("%s",(TYPE == CoreConErr) ? "Yes" : "No")
