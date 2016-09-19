#include <lib.h>
#include <unistd.h>


// Get count of logged processes from table
int get_plog_size() {
	message m;
	m.m1_i1 = 5; // Call mode
	return _syscall(PM_PROC_NR, LOGSYSPS, &m);
	
}