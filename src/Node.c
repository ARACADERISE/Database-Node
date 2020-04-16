/*
    * KEY FILE FOR WORKING WITH THE NODES
    * This file is also used to create the Database Node
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
  char NodeName[150], EraType[4], CanRead[4], AllocData[3], CGE[4];
  bool __CGE,CanRead_,AlocData;
  int FileSize, StringSize, IntegerSize;

  printf("Node Name #%d: ",Times);scanf("%s",NodeName);
  printf("-----\nCore Generated Errors(yes/no): ");scanf("%s",CGE);
  printf("-----\nCan Read(yes/no): ");scanf("%s",CanRead);
  printf("-----\nAllocated Data(yes/no): ");scanf("%s",AllocData);
  printf("-----\nEra Type(wro(write/read), wo(write only), ro(read only), da(collect and work with data)): ");scanf("%s",EraType);
  printf("-----\nFile Size(defaults to 10000): ");scanf("%d",&FileSize);
  printf("-----\nString Size(defaults to 20000): ");scanf("%d",&StringSize);
  printf("-----\nInteger Size(defaults to 20000): ");scanf("%d",&IntegerSize);

  if(strcmp(CGE,"yes")==0)__CGE=true;
  else __CGE=false;
  if(strcmp(CanRead,"yes")==0)CanRead_=true;
  else CanRead_=false;
  if(strcmp(AllocData,"yes")==0)AlocData=true;
  else if(strcmp(AllocData, "no")) AlocData=false;
  else AlocData=false;

  SetupDatabaseNode(NodeName, __CGE, CanRead_, AlocData, EraType,FileSize,StringSize,IntegerSize);
  printf("\n");
}
