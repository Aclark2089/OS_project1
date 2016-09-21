#include <lib.h>
#include <unistd.h>

/*
	Get process from logs using given PID
	- pid : ID of wanted process
	- c_time : Creation time (UNISTD Time value)
	- t_time : Termination time (UNISTD Time value)
*/
int get_plog_byPID(int pid, long *c_time, long *t_time) {
	message m;
	m.m10_i1 = 4; 	// Call mode
	m.m10_i2 = pid; // PID of process wanted
	return _syscall(PM_PROC_NR, LOGSYSPS, &m);
	
}