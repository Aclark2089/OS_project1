#include <lib.h>
#include <unistd.h>

void start_plog() {

	message m;
	m.m1_i1 = 10;
	_syscall(PM_PROC_NR, LOGSYSPS, &m);
	
}