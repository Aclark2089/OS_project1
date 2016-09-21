#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pm.h"

#define DEBUG_MODE TRUE				// Debug printing on
#define TABLE_CAPACITY 1024			// Globally defined sz of table
#define true 1 						// Definition for true boolean value
#define false 0						// Definition for false boolean value

typedef int bool;	// Definition for type boolean

/* 
 *	Struct aggregating each process' details as element 
 *	in logging table
 */
typedef struct logging_node {
	int pid;												// Process id
	long c_time;											// Creation time of this process
	long t_time;											// Termination time of this process
} logging_node;

/*
 * Logging table as a circular buffer & its member details
 *
 */
typedef struct logging_buffer {
	logging_node **buffer;					// Buffer of TABLE_CAPACITY
	logging_node **buffer_end;				// Ptr to end of buffer
	logging_node **current;					// Ptr to latest element of buffer
	size_t capacity; 						// Max number of items allowed (TABLE_CAPACITY)
	size_t count;							// Current number of items in buffer
	size_t sz;								// Size of each element (*loggging_node)
} logging_buffer;	

static bool initialized = false;			// Initialized flag for buffer
static bool logging_enabled = false;		// Flag for enabling process logging
static logging_buffer psbuffer;			// Logging buffer

// Function prototypes
void intialize_buffer_logging(void);				// Setup buffer
void start_buffer_logging(void);					// Start buffer logging
void stop_buffer_logging(void);						// Stop buffer logging
void reset_logging(void);							// Reset logging table
void push_table_entry(int, long, long);				// Push new entry into logging table
logging_node* find_node_by_PID(int);				// Find a node by PID
logging_node* add_process_termination_time(int); 	// Add termination time to a logging entry for a killed process by its PID

/* Function implementing custom syscall for process logging */
int do_logsysps() {
	
	int mode = m_in.m1_i1;	// Call mode
	int pid;				// PID
	int pid_index;			// Index in logging table

	if (!initialized) intialize_buffer_logging();

	if (initialized) {
		switch (mode) {
			case 0:
				// Turn on logging
				#ifdef DEBUG_MODE
					printf("Starting LOGSYSPS process logging...\n");
				#endif
				start_buffer_logging();
				break;
			case 1:
				// Turn off logging
				#ifdef DEBUG_MODE
					printf("Stopping LOGSYSPS process logging...\n");
				#endif
				stop_buffer_logging();
			case 2:
				// Reset logging table
				#ifdef DEBUG_MODE
					printf("Resetting LOGSYSPS process logging table...\n");
				#endif
				reset_logging();
				break;
			case 3:
				// Get the process from logs using index
				#ifdef DEBUG_MODE
					printf("Getting LOGSYSPS process by index...\n");
				#endif
				break;
			case 4:
				// Get the process from logs using PID
				#ifdef DEBUG_MODE
					printf("Getting LOGSYSPS process by PID...\n");
				#endif
				break;
			case 5:
				// Get size of the loggging table (return max index)
				#ifdef DEBUG_MODE
					printf("Returning size of LOGSYSPS logging table...\n");
				#endif
				break;
			default:
				// Unknown mode action
				#ifdef DEBUG_MODE
					printf("Unable to perform passed action to LOGSYSPS\nUnknown action mode\n");
				#endif
		}
	}

 	return 0;
}

// Initialize static circular psbuffer for logging table & set flag
void intialize_buffer_logging() {
	psbuffer.capacity = TABLE_CAPACITY;														// Set buffer capacity details
	psbuffer.sz = sizeof(logging_node*);														// Set sz for buffer elements
	psbuffer.buffer = (logging_node*) malloc(psbuffer.sz + psbuffer.capacity);
	if (psbuffer.buffer != NULL) {															// If successfully allocated, continue	
		psbuffer.buffer_end = psbuffer.buffer + psbuffer.capacity;							// Set end of buffer ptr
		psbuffer.current = psbuffer.buffer;													// Set head ptr to start
		initialized = true;																	// Set flag for initialized buffer
		#ifdef DEBUG_MODE
			printf("Buffer successfully allocated\n");
		#endif
	}
	else {
		fprintf(stderr, "Unable to allocate memory for LOGSYSPS buffer table: %d\n", errno);	// Log error of memory allocation	
	}
}

// Start logging of ps to buffer table
void start_buffer_logging() {
logging_enabled = true;
	#ifdef DEBUG_MODE
		printf("Logging enabled for ps table\n");
	#endif
}

// Stop logging of ps to buffer table
void stop_buffer_logging() {
	logging_enabled = false;
	#ifdef DEBUG_MODE
		printf("Logging disabled for ps table\n");
	#endif
}

// Reset logging table entries for entire table
void reset_logging() {
	// for (int i = 0; i < psbuffer.capacity; i++) {
	// 	temp = &psbuffer.buffer[i];
	// 	psbuffer.buffer[i] = NULL;
	// 	free(temp);											// Reset all logging table nodes
	// }
	// psbuffer.current = psbuffer.buffer;						// Reset current ptr to start
	#ifdef DEBUG_MODE
		printf("Reset logging table entries\n");
	#endif
}

// Return a ptr to a node by PID
logging_node* find_node_by_PID(int pid) {
	logging_node *n_ptr = psbuffer.buffer;				// Set new ptr to start of array
	// while(n_ptr != NULL) {								// Loop through array
	// 	if(n_ptr->pid == pid) break;					// Stop if we have found the node
	// 	n_ptr += psbuffer.sz;							// Increment by size of a node
	// }

	return n_ptr;										// Return ptr
}

logging_node* add_process_termination_time(int pid) {
	logging_node *n_ptr = psbuffer.buffer;
	return n_ptr;
}

// Add entry to logging table
void push_table_entry(int pid, long c_time, long t_time) {
	// logging_node n_ps = {pid, c_time, t_time};													// Create new entry
	// logging_node *temp;																			// Temp ptr to free old node
	// if (n_ps != NULL) {
	// 	// If index is currently at the end we wrap around to the beginning
	// 	if (psbuffer.current == psbuffer.buffer_end) psbuffer.current = psbuffer.buffer;
	// 	psbuffer.current = psbuffer.current + psbuffer.sz;		   							// Move ptr to next ptr
	// 	temp = psbuffer.current;
	// 	psbuffer.current = &n_ps;															// Set to address of new entry
	// 	free(temp);
	// 	#ifdef DEBUG_MODE
	// 		printf("Added new ps to logging table\nPID: %d\nc_time: %ld\nt_time: %ld\n", psbuffer.current->pid, psbuffer.current->c_time, psbuffer.current->t_time);
	// 	#endif
	// } 
	// else {
	// 	fprintf(stderr, "Unable to add new process node to table: %d", errno);	// Log error for inability to allocate new ps
	// }
}
