/* 
	Source code of all storage of the Database Node.

	This is all hard coded storage, yes, it still has bytes due to being size_t and type of int, but it cannot
	be anywhere above 40 million
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "CORE_types.h"

extern int _CGE;
extern bool AllocatedData;
extern char *DatabaseNodeName;

int ErrStatus;

DatabaseNodeset *ResetStorage(DatabaseNodeset *Db, int SizeToIterate) {
	static int Print_ = 0; // Meaning it prints once

	// Freeing up allocated data
	if(AllocatedData) {

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
		}

	// Freeing up regular storage
		
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

	return 0;
}

DatabaseNodeset *
AllocateData(DatabaseNodeset *Db, int SizeToIterate /*const char *NodeName*/) {
	//static int Print_ = 0; // Zero by default meaning the error prints once
	//static int Amm = 0; // Zero by default
	//static int UseIndex = 0;

	/* may need it for later on if we run into an error allocating from default node

  	if(SizeToIterate == 2 && AllocatedData) {
		ErrStatus = (_CGE == 0) ? CannotAllocateFromDefaultDbNode : Failure;
		RETURNERRINFO("\033[0;31m", ErrStatus);
		exit(ErrStatus);
	}
	*/

	if(AllocatedData && (
		Db->CoreInfo.StorageUsed.Total[SizeToIterate]!=0 &&
		Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]!=0 &&
		Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]!=0 &&
		Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]!=0
	)) {
		Db->CoreInfo.StorageUsed.Total[SizeToIterate]-=1;
		Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]-=1;
		Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]-=1;
		Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]-=1;

		if(Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]==0) {

			//UseIndex = i+1;
			memcpy(&Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[SizeToIterate], &Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate], sizeof(Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]));
			memcpy(&Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[SizeToIterate],&Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate],sizeof(Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[SizeToIterate]));
			memcpy(&Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[SizeToIterate],&Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate],sizeof(Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[SizeToIterate]));
			memcpy(&Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate],&Db->CoreInfo.StorageUsed.Total[SizeToIterate],sizeof(Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]));
			//printf("%d->%ld\n",SizeToIterate,Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]);
		}

		//Amm+=1;
	} else {
		goto ERROR;
	}

	/* This will stop the application from allocating size of zero */
	ERROR:
  if(
    AllocatedData &&
    (Db->CoreInfo.StorageUsed.Total[SizeToIterate]==0 ||
    Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]==0 ||
    Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]==0 ||
    Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]==0)
  ) {
    ErrStatus = (_CGE == 0) ? AllocatingStorageWithSizeZero : Failure;
    RETURNERRINFO("\033[3;31m", ErrStatus);

    // RESETING ALL SIZES
    Db->CoreInfo.StorageUsed.Total[SizeToIterate]=0;
    Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]=0;
    Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]=0;
    Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]=0;
    AllocatedData=false;
  }

	return Db;
}

// Simple function that writes info about updated storage
static inline void
UpdateStorageFile(char *FileName, const size_t From, char *StorageType, const size_t To) {
	FILE *UpdStgFile;

	char Info[100];
	sprintf(Info,"%ld to %ld", From, To);

	UpdStgFile = fopen(FileName,"w");
	fputs(Info,UpdStgFile);
	fputs(StorageType,UpdStgFile);
	fclose(UpdStgFile);
}

DatabaseNodeset *
UpdateStorage(DatabaseNodeset *Db,size_t *ToChange,size_t changeBy, size_t Maxed, int SizeToIterate, char *StorageType){
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
					
				All = Db->CoreInfo.NodeStorage.MaxFileSize[SizeToIterate] + Db->CoreInfo.NodeStorage.MaxStringSize[SizeToIterate] + Db->CoreInfo.NodeStorage.MaxIntegerSize[SizeToIterate];
				if(All > Db->CoreInfo.NodeStorage.MaxStorageAllowed) {
					ErrStatus = (_CGE == 0) ? StorageAboveMax : Failure;
					RETURNERRINFO("\033[1;33m", ErrStatus);

					Db->CoreInfo.NodeStorage.MaxFileSize[SizeToIterate] = 40000000/3;
					Db->CoreInfo.NodeStorage.MaxStringSize[SizeToIterate] = 40000000/3;
					Db->CoreInfo.NodeStorage.MaxIntegerSize[SizeToIterate]=40000000/3;

					system("clear"); // We don't want to keep all that information printed
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
	sprintf(Filename, "UPDATESTORAGE-%s",DatabaseNodeName);
	UpdateStorageFile(Filename,from, StorageType,*ToChange);

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

	char Update[2000];
	char Info[2000][150];

	// Storage is factored into the Sizes struct in types.h, just not set to the Datbase Node
	DbNode->CoreInfo.NodeStorage.MaxFileSize[SizeToIterate] = Sizes->MaxFileSize;
	DbNode->CoreInfo.NodeStorage.MaxStringSize[SizeToIterate] = Sizes->MaxStringSize;
	DbNode->CoreInfo.NodeStorage.MaxIntegerSize[SizeToIterate] = Sizes->MaxIntegerSize;

	DbNode->CoreInfo.NodeStorage.MaxStorageUpgrade=50000;

	/* 
		*	DbNode->CoreInfo.NodeStorage.MaxStorageTotal:
		*	This will be the total ammount of storage of all the Storages combined
	*/
	DbNode->CoreInfo.NodeStorage.MaxStorageTotal[SizeToIterate]=Sizes->MaxStorageTotal;

	/* 
		There cannot be any allocating data going on before SetupNodeStorage is used.

    This section is commented out due to the fact this error should be taken cared of
    in CORE.c, but just in case for later references, we'll keep it commented out
	
	if(AllocatedData) {
		if(DbNode->CoreInfo.AllocatedStorage.AllocatedTotal[3]!=0) {
			ErrStatus = (_CGE == 0) ? CannotHaveAllocatedStorageYet : Failure;
			fprintf(stderr,"\033[1;31mCannot have allocated data when there is no storage saved.\033[0;0m\033[3;31m\n\tEXIT_STATUS_%d\n",ErrStatus);
			exit(ErrStatus);
		}
	}
  */

	// This needs to be done in SetupNodeStorage, sets all of them to zero since no storage is being used as 
	// of thus far
	DbNode->CoreInfo.StorageUsed.Total[SizeToIterate]=0;
	DbNode->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate]=0;
	DbNode->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate]=0;
	DbNode->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]=0;

	// Signing of the value of 40000000 stored in sizes to CoreInfo.NodeStorage.MaxStorageAllowed
	DbNode->CoreInfo.NodeStorage.MaxStorageAllowed=Sizes->MaxStorageAllowed;

	// Sizes aren't needed anymore
	free(Sizes);

	// Sets ammount of storage the Node can hold for each
	if(!(strcmp(RecentNodeName,"DefaultNodeSetup")==0)) {
		sprintf(Update,"%s:\n\tFile Storage: %ld\n\tString Storage: %ld\n\tInteger Storage: %ld\n", RecentNodeName,DbNode->CoreInfo.NodeStorage.MaxFileSize[SizeToIterate],DbNode->CoreInfo.NodeStorage.MaxStringSize[SizeToIterate],DbNode->CoreInfo.NodeStorage.MaxIntegerSize[SizeToIterate]);
	}

	FILE *Write;

	char FileName[1000];
	sprintf(FileName,"STORAGE-%s",RecentNodeName);

	Write = fopen(FileName,"w");
	fputs(Update,Write);
	fclose(Write);

	return 0;
}

// Prints storage ammounts
void CheckStorage(DatabaseNodeset *Db, int SizeToIterate, char *NodeName) {

  /*
      Beta version of printing storage ammounts,
      keeping commented out printf statements just in case I want to use them later on instead of the
      printf statement I have right now.
  */

	if(AllocatedData && Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate]==0) {
		fprintf(stderr, "\n\n\t\033[0;34mChecked allocated storage of %s,\n\tNo storage has been allocated\033[0;0m\n\n",NodeName);
	} else if(!(AllocatedData) && Db->CoreInfo.StorageUsed.Total[SizeToIterate]==0) {
		fprintf(stderr, "\n\n\033[0;34m\tChecked storage of %s,\n\tNo storage has been used yet\n\033[0;0m\n\n",NodeName);
	} else {
		if(AllocatedData) {
			//printf("====ALLOCATED_STORAGE->%s====\n",NodeName);
			//printf("\tTOTAL-%ld\n\tFILE-%ld\n\tSTRING-%ld\n\tINTEGER-%ld\n",Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate],Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[SizeToIterate],Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[SizeToIterate],Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[SizeToIterate]);
      			//printf("====END====\n\n");

      			printf("NODE_NAME: %s | TYPE: ALLOCATED | TOTAL: %ld | FILE: %ld | STRING: %ld | INTEGER: %ld",NodeName,Db->CoreInfo.AllocatedStorage.AllocatedTotal[SizeToIterate],Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[SizeToIterate],Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[SizeToIterate],Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[SizeToIterate]);
		} else {
      			//printf("====STORAGE->%s====\n",NodeName);
			//printf("\tTOTAL-%ld\n\tFILE-%ld\n\tSTRING-%ld\n\tINTEGER-%ld\n",Db->CoreInfo.StorageUsed.Total[SizeToIterate],Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate],Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate],Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]);
			//printf("====END====\n\n");

      			printf("NODE_NAME: %s | TYPE: Regular | TOTAL: %ld | FILE: %ld | STRING: %ld | INTEGER: %ld",NodeName,Db->CoreInfo.StorageUsed.Total[SizeToIterate],Db->CoreInfo.StorageUsed.TotalFileStorageUsed[SizeToIterate],Db->CoreInfo.StorageUsed.TotalStringStorageUsed[SizeToIterate],Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[SizeToIterate]);
		}
	}
}
