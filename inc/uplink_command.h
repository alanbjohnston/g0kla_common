/*
 * uplink_command.h
 *
 *  Created on: Nov 27, 2023
 *      Author: g0kla
 */

#ifndef UPLINK_COMMAND_H_
#define UPLINK_COMMAND_H_

#include <stdint.h>

#define AUTH_VECTOR_SIZE 32
#define SW_COMMAND_SIZE 18
#define OUR_ADDRESS 0x1 // Initial test address - redundant as we have a callsign??

#define EXIT_DUPLICATE 2

/*
 * Following is the data structure representing software uplink commands
 */
typedef struct  __attribute__((__packed__)) {
	uint16_t command;
	uint16_t arguments[4];
} CommandAndArgs;

typedef struct  __attribute__((__packed__)){
	uint32_t dateTime;
	uint8_t reserved;
	uint8_t address;
	uint8_t special;
	uint8_t namespaceNumber;
	CommandAndArgs comArg;
    uint8_t AuthenticationVector[32];
} SWCmdUplink;

/*
 * Here are the definitions of the name spaces and commands
 */

typedef enum {
	 SWCmdNSReserved=0
	,SWCmdNSOps
	,SWCmdNSTelem
	,SWCmdNSPacsat
	,SWCmdNumberOfNamespaces
}SWCommandNameSpace;

typedef enum {
     SWCmdIntReserved=0
    ,SWCmdIntAutosafeMode
}SWInternalCommands;


/* ANY ADDITIONS HERE MUST GO IN uplink_command.c str list */
typedef enum {
	 SwCmdPacsatReserved=0
	,SWCmdPacsatEnablePB			// Args Enable/Disable, Status Period(s), Station Timeout(s)
	,SWCmdPacsatEnableUplink		// Args Enable/Disable, Status Period(s), Station Timeout(s)
	,SWCmdPacsatInstallFile			// Args 32-bit File-Id, Folder-Id  -- TODO - it might be better to move this to Ops
	,SWCmdPacsatDeleteFile
	,SWCmdPacsatDeleteFolder = 5
	,SWCmdPacsatDefaultFileExpiryPeriod // in days
	,SWCmdPacsatFileExpiryPeriod        // in days
	,SWCmdPacsatDirMaintPeriod          // in seconds - one node processed per period
	,SWCmdPacsatFtl0MaintPeriod         // in seconds - Whole upload queue processed per period
	,SWCmdPacsatFileQueueCheckPeriod = 10         // in seconds - Check all the queues for files to add to the dir
	,SWCmdPacsatMaxFileSize				// Set the max upload file size in kb
	,SWCmdPacsatMaxUploadAge			// Set the max age for a file being uploaded.  After this time it is removed from upload queue
	,SWCmdPacsatEnableFSTelemetry
	,SwCmdPacsatNumberOfCommands
}SWPacsatCommands;


/* These are the default writable folders on the USB Stick.  The strings are defined in
 * uplink_command.c in a static array FolderIdStrings */
typedef enum {
	FolderBin
	,FolderLib
	,FolderCfg
	,FolderDir
	,FolderUpload
	,FolderWod  // Any file put in this folder will be automaticalled added to the dir as an WOD File
	,FolderLog  // Any file put in this folder will be automaticalled added to the dir as an ALOG File
	,FolderTxt  // Any file put in this folder will be automaticalled added to the dir as an ASCII File
	,FolderImg  // Any file put in this folder will be automaticalled added to the dir as an IMAGE TYPE 16 File
	,FolderSenWod  // Any file put in this folder will be automaticalled added to the dir as an SENSOR WOD File
	,FolderData1
	,FolderData2
	,FolderData3
	,FolderData4
	,FolderData5
	,FolderData6
	,FolderData7
	,FolderData8
	,FolderData9
	,NumberOfFolderIds
} FolderIds;


/* These ids are a lookup for the symbolrate strings.  If this is changed then edit the array in uplink_control.c */
typedef enum {
	Rate1200 = 0
	,Rate9600
	,NumberOfSymbolRateIds
} SymbolRateIds;



void init_commanding();
char * get_folder_str(FolderIds i);
int get_symbol_rates(SymbolRateIds i);
int get_namespace_from_str(char *name_space);
int get_command_from_str(SWCommandNameSpace name_space, char * cmd);
SWCmdUplink *get_last_command();
int AuthenticatePacket(uint32_t date_time_in_packet, uint8_t * uplink, int pkt_len, uint8_t *auth_vector);
int AuthenticateSoftwareCommand(SWCmdUplink *uplink);

#endif /* UPLINK_COMMAND_H_ */
