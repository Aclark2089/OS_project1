#include <lib.h>
#include <unistd.h>

// Reset LOGSYSPS logging table
void reset_plog() {

	message m;								// Message
	m.m1_i1 = 2; 							// Call mode
	_syscall(PM_PROC_NR, LOGSYSPS, &m);		// Perform syscall
	
}