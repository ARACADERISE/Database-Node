/* 
    Keep Note:
        The Core Generated Errs/Types are for the err status,
        or the status of which the error occured which is
        represented by a number. The exit will then return
        the number, with printing what the error was.

        _CGE Is not majorly depended on in this file, but errors returned in other files are 
        majorly dependent on _CGE
*/

#include <stdio.h>
#include <stdlib.h>

// Update types
#define INTEGER_STORAGE     "INTEGER STORAGE"
#define FILE_STORAGE        "FILE STORAGE"
#define STRING_STORAGE      "STRING STORAGE"

// Initital file buffer size
#define InitFileBufferSize         250
// Update file buffer size
#define UpdateFileBufferSize       1200

/* 
    * Needed for default values of the Node struct,
    * long very basic function but is needed!
*/
#define SETDEFAULT(Db) \
    memset(Db->CoreInfo.NodeName,'_',sizeof(&Db->CoreInfo.NodeName)); memset(Db->NodeId,0,sizeof(&Db->NodeId)); \
    memset(Db->CoreInfo.NodeStorage.MaxStorageTotal, 0, sizeof(&Db->CoreInfo.NodeStorage.MaxStorageTotal)); \
    memset(Db->CoreInfo.NodeStorage.MaxFileSize,0,sizeof(&Db->CoreInfo.NodeStorage.MaxFileSize)); memset(Db->CoreInfo.NodeStorage.MaxStringSize,0,sizeof(&Db->CoreInfo.NodeStorage.MaxStringSize)); \
    memset(Db->CoreInfo.NodeStorage.MaxIntegerSize,0,sizeof(&Db->CoreInfo.NodeStorage.MaxIntegerSize)); memset(Db->CoreInfo.StorageUsed.Total,0,sizeof(&Db->CoreInfo.StorageUsed.Total)); \
    memset(Db->CoreInfo.StorageUsed.TotalFileStorageUsed,0,sizeof(&Db->CoreInfo.StorageUsed.TotalFileStorageUsed)); memset(Db->CoreInfo.StorageUsed.TotalStringStorageUsed,0,sizeof(&Db->CoreInfo.StorageUsed.TotalStringStorageUsed)); \
    memset(Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed,0,sizeof(&Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed))


/* 
    * Needed for adding space if 1000 is reached 
    * No matter what index anything else is at, if Node names
    * is at a thousand it will switch over to ExtraDatabaseNodeSet.
    * Yet another simple, very simple, function, yet again...very much needed
    * If CopyOld is true then there will be 1000 added to the each index of ExtraDatabaseNodeSet.
    * There is allot of "waste code" as I like to call it.
      - "waste code" meaning..code that could be refactored, but I just didn't refactor it

    EVERYTHING IN DatabaseNodeSet WILL BE SAVED!
*/
#define BuffAmmount(Db,ExtraNode,CopyOld) \
    for(int i = 0; i < 1000/*Only a thousand indexes*/; i++) {\
        if(i==999&&!(strcmp(Db->CoreInfo.NodeName[i],"_")==0)) {\
          /* 
          Setting value of ExtraNodeSetNeeded to true,
          then setting values of ExtraDatabaseNodeSet to a default value of 0 and _ 
          */\
          Db->ExtraNodeSetNeeded=true;\
          if(CopyOld) {\
            /*Reseting all to 2000*/\
            /* Node name/Node id */\
            ExtraNode->ExtraDb->CoreInfo.NodeName = (char *) realloc(2000,sizeof(char)*50);\
            ExtraNode->ExtraDb->NodeId = realloc(2000,sizeof(int));\
            /* Node Storage */\
            ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxStorageTotal = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.MaxStringSize = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxFileSize = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxIntegerSize = realloc(2000,sizeof(size_t));\
            /* Allocated Data */\
            ExtraNode->ExtraDb->CoreInfo.AllocatedStorage.AllocatedTotal = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.AllocatedStorage.AllocatedMaxFileSize = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.AllocatedStorage.AllocatedMaxStringSize = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize = realloc(2000,sizeof(size_t));\
            /* Storage Used */\
            ExtraNode->ExtraDb->CoreInfo.StorageUsed.Total = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalFileStorageUsed = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalStringStorageUsed = realloc(2000,sizeof(size_t));\
            ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalIntegerStorageUsed = realloc(2000,sizeof(size_t));\
            /* Copying */\
            for(int i = 0; i < 1000/*using 1000 out of 2000 indexes to copy*/; i++) {\
              /* Node name/Node id */\
              memcpy(ExtraNode->ExtraDb->NodeId[i],Db->CoreInfo.NodeId[i]);memcpy(ExtraNode->ExtraDb->CoreInfo->NodeName[i],Db->CoreInfo.NodeName[i]);\
              /* Node Storage */\
              memcpy(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxStorageTotal[i],Db->CoreInfo.NodeStorage.MaxStorageTotal[i]);memcpy(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxFileSize[i],Db->CoreInfo.NodeStorage.MaxFileSize[i]);\
              memcpy(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxStringSize[i],Db->CoreInfo.NodeStorage.MaxStringSize[i]);memcpy(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxIntegerSize[i],Db->CoreInfo.NodeStorage.MaxIntegerSize[i]);\
              /* Allocated Storage */\
              memcpy(ExtraNode->ExtraDb->CoreInfo.AllocatedStorage.AllocatedTotal[i],Db->CoreInfo.AllocatedStorage.AllocatedTotal[i]);memcpy(ExtraNode->ExtraDb->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[i],Db->CoreInfo.AllocatedStorage.AllocatedMaxFileSize[i]);\
              memcpy(ExtraNode->ExtraDb->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[i],Db->CoreInfo.AllocatedStorage.AllocatedMaxStringSize[i]);memcpy(ExtraNode->ExtraDb->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[i],Db->CoreInfo.AllocatedStorage.AllocatedMaxIntegerSize[i]);\
              /* Storage Used */\
              memcpy(ExtraNode->ExtraDb->CoreInfo.StorageUsed.Total[i],Db->CoreInfo.StorageUsed.Total[i]);memcpy(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalFileStorageUsed[i],Db->CoreInfo.StorageUsed.TotalFileStorageUsed[i]);\
              memcpy(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalStringStorageUsed[i],Db->CoreInfo.StorageUsed.TotalStringStorageUsed[i]);memcpy(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalIntegerStorageUsed[i],Db->CoreInfo.StorageUsed.TotalIntegerStorageUsed[i]);\
              }\
          }\
          /* Setting up extra Node Information */\
          memset(ExtraNode->ExtraDb->NodeId,0,sizeof(ExtraNode->ExtraDb->NodeId));memset(ExtraNode->ExtraDb->CoreInfo.NodeName,'_',sizeof(ExtraNode->ExtraDb->CoreInfo.NodeName));\
          memset(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxStorageTotal,0,sizeof(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxStorageTotal));memset(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxFileSize,0,sizeof(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxFileSize));\
          memset(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxStringSize,0,sizeof(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxStringSize));memset(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxIntegerSize,0,sizeof(ExtraNode->ExtraDb->CoreInfo.NodeStorage.MaxIntegerSize));\
          memset(ExtraNode->ExtraDb->CoreInfo.StorageUsed.Total,0,sizeof(ExtraNode->ExtraDb->CoreInfo.StorageUsed.Total));memset(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalFileStorageUsed,0,sizeof(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalFileStorageUsed));\
          memset(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalStringStorageUsed,0,sizeof(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalStringStorageUsed));memset(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalIntegerStorageUsed,0,sizeof(ExtraNode->ExtraDb->CoreInfo.StorageUsed.TotalIntegerStorageUsed));\
        }\
      }\
    }


//extern int _CGE;

// Default Errors
#  define CoreConErr                        2 // Starts at 2 since Failure is 1
#  define FileConErr                        3
#  define NotDumped                         4
#  define FoundInOtherFile                  5
// ERA errors
#  define DeclarationOfEraNun               6
#  define DefaultNodeSetupEraTypeNotNun     7
#  define NotAEraType                       8
// Default Database Node errors
#  define DefaultNodeSetupNotFound          9
#  define DefaultDbNodeNotFullySetup        10
#  define MoreThanOneDefaultNodeCreated     11
// User created Database Node errors
#  define DatabaseNodeAlreadyCreated        12
// Storage Errors
#  define StorageAboveMax                   13
#  define StorageAddOverload                14
#  define AllocatingStorageWithSizeZero     15
#  define ResetingStorageOfSizeZero         16
#  define MaxAllowedStorageIsZero           17
#  define CannotHaveAllocatedStorageYet     18
#  define CannotAllocateFromDefaultDbNode   19
// STORAGE.c argument error
#  define MaxedAboveTotalStorageAllowed     20
#  define ChangingByAboveStorageAllowed     21
// Regular success/fail errors
#  define Failure                           1
#  define Success                           0

#define RETURNERRINFO(COLOR,TYPE)                                                                                                                     \
    if(TYPE == CoreConErr) {                                                                                                                      \
        printf("%sError connection with core. \n\t\033[3;31mERR_STATUS_%d\n",COLOR,CoreConErr);                                                 \
    }                                                                                                                                             \
    else if(TYPE == MaxAllowedStorageIsZero) {\
        printf("%sSetupNodeStorage function has not yet been ran.\nInstead UpdateStorage function was ran.\n\t\033[3;31mERR_STATUS_%d\n",COLOR,MaxAllowedStorageIsZero);\
    }\
    else if(TYPE == FileConErr) {                                                                                                                 \
        printf("%sError connecting/finding file. \n\t\033[3;31mERR_STATUS_%d\n",COLOR,FileConErr);                                              \
    }                                                                                                                                             \
    else if(TYPE == FoundInOtherFile) {                                                                                                           \
        printf("%sThe string/number/character was found in another file. \n\t\033[3;31mERR_STATUS_%d\n",COLOR,FoundInOtherFile);                \
    }                                                                                                                                             \
    else if(TYPE == ChangingByAboveStorageAllowed) { \
        printf("%sYou cannot change the value by a size greater than 40000000.\n\t_WARNING_STATUS_%d\n\033[0;m",COLOR,ChangingByAboveStorageAllowed); \
    } \
    else if(TYPE == MaxedAboveTotalStorageAllowed) { \
        printf("%sArgument Maxed cannot be set to any value above 40000000.\n\t_WARNING_STATUS_%d\n\033[0;m",COLOR,MaxedAboveTotalStorageAllowed);\
    }\
    else if(TYPE == DeclarationOfEraNun) {                                                                                                        \
        printf("%sAttempt to set a Era type of NUN to your Database Node. \n\t\033[3;31mERR_STATUS_%d\n",COLOR,DeclarationOfEraNun);                    \
    }                                                                                                                                             \
    else if(TYPE == DefaultNodeSetupNotFound) {                                                                                                   \
        printf("%sThe DefaultNodeSetup Database Node was not found.\n\t\033[3;31mERR_STATUS_%d\n",COLOR,DefaultNodeSetupNotFound);                      \
    }                                                                                                                                             \
    else if(TYPE == DefaultNodeSetupEraTypeNotNun) {                                                                                              \
        printf("%sThe Era type of the Default Database Node is required to be NUN.\n\t\033[3;31mERR_STATUS_%d\n",COLOR,DefaultNodeSetupEraTypeNotNun);  \
    }                                                                                                                                             \
    else if(TYPE == DefaultDbNodeNotFullySetup) {                                                                                                 \
        printf("%sThe Default Database Node is not fully set up yet.\n\t\033[3;31mERR_STATUS_%d\n",COLOR,DefaultDbNodeNotFullySetup);                   \
    }                                                                                                                                             \
    else if(TYPE == MoreThanOneDefaultNodeCreated) {                                                                                              \
        printf("%sAttempted to create more than one Default Database Node.\n\t\033[3;31mERR_STATUS_%d\n",COLOR,MoreThanOneDefaultNodeCreated);          \
    }                                                                                                                                             \
    else if(TYPE == DatabaseNodeAlreadyCreated) {                                                                                                 \
        printf("%sAttempted to create a already existing Database Node.\n\t\033[3;31mERR_STATUS_%d\n",COLOR,DatabaseNodeAlreadyCreated);                \
    }                                                                                                                                             \
    else if(TYPE == NotAEraType) {                                                                                                                \
        printf("%sAttempted to assign an unexisting Era type to the Database node.\n\t\033[3;31mERR_STATUS_%d\n",COLOR,NotAEraType);                    \
    }                                                                                                                                             \
    else if(TYPE == StorageAboveMax) {                                                                                                            \
        printf("%sTotal storage ammount reached for the Database Node.\n\t\033[3;31mERR_STATUS_%d\n\033[0;32mReallocating memory for the Database Nodes storage...\033[0;m",COLOR,StorageAboveMax);                              \
    }                                                                                                                                             \
    else if(TYPE == StorageAddOverload) {                                                                                                         \
        printf("%sAdding too much storage. Total of 50000 storage segments can be added at once.\n\t\033[3;31mERR_STATUS_%d\n",COLOR,StorageAddOverload); \
    }                                                                                                                                             \
    else if(TYPE == AllocatingStorageWithSizeZero) {\
        printf("%sCannot allocate data of zero to your Database Node.\n\t\033[4;36m_WARNING_STATUS_%d\n\033[0;0m\n",COLOR,AllocatingStorageWithSizeZero); \
    } \
    else if(TYPE == Failure) {                                                                                                                    \
        printf("%sFailed to compile successfully. \n\t\033[3;31mERR_STATUS_%d\n",COLOR,Failure);                                                \
     }                                                                                                                                            \
    else if(TYPE == ResetingStorageOfSizeZero) {\
        printf("%sCannot reset a Database Nodes storage of size zero.\n\t\033[4;36m_WARNING_STATUS_%d\033[0;m",COLOR,ResetingStorageOfSizeZero); \
    } \
    else if(TYPE == Success) {                                                                                                                    \
        printf("%sProgram compiled successfully. \n\t033[3;31mERR_STATUS%d\n",COLOR,Success);                                                 \
    }                                                                                                                                             \
    else if(TYPE == CannotAllocateFromDefaultDbNode) {\
        printf("%sCannot allocate storage from DefaultNodeSetup.\nThere is no storage stored for this node.\n\t\033[3;31mERR_STATUS%d\n",COLOR,TYPE);\
    }\
    else {                                                                                                                                        \
        printf("%s",COLOR);                                                                                                                   \
        printf("\033[3;31mUnknown return type\n");                                                                                                      \
    }
