#include <lib.h>
#include <unistd.h>

// Start LOGSYSPS logging
void start_plog() {

	message m;								// Message
	m.m10_i1 = 0; 							// Call Mode
	_syscall(PM_PROC_NR, LOGSYSPS, &m);		// Perform syscall
	
}