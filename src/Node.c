/*
    * KEY FILE FOR WORKING WITH THE NODES
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "CORE.h"

static int Times;

void
SetupNode() {

  Times++; // Increments at beggining due to the fact this is keeping track how many time the function is called
  // Ideals for the file
  char NodeName[150], EraType[4], CGE[3], CanRead[3], AllocData[3];
  bool __CGE,CanRead_,AlocData;
  int FileSize, StringSize, IntegerSize;

  printf("Node Name #%d: ",Times);scanf("%s",NodeName);
  printf("Core Generated Errors(yes/no): ");scanf("%s",CGE);
  printf("Can Read(yes/no): ");scanf("%s",CanRead);
  printf("Allocated Data(yes/no): ");scanf("%s",AllocData);
  printf("Era Type(wro(write/read), wo(write only), ro(read only), da(collect and work with data)): ");scanf("%s",EraType);
  printf("File Size(defaults to 10000): ");scanf("%d",&FileSize);
  printf("String Size(defaults to 20000): ");scanf("%d",&StringSize);
  printf("Integer Size(defaults to 20000): ");scanf("%d",&IntegerSize);

  if(strcmp(CGE,"yes")==0)__CGE=true;
  if(strcmp(CanRead,"yes")==0)CanRead_=true;
  if(strcmp(AllocData,"yes")==0)AlocData=true;

  SetupDatabaseNode(NodeName, __CGE, CanRead_, AlocData, EraType,FileSize,StringSize,IntegerSize);
  printf("\n");
}
