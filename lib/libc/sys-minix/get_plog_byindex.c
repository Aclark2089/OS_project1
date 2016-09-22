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
	m.m10_i1 = 3; 												// Call mode
	m.m10_i2 = index;											// Index for pid

	int return_value = _syscall(PM_PROC_NR, LOGSYSPS, &m);		// Perform syscall

	if (return_value == 3) {	// No entry found
		*c_time = -1;
		*t_time = -1;
		return 3;
	}						// Entry found, return results
		
	*c_time = m.m10_l1;
	*t_time = m.m10_l2;

	return 1;

}