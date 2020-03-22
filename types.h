/* 
	structs and other data structures needed for
	the project
*/

#include <stdio.h>

typedef struct {
	int ResetId;
	char *DatabaseNode;
} Reset;

typedef struct {
	int NodeId;
	struct {
		bool Core_Generated_Errs;
		bool CanRead;
		char *EraType;
		char *NodeName;
	} CoreInfo;
} DatabaseNodeset;
