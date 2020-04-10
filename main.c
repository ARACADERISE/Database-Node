#include <stdio.h>
#include <stdlib.h>
#include "src/CORE.h"

int main(void) {
	// The program will go off of this
	SetupDatabaseNode("DefaultNodeSetup", true, true, false, "NUN", 0, 0, 0);

	char AddNode[4];
	printf("Add Node?[yes/no]: ");
	scanf("%s",AddNode);
	if(strcmp(AddNode,"yes")==0)SetupNode();

	// Final step of setting up Database Nodes
	system("python Python/dataparser.py");
}
