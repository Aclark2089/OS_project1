#include <lib.h>
#include <unistd.h>

/*
	Get process from logs using given index
	- index : Index of wanted tuple
	- c_time : Creation time (UNISTD Time value)
	- t_time : Termination time (UNISTD Time value)
*/
int get_plog_byindex(int index, long *c_time, long *t_time) {
	message m;
	m.m1_i1=4; // Call mode
	return _syscall(PM_PROC_NR, LOGSYSPS, &m);
	
}