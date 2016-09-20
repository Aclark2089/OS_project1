#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pm.h"

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
	logging_node *buffer;									// Ptr to buffer
	logging_node *buffer_end;								// Ptr to tail of buffer
	size_t capacity; 										// Max number of items allowed (1024)
	size_t count;											// Current number of items in buffer
	size_t sz;												// Size of each element
	logging_node *head;										// Ptr to first element of buffer
	logging_node *tail;										// Ptr to last element of buffer
} logging_buffer;	

#define DEBUG_MODE TRUE				// Debug printing on
#define TABLE_CAPACITY 1024			// Globally defined sz of table
#define true 1 						// Definition for true boolean value
#define false 0						// Definition for false boolean value
bool initialized = false;			// Initialized flag for buffer
bool logging_enabled = false;		// Flag for enabling process logging
static logging_buffer *psbuffer;	// Logging buffer

// Function prototypes
void intialize_buffer_logging(void);		// Setup buffer
void start_buffer_logging(void);			// Start buffer logging
void stop_buffer_logging(void);				// Stop buffer logging
void reset_logging(void);					// Reset logging table

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

void intialize_buffer_logging() {
	psbuffer = malloc(sizeof(logging_buffer));										// Declare & create buffer structure
	psbuffer->capacity = TABLE_CAPACITY;											// Set buffer capacity details
	psbuffer->sz = sizeof(logging_node);											// Set sz for buffer elements
	psbuffer->buffer = calloc(psbuffer->capacity, psbuffer->sz);					// Create buffer table of TABLE_CAPACITY logging nodes
	if (psbuffer->buffer != NULL) {													// If successfully allocated, continue	
		psbuffer->buffer_end = psbuffer->buffer + psbuffer->capacity;				// Set end of buffer ptr
		initialized = true;															// Set flag for initialized buffer
		#ifdef DEBUG_MODE
			printf("Buffer successfully allocated\n");
		#endif
	}
	else {
		fprintf(stderr, "Unable to allocate memory for LOGSYSPS buffer\n", errno);	// Log error of memory allocation
	}
}

// Start logging of ps to buffer table
void start_buffer_logging() {
logging_enabled = true;
	#ifdef DEBUG_MODE
		printf("Logging enabled for ps table");
	#endif
}

// Stop logging of ps to buffer table
void stop_buffer_logging() {
	logging_enabled = false;
	#ifdef DEBUG_MODE
		printf("Logging disabled for ps table");
	#endif
}

// Reset logging table
void reset_logging() {}
