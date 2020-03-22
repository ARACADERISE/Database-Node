/* 
	Sets up the core of the users Database Node.

	Basically, it does all of the backend work of setting
	up what the Database Node does, what it can and cannot
	do, and the functionalities going into it
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "CORE_types.h"

char *DatabaseNodeName;
int _CGE;

void SetupDatabaseNode(
	char *DatabaseNode,
	bool CoreGenereatedErrs,
	bool NodeCanRead,
	char *Era
);
