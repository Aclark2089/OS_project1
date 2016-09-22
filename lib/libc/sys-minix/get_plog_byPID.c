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

	int return_value = _syscall(PM_PROC_NR, LOGSYSPS, &m);

	if (return_value == 2) {	 	// No entry found
		*c_time = -1;
		*t_time = -1;
		return 2;
	}

		// Entry found, return results
		*c_time = m.m10_l1;
		*t_time = m.m10_l2;

	return 0;
	
}