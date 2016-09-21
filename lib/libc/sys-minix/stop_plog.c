#include <lib.h>
#include <unistd.h>

// Stop LOGSYSPS logging
void stop_plog() {

	message m;
	m.m10_i1 = 1; // Mode
	_syscall(PM_PROC_NR, LOGSYSPS, &m);
	
}