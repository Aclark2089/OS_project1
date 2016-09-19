#include <lib.h>
#include <unistd.h>

// Start LOGSYSPS logging
void start_plog() {

	message m;
	m.m1_i1 = 1; // Mode
	_syscall(PM_PROC_NR, LOGSYSPS, &m);
	
}