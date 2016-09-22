#include <lib.h>
#include <unistd.h>


// Get count of logged processes from table
int get_plog_size() {

	message m;												// Message
	m.m10_i1 = 5; 											// Call Mode
	int return_value = _syscall(PM_PROC_NR, LOGSYSPS, &m);	// Perform syscall

	if (return_value == 1) {
		return m.m10_i1;			// Return size
	}

	return 2;
}