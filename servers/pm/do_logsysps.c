#include <stdio.h>
#include "pm.h"

/* Function implementing custom syscall for process logging */
int do_logsysps()
{
	int i = 0;
	if (m_in.m1_i1 == 10) {
		i = 200;
	}
	/*int i = m_in.m1_i1; */
	printf("Hello World, got number %d\n", i);
 	return 0;
}
