#include <lib.h>
#include <unistd.h>

// Stop LOGSYSPS logging
void stop_plog() {

	message m;
	m.m1_i1 = 0; // Mode
	_syscall(PM_PROC_NR, LOGSYSPS, &m);
	
}