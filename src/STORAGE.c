/* 
	Source code of all storage of the Database Node
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "CORE_types.h"

extern int _CGE;
extern bool AllocatedData;

int ErrStatus;

DatabaseNodeset *ResetStorage(DatabaseNodeset *Db, int SizeToIterate) {
	static int Print_ = 0; // Meaning it prints once

	// Freeing up allocated data
	if(AllocatedData) {
		for(;SizeToIterate;) {

			if(Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]!=0 &&
				Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[SizeToIterate]!=0 &&
				Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[SizeToIterate]!=0 &&
				Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[SizeToIterate]!=0
			) {
				Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]=0;
				Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[SizeToIterate]=0;
				Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[SizeToIterate]=0;
				Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[SizeToIterate]=0;
			} else {
				ErrStatus = (_CGE == 0) ? ResetingStorageOfSizeZero : Failure;
				if(Print_ == 0) {
					RETURNERRINFO("\033[0;36m", ErrStatus);
				}
				Print_=1;
			}
			break;
		}
	}

	// Freeing up regular storage
	for(;SizeToIterate;) {
		
		if(Db->CoreInfo.StorageUsed.Total[SizeToIterate]!=0 &&
			 Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]!=0 &&
			 Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]!=0 &&
			 Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]!=0
		) {
			Db->CoreInfo.StorageUsed.Total[SizeToIterate]=0;
			Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]=0;
			Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]=0;
			Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]=0;
		}

		break;
	}

	return 0;
}

DatabaseNodeset *
AllocateData(DatabaseNodeset *Db, int SizeToIterate, const char *NodeName) {
	static int Print_ = 0; // Zero by default meaning the error prints once
	//static int UseIndex = 0;

	for(;SizeToIterate;) {
		if(
			Db->CoreInfo.StorageUsed.Total[SizeToIterate]==0 ||
			Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]==0 ||
			Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]==0 ||
			Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]==0
			) {
			ErrStatus = (_CGE == 0) ? AllocatingStorageWithSizeZero : Failure;
			if(Print_ < 1) {
				RETURNERRINFO("\033[1;36m", ErrStatus);
			}
			Print_=1;
			//break;
		} else {
			if(Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]==0) {

				//UseIndex = i+1;
				memcpy(&Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[SizeToIterate],& Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate], sizeof(Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]));
				memcpy(&Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[SizeToIterate],&Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate],sizeof(Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[SizeToIterate]));
				memcpy(&Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[SizeToIterate],&Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate],sizeof(Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[SizeToIterate]));
				memcpy(&Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate],&Db->CoreInfo.StorageUsed.Total[SizeToIterate],sizeof(Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]));
				//printf("%d->%d\n",SizeToIterate,Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]);
			}
		}
		break;
	}

	return Db;
}

// Simple function that writes info about updated storage
static inline int
UpdateStorageFile(char *FileName, const int From, const int To) {
	FILE *UpdStgFile;

	char Info[100];
	sprintf(Info,"%d to %d", From, To);

	UpdStgFile = fopen(FileName,"w");
	fputs(Info,UpdStgFile);
	fclose(UpdStgFile);
	
	return 0;
}

DatabaseNodeset *
UpdateStorage(DatabaseNodeset *Db,int *ToChange,int changeBy, int Maxed, int SizeToIterate){
	int AmmountLeft;
	int from = *ToChange;

	/*
	 * Maxed: Set the Database Nodes storage to a maximum, so if the new storage amount is anywhere near Maxed
	 * (500 below and or above), it rounds it up. If it's above Maxed, it rounds it  down

	 *	NOTE: If Maxed is greater than the Nodes total storage allowed it will throw a error
	*/

	if(Db->CoreInfo.NodeStorage.MaxStorageAllowed!=0) {
		if(Maxed >= Db->CoreInfo.NodeStorage.MaxStorageAllowed) {
			static int Print_ = 0; // Printing error only once
			ErrStatus = (_CGE == 0) ? MaxedAboveTotalStorageAllowed : Failure;
			if(Print_ == 0){
				RETURNERRINFO("\033[0;36m", ErrStatus);
			}
			Print_=1;
			Maxed = 100000;

			//system("clear");
		}
		if(changeBy >= Db->CoreInfo.NodeStorage.MaxStorageAllowed) {
			static int Pr = 0; // Printing error only once
			ErrStatus = (_CGE == 0 ) ? ChangingByAboveStorageAllowed : Failure;
			if(Pr == 0) {
				RETURNERRINFO("\033[0;36m", ErrStatus);
			}
			Pr=1;
			changeBy=Db->CoreInfo.NodeStorage.MaxStorageUpgrade;
		}
		*ToChange += changeBy;

		if(*ToChange != Db->CoreInfo.NodeStorage.MaxStorageAllowed && !(*ToChange>=Db->CoreInfo.NodeStorage.MaxStorageAllowed))
		{
			if(*ToChange > Maxed) {
				int All;
				for(;SizeToIterate;) {
					
					All = Db->CoreInfo.NodeStorage.MaxFileSize[SizeToIterate] + Db->CoreInfo.NodeStorage.MaxStringSize[SizeToIterate] + Db->CoreInfo.NodeStorage.MaxIntegerSize[SizeToIterate];
					if(All > Db->CoreInfo.NodeStorage.MaxStorageAllowed) {
						ErrStatus = (_CGE == 0) ? StorageAboveMax : Failure;
						RETURNERRINFO("\033[1;33m", ErrStatus);

						Db->CoreInfo.NodeStorage.MaxFileSize[SizeToIterate] = 40000000/3;
						Db->CoreInfo.NodeStorage.MaxStringSize[SizeToIterate] = 40000000/3;
						Db->CoreInfo.NodeStorage.MaxIntegerSize[SizeToIterate]=40000000/3;

						system("clear"); // We don't want to keep all that information printed
					}
					break;
				}
				
				int Sub = Maxed-*ToChange;
				*ToChange = *ToChange + Sub;
			}
			else {
				int AmLeft;
				if(Maxed-*ToChange <= 500) {
					AmLeft = Maxed-*ToChange;
					*ToChange += AmLeft;
				}
			}
		} else {
			if(*ToChange >= Db->CoreInfo.NodeStorage.MaxStorageAllowed) {
				*ToChange = 40000000/3;
			}
		}
	} else {
		ErrStatus = (_CGE == 0) ? MaxAllowedStorageIsZero : Failure;
		RETURNERRINFO("\033[0;31m", ErrStatus);
		exit(ErrStatus);
	}

	char Filename[100];
	sprintf(Filename, "UPDATESTORAGE-%d",SizeToIterate);
	
	UpdateStorageFile(Filename,from, *ToChange);

	return 0;
}

// A very simple function
DatabaseNodeset *
SetupNodeStorage(
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes,
	char DbNames[1000][100],
	char *RecentNodeName,
	int SizeToIterate
) {

	char Update[2000][150];
	char Info[2000][150];

	// Storage is factored into the Sizes struct in types.h, just not set to the Datbase Node
	if(!(strcmp(RecentNodeName,"DefaultNodeSetup")==0)) {
		for(;SizeToIterate;) {
			DbNode->CoreInfo.NodeStorage.MaxFileSize[SizeToIterate] = Sizes->MaxFileSize;
			DbNode->CoreInfo.NodeStorage.MaxStringSize[SizeToIterate] = Sizes->MaxStringSize;
			DbNode->CoreInfo.NodeStorage.MaxIntegerSize[SizeToIterate] = Sizes->MaxIntegerSize;
			break;
		}
		DbNode->CoreInfo.NodeStorage.MaxStorageUpgrade=50000;
		for(;SizeToIterate;) {

			/* 
			*	DbNode->CoreInfo.NodeStorage.MaxStorageTotal:
			*	This will be the total ammount of storage of all the Storages combined
			*/
			DbNode->CoreInfo.NodeStorage.MaxStorageTotal[SizeToIterate]=Sizes->MaxStorageTotal;

			// This needs to be done in SetupNodeStorage, sets all of them to zero since no storage is being used as 
			// of thus far
			DbNode->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]=0;
			DbNode->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]=0;
			DbNode->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]=0;

			break;
		}

		// Signing of the value of 40000000 stored in sizes to CoreInfo.NodeStorage.MaxStorageAllowed
		DbNode->CoreInfo.NodeStorage.MaxStorageAllowed=Sizes->MaxStorageAllowed;

		// Sizes aren't needed anymore
		free(Sizes);

		// Sets ammount of storage the Node can hold for each
		for(;SizeToIterate;) {
			if(!(strcmp(RecentNodeName,"DefaultNodeSetup")==0)) {
				sprintf(Update[SizeToIterate],"%s:\n\tFile Storage: %d\n\tString Storage: %d\n\tInteger Storage: %d\n", DbNames[SizeToIterate],DbNode->CoreInfo.NodeStorage.MaxFileSize[SizeToIterate],DbNode->CoreInfo.NodeStorage.MaxStringSize[SizeToIterate],DbNode->CoreInfo.NodeStorage.MaxIntegerSize[SizeToIterate]);
				break;
			}
		}
		
		FILE * WriteData;
		
		char FileName[1000][50];
		if(!(strcmp(RecentNodeName,"DefaultNodeSetup")==0))
			sprintf(FileName[SizeToIterate],"STORAGE-%s",RecentNodeName);
		
		WriteData = fopen(FileName[SizeToIterate],"w");
		for(;SizeToIterate;) {
			if(!(strcmp(RecentNodeName,"DefaultNodeSetup")==0))
				fputs(Update[SizeToIterate],WriteData);
			break;
		}
		fclose(WriteData);
	}

	return 0;
}
