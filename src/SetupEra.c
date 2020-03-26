/* 
	Sets up what the ERA type does. Backend to ERAS
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

// Writes data stored in struct EraSetup
static void
WriteFile(char *FileName,EraSetup *Era_Setup) {
	FILE *Data;

	Data = fopen(FileName,"w");
	fputs(Era_Setup->Era,Data);
	fputs("\n",Data);
	fputs(Era_Setup->Action,Data);
	fclose(Data);
}

char *Action;
// Gathers the Era name using the DefaultMainDbNode struct
void *
GatherEra(char *Era, DefaultMainDbNode * Db/*Used to go through all ERAS setup through the Default Node*/,DatabaseNodeset *DbNode) {
	
	EraSetup * Era_Setup = (EraSetup *) malloc(sizeof(EraSetup));
	static int InitUpd = 1;
	char fileName[50];

	// Setting up filename
	sprintf(fileName,"Era Setup #%d",InitUpd);

	Era_Setup->Era = Era;

	int index = 0; // 0 by default
	for(int i = 0; i < 4; i++) {
		if(strcmp(Era,Db->ERAS[i]) == 0)
			index = i;
	}
	// The most boring step of the whole application
	switch(index) {
		case 0:
			Action = "Writing and Reading files";
			break;
		case 1:
			Action = "Reading files";
			break;
		case 2:
			Action = "Writing files";
			break;
		case 3:
			Action = "Working with data";
			break;
		/*Default would be here, but would be useless
			since the error of the Era not being in Db->ERAS
			is caught in CORE.c*/
	}
	
	Era_Setup->Action = Action;

	DbNode->CoreInfo.NodeEra.EraType = Era_Setup->Era;
	DbNode->CoreInfo.NodeEra.EraAction = Era_Setup->Action;

	WriteFile(fileName,Era_Setup);

	return 0;
}
