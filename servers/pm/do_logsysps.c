#include "pm.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "mproc.h"
#include "do_logsysps.h"


// Logging buffer for process table entries
struct logging_node psbuffer[TABLE_CAPACITY];
int initialized = 0;         	

/* Function implementing custom syscall for process logging */
int do_logsysps() {

	if (!initialized) {
		ps_logging_index = 0;
		ps_logging_count = 0;
		ps_logging_enabled = 0;
		initialized = 1;
	}
	
	int mode = m_in.m10_i1;					// Call mode
	int pid_index = m_in.m10_i2;			// Index or PID # in logging table

	switch (mode) {
		case 0:
			// Turn on logging
			#ifdef DEBUG_MODE
				printf("Starting LOGSYSPS process logging...\n");
			#endif
			start_buffer_logging();
			return 1;
		case 1:
			// Turn off logging
			#ifdef DEBUG_MODE
				printf("Stopping LOGSYSPS process logging...\n");
			#endif
			stop_buffer_logging();
			return 1;
		case 2:
			// Reset logging table
			#ifdef DEBUG_MODE
				printf("Resetting LOGSYSPS process logging table...\n");
			#endif
			reset_logging();
			return 1;
		case 3:
			// Get the process from logs using index
			#ifdef DEBUG_MODE
				printf("Getting LOGSYSPS process by index...\n");
			#endif
			return get_plog_by_index(pid_index);
		case 4:
			// Get the process from logs using PID
			#ifdef DEBUG_MODE
				printf("Getting LOGSYSPS process by PID...\n");
			#endif
			return get_plog_by_PID(pid_index);
		case 5:
			// Get size of the loggging table (return max index)
			#ifdef DEBUG_MODE
				printf("Returning size of LOGSYSPS logging table...\n");
			#endif
			return get_plog_size();
		default:			
			#ifdef DEBUG_MODE // Unknown mode action
				printf("Unable to perform passed action to LOGSYSPS\nUnknown action mode\n");
			#endif
			break;
	}

	// Failure to perform action
 	return 2; 
}

// Start logging of ps to buffer table
void start_buffer_logging() {
	ps_logging_enabled = 1;	// Enable logging
	#ifdef DEBUG_MODE
		printf("Logging enabled for ps table\n");
	#endif
}

// Stop logging of ps to buffer table
void stop_buffer_logging() {
	ps_logging_enabled = 0;	// Disable logging
	#ifdef DEBUG_MODE
		printf("Logging disabled for ps table\n");
	#endif
}

// Reset logging table entries for entire table
void reset_logging() {


	// Zero out logging table process entries
	for (int i = 0; i < TABLE_CAPACITY; i++) {	
		psbuffer[i].pid = 0;
		psbuffer[i].c_time = 0;
		psbuffer[i].t_time = 0;
	}

	ps_logging_index =  0; 	// Reset current table index
	ps_logging_count = 0;	// Reset table entry count

	#ifdef DEBUG_MODE
		printf("Reset logging table entries\n");
	#endif
}

// Add termination time for recently killed ps
void add_process_termination_time(int pid) {

	long t_time = mp->mp_reply.m2_l1;									// Grab termination time
	for(int i = 0; i < TABLE_CAPACITY; i++) {							// Loop through buffer
		if (psbuffer[i].pid == pid) psbuffer[i].t_time = t_time;		// Set t_time if entry pid matches
	}

}

// Return size of logging buffer
int get_plog_size() {
	mp->mp_reply.m10_i1 = TABLE_CAPACITY;	// # of entries in table
	return 1;
}

int get_plog_by_PID(int pid) {
	
	int i = 0;
	while (i++ < ps_logging_count) {	
		if(psbuffer[i].pid == pid) {
			mp->mp_reply.m10_l1 = psbuffer[i].c_time;	// Set c_time in reply
			mp->mp_reply.m10_l2 = psbuffer[i].t_time;	// Set t_time in reply
			return 1;
		}
	}

	// PID not found in buffer, failure
	return 2;
}

// Return the entry associated by given index
int get_plog_by_index(int index) {

	// If index is not an entry, return failure
	if (psbuffer[index].pid == 0) return 3;

	// Set message details
	mp->mp_reply.m10_l1 = psbuffer[index].c_time;	// Set c_time in reply
	mp->mp_reply.m10_l2 = psbuffer[index].t_time;	// Set t_time in reply

	#ifdef DEBUG_MODE
		printf("Found index %d values: %ld %ld\n", index, psbuffer[index].c_time, psbuffer[index].t_time);
		printf("Reported index %d values: %ld %ld\n", index, mp->mp_reply.m10_l1, mp->mp_reply.m10_l2);
	#endif

	// Success
	return 1;
}

void print_table() {
	printf("\nPRINTING TABLE:\n");
	for(int i = 0; i < ps_logging_count; i++) {
		printf("Logging Table Entry %d: %d %ld %ld\n", i, psbuffer[i].pid, psbuffer[i].c_time, psbuffer[i].t_time);
	}
	printf("\nTABLE END\n");
}

// Add entry to logging table
void push_table_entry(int pid) {

		long c_time = mp->mp_reply.m2_l1;									// Grab creation time
		psbuffer[ps_logging_index].pid = pid;								// Set entry pid
		psbuffer[ps_logging_index].c_time = c_time;							// Set entry c_time
		psbuffer[ps_logging_index].t_time = 0;								// T_time pending

		if (ps_logging_count < TABLE_CAPACITY) ++ps_logging_count;			// Add to count only if we have not reached max size

		#ifdef DEBUG_MODE
			printf("Added new ps to logging table\nIndex: %d\nPID: %d\nc_time: %ld\nt_time: %ld\n", ps_logging_index, psbuffer[ps_logging_index].pid, psbuffer[ps_logging_index].c_time, psbuffer[ps_logging_index].t_time);
			print_table();
		#endif

		++ps_logging_index;													// Increment logging table index
		if (ps_logging_index == TABLE_CAPACITY) ps_logging_index = 0;									// Mod table index if outsize [0, 1024)

}
