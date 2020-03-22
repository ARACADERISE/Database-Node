/* 
	Keep Note:
		The Core Generated Errs/Types are for the err status,
		or the status of which the error occured which is
		represented by a number. The exit will then return
		the number, with printing what the error was
*/

#include <stdio.h>

extern int _CGE;

#if(_CGE == 0)
#  define CoreConErr    1
#  define FileConErr    2
#else
#  define Failure        1
#  define Success        0
#endif

#define CTYPES() \
	printf("TYPES: \n%s",(_CGE == 0) ? "\tCoreConErr - Err Status 1\n\tFileConErr - Err Status 2\n" : "\tFailure - Exit Status 1\n\tSuccess - Exit Status 0");
