#include <stdio.h>
#include "pm.h"

/* Function implementing custom syscall for process logging */
int do_logsysps() {
	
	int mode = m_in.m1_i1;	// Call mode
	int pid;				// PID
	int pid_index;			// Index in logging table

	switch (mode) {
		case 1:
			// Turn on logging
			printf("Started Process Logging\n");
			break;
		case 2:
			// Reset logging table
			printf("Resetting Process Logging Table\n");
			break;
		case 3:
			// Get the process from logs using index
			printf("Getting Process by Index\n");
			break;
		case 4:
			// Get the process from logs using PID
			printf("Getting Process by PID\n");
			break;
		case 5:
			// Get size of the loggging table (return max index)
			printf("Returning Size of Logging Table\n");
			break;
		default:
			// Turn off logging
			printf("Stopped Process Logging\n");
	}

 	return 0;
}
