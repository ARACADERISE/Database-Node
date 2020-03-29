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
		for(int i = 0; i < SizeToIterate; i++) {
			if(SizeToIterate-1==i)
				break;
			if(Db->CoreInfo.AllocatedStorage.AllocatedTotal[i]!=0 &&
				Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[i]!=0 &&
				Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[i]!=0 &&
				Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[i]!=0
			) {
				Db->CoreInfo.AllocatedStorage.AllocatedTotal[i]=0;
				Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[i]=0;
				Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[i]=0;
				Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[i]=0;
				break;
			} else {
				ErrStatus = (_CGE == 0) ? ResetingStorageOfSizeZero : Failure;
				if(Print_ == 0) {
					RETURNERRINFO("\033[0;36m", ErrStatus);
				}
				Print_=1;
				break;
			}
		}
	}

	// Freeing up regular storage
	for(int i = 0; i < SizeToIterate; i++) {
		if(SizeToIterate-1==i)
			break;
		
		if(
			Db->CoreInfo.StorageUsed.Total[i]!=0 &&
			Db->CoreInfo.StorageUsed.TotalFileStorageUsed[i]!=0 &&
			Db->CoreInfo.StorageUsed.TotalStringStorageUsed[i]!=0 &&
			Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[i]!=0
		) {
			Db->CoreInfo.StorageUsed.Total[i]=0;
			Db->CoreInfo.StorageUsed.TotalFileStorageUsed[i]=0;
			Db->CoreInfo.StorageUsed.TotalStringStorageUsed[i]=0;
			Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[i]=0;
		}
	}

	return 0;
}

DatabaseNodeset *
AllocateData(DatabaseNodeset *Db, int SizeToIterate, const char *NodeName) {
	static int Print_ = 0; // Zero by default meaning the error prints once
	char Info[450][100];
	static int UseIndex = 0;
	for(int i = 0; i < SizeToIterate+1; i++) {
		if(SizeToIterate-1==i)
			break;
		if(
			Db->CoreInfo.StorageUsed.Total[i]==0 ||
			Db->CoreInfo.StorageUsed.TotalFileStorageUsed[i]==0 ||
			Db->CoreInfo.StorageUsed.TotalStringStorageUsed[i]==0 ||
			Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[i]==0
			) {
			ErrStatus = (_CGE == 0) ? AllocatingStorageWithSizeZero : Failure;
			if(Print_ < 1) {
				RETURNERRINFO("\033[1;36m", ErrStatus);
			}
			Print_=1;
			//break;
		} else {
			if(Db->CoreInfo.AllocatedStorage.AllocatedTotal[i+1]==0) {

				//UseIndex = i+1;
				Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[i]=Db->CoreInfo.StorageUsed.TotalFileStorageUsed[i];
				Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[i]=Db->CoreInfo.StorageUsed.TotalStringStorageUsed[i];
				Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[i]=Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[i];
				Db->CoreInfo.AllocatedStorage.AllocatedTotal[i]=Db->CoreInfo.StorageUsed.Total[i];
				//printf("%d\n",Db->CoreInfo.AllocatedStorage.AllocatedTotal[i]);
			}
		}
	}

	return Db;
}

DatabaseNodeset *
UpdateStorage(DatabaseNodeset *Db,int *ToChange,int changeBy, int Maxed, int SizeToIterate){
	int AmmountLeft;

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
				for(int i = 0; i < SizeToIterate+1; i++) {
					if(SizeToIterate-1==i)
						break;
					
					All = Db->CoreInfo.NodeStorage.MaxFileSize[i] + Db->CoreInfo.NodeStorage.MaxStringSize[i] + Db->CoreInfo.NodeStorage.MaxIntegerSize[i];
					if(All > Db->CoreInfo.NodeStorage.MaxStorageAllowed) {
						ErrStatus = (_CGE == 0) ? StorageAboveMax : Failure;
						RETURNERRINFO("\033[1;33m", ErrStatus);

						Db->CoreInfo.NodeStorage.MaxFileSize[i] = 40000000/3;
						Db->CoreInfo.NodeStorage.MaxStringSize[i] = 40000000/3;
						Db->CoreInfo.NodeStorage.MaxIntegerSize[i]=40000000/3;

						system("clear"); // We don't want to keep all that information printed
					}
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

	return 0;
}

// A very simple function
DatabaseNodeset *
SetupNodeStorage(
	DatabaseNodeset *DbNode,
	NodeSizes *Sizes,
	char DbNames[1000][100],
	int SizeToIterate
) {

	char Update[2000][150];
	char Info[2000][150];

	// Storage is factored into the Sizes struct in types.h, just not set to the Datbase Node
	for(int i = 0; i < SizeToIterate+1; i++) {
		if(SizeToIterate-1==i)
			break;

		DbNode->CoreInfo.NodeStorage.MaxFileSize[i] = Sizes->MaxFileSize;
		DbNode->CoreInfo.NodeStorage.MaxStringSize[i] = Sizes->MaxStringSize;
		DbNode->CoreInfo.NodeStorage.MaxIntegerSize[i] = Sizes->MaxIntegerSize;
	}
	DbNode->CoreInfo.NodeStorage.MaxStorageUpgrade=50000;
	for(int i = 0; i < SizeToIterate+1; i++) {
		if(SizeToIterate-1==i)
			break;

		/* 
		*	DbNode->CoreInfo.NodeStorage.MaxStorageTotal:
		*	This will be the total ammount of storage of all the Storages combined
		*/
		DbNode->CoreInfo.NodeStorage.MaxStorageTotal[i]=Sizes->MaxStorageTotal;

		// This needs to be done in SetupNodeStorage, sets all of them to zero since no storage is being used as 
		// of thus far
		DbNode->CoreInfo.StorageUsed.TotalFileStorageUsed[i]=0;
		DbNode->CoreInfo.StorageUsed.TotalStringStorageUsed[i]=0;
		DbNode->CoreInfo.StorageUsed.TotalIntegerStorageUsed[i]=0;
	}

	// Signing of the value of 40000000 stored in sizes to CoreInfo.NodeStorage.MaxStorageAllowed
	DbNode->CoreInfo.NodeStorage.MaxStorageAllowed=Sizes->MaxStorageAllowed;

	// Sizes aren't needed anymore
	free(Sizes);

	// Sets ammount of storage the Node can hold for each
	for(int i = 0; i < SizeToIterate; i++) {
		if(!(strcmp(DbNames[i],"DefaultNodeSetup")==0)) {
			sprintf(Update[i],"%s:\n\tFile Storage: %d\n\tString Storage: %d\n\tInteger Storage: %d\n", DbNames[i],DbNode->CoreInfo.NodeStorage.MaxFileSize[i],DbNode->CoreInfo.NodeStorage.MaxStringSize[i],DbNode->CoreInfo.NodeStorage.MaxIntegerSize[i]);
		}
	}
	FILE * WriteData;

	WriteData = fopen("STORAGEINFO","w");
	for(int i = 0; i < SizeToIterate+1; i++) {
		fputs(Update[i],WriteData);
	}
	fclose(WriteData);

	return 0;
}
