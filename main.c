#include <stdio.h>
#include <stdlib.h>
#include "src/CORE.h"
#include "src/Node.h" // Source for setting up the Node

int main(void) {
    // The program will go off of this
    SetupDatabaseNode("DefaultNodeSetup", true, true, false, "NUN", 0, 0, 0);

    int Times;
    printf("How many nodes to add? ");
    scanf("%d",&Times);
    
    if(!(Times==0))for(int i = 0; i < Times; i++)SetupNode();

    // Final step of setting up Database Nodes
    system("python Python/dataparser.py");
}
