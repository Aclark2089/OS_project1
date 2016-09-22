/* newtest.c
 *
 * usage: 
 *    newtest
 *
 * Author: R. E. Newman, CISE Department, UF, Gainesville, FL 32611-6120
 * Created: 
 * Modified:
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


//#include "plog.h"

#ifndef _PLOG
void start_plog(); 
void stop_plog(); 
void reset_plog(); 
int get_plog_size(); 
int get_plog_byPID(int pid, long* c_time, long* t_time); 
int get_plog_byindex(int index, long* c_time, long* t_time);
#endif


int debug = 0;
#define kids 10


#define CMDS "0=exit, 1=help, 2=start, 3=stop, 4=reset, 5=getByPID, 6=getByIndex, 7=getSize, 8=verbose, 9=silent"
enum cmd {EXIT, HELP, START, STOP, RESET, PID, INDEX, SIZE, VERBOSE, SILENT, DEBUGT};
int verbose=1;
#define PROMPT "Enter command: "

int help() 
{ 
	printf("%s\n",CMDS);
	return 0;
}

int get_command() 
{
	int c;
	int rv;

	if (verbose) printf("%s", PROMPT);
	fflush(stdout);
	rv = scanf("%d",&c);
	if (debug) fprintf(stderr, "rv = %d\n", rv);
	if ((c<0) || (c>DEBUGT)) return HELP;
	else return c;
}

int pid_case()
{
int pid;
int rv;
long start, finish;

	if (verbose) printf("Enter PID: ");
	fflush(stdout);
	rv = scanf("%d",&pid);
	if (debug) fprintf(stderr, "Getting times by PID: %d\n", pid);
	rv = get_plog_byPID(pid, &start, &finish); 
	if (rv == 0) 
	    {
		printf("PID %d, started at %ld, finished at %ld\n", pid, start, finish);
	    }
	    else
	    {
		printf("PID %d was not found\n", pid);
	    }
}

int index_case()
{
int index;
int rv;
long start, finish;

	if (verbose) printf("Enter index: ");
	fflush(stdout);
	rv = scanf("%d",&index);
	if (debug) fprintf(stderr, "Getting times by index: %d\n", index);

	rv = get_plog_byindex(index, &start, &finish);
	if (rv == 0) 
	{
	    printf("\tEntry %d started at %ld, finished at %ld\n", index, start, finish);
	}
	else
	{
		printf("\tEntry %d is not valid\n", index);
	}
}



int main(int argc, char *argv[])
{
int command;
pid_t pid;
int N;
int rv, s;
int i = 0;
long int start, finish;

	if (argc > 1) 
	    if (argv[1][0] == 'q') verbose = 0;

	if (verbose) 
		printf("%s\n", CMDS);

	while ((command = get_command())!=EXIT)
	{
	    switch(command)
	    {
		case EXIT:
		    return 0;
		    break;
		case HELP:
		    printf("%s\n", CMDS);
		    break;
		case START:
		    (void) start_plog();
		    break;
		case STOP:
		    (void) stop_plog();
		    break;
		case RESET:
		    (void) reset_plog();
		    break;
		case PID:
		    (void) pid_case();
		    break;
		case INDEX:
		    (void) index_case();
		    break;
		case SIZE:
		    N = get_plog_size();
		    printf("%d\n", N);
		    break;
		case VERBOSE:
		    verbose=1;
		    break;
		case SILENT:
		    verbose=0;
		    break;
		case DEBUGT:
		    debug=1-debug;
		    break;
		default:
		    break;
	    }
	}
	return 0;

}

