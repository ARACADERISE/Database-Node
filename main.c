#include <stdio.h>
#include <stdlib.h>
#include "CORE.h"

int main(void) {
	// The program will go off of this
	SetupDatabaseNode("DefaultNodeSetup", true, true, "NUN");

	// Final step of setting up Database Nodes
	system("python Python/dataparser.py");
}
