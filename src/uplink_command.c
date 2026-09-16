/*
 * uplink_command.c
 *
 *  Created on: Nov 27, 2023
 *      Author: g0kla
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uplink_command.h>
#include "common_config.h"
#include "str_util.h"

/* Forwards */


/* This defines the folder names that can be referenced in commands using the ids in FolderIds
 * IMPORTANT - Must also change the enum in uplink_command.h that corresponds to this */
char *FolderIdStrings[] = {
		"bin"
		,"lib"
		,"cfg"
		,"pacsat/dir"
		,"pacsat/upload"
		,"pacsat/wod"
		,"pacsat/log"
		,"pacsat/txt"
		,"pacsat/img"
		,"pacsat/senwod"
		,"data1"
		,"data2"
		,"data3"
		,"data4"
		,"data5"
		,"data6"
		,"data7"
		,"data8"
		,"data9"
};

/* This gives user understandable names for the name spaces.  These are used in the schedule. It must match the enum in uplink_command.h */
char *NameSpaceStrings[] = {
		"-"
		,"ops"
		,"telem"
		,"fs"
};


char *PacsatCommandStrings[] = {
		"reserved"
		,"pb"
		,"uplink"
		,"install"
		,"del" // 4
		,"del-folder" // 5
		,"default-file-exp-period"
		,"file-exp-period"
		,"dir-maint-period"
		,"up-maint-period"
		,"que-chk-period" // 10
		,"max-file-size"
		,"max-upload-age"
		,"exec-file" //13
};


int SymbolRates[] = {
		1200
		,9600
};

void init_commanding() {

}

char * get_folder_str(FolderIds i) {
	if (i < 0 || i > NumberOfFolderIds) return NULL;
	return FolderIdStrings[i];
}

int get_symbol_rates(SymbolRateIds i) {
	if (i < 0 || i > NumberOfSymbolRateIds) return -1;
	return SymbolRates[i];
}

int get_namespace_from_str(char *name_space) {
	int i = 0;
	for (i = 0; i < SWCmdNumberOfNamespaces; i++) {
		if (strcasecmp(name_space, NameSpaceStrings[i]) == 0) {
			return i;
		}
	}
	return SWCmdNSReserved;
}

int get_command_from_str(SWCommandNameSpace name_space, char * cmd) {

	if (name_space == SWCmdNSPacsat) {
		int i = 0;
		for (i = 0; i < SwCmdPacsatNumberOfCommands; i++) {
			if (strcasecmp(cmd, PacsatCommandStrings[i]) == 0) {
				return i;
			}
		}
	}
	return SwCmdPacsatReserved;
}



/**
 * Dummy
 *
 */
int AuthenticatePacket(uint32_t date_time_in_packet, uint8_t * uplink, int pkt_len, uint8_t *auth_vector) {
	return EXIT_SUCCESS;
}

/**
 * Dummy
 */
int AuthenticateSoftwareCommand(SWCmdUplink *uplink) {
	return EXIT_SUCCESS;
}
