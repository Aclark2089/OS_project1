#include <lib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

	int size, pid, return_value;
	long c_time, t_time;

	printf("\n******* Starting **********\n");
	while(*++argv) {
		if( (*argv)[0] == '-') {
			switch((*argv)[1]) {
				default:
					printf("Unknown option given\n\n");
					break;
				case 's':
					printf("Start plog option given\n\n");
					start_plog();
					break;
				case 'k':
					printf("Stop plog option given\n\n");
					stop_plog();
					break;
				case 'r':
					printf("Reset plog option given\n\n");
					reset_plog();
					break;
				case 'i':
					printf("Get plog by index option given\n\n");
					return_value = get_plog_byindex(0, &c_time, &t_time);
					if (return_value == 1) {
						printf("Reported time values of index: %d %ld %ld\n", 0, c_time, t_time);	
					}
					else {
						printf("Invalid index position\n");
					}
					
					break;
				case 'p':
					printf("Get plog by pid option given\n\n");
					pid = fork();
					return_value = get_plog_byPID(pid, &c_time, &t_time);
					if (return_value == 1) {
						printf("Reported time values of\nPID: %d\nc_time: %ld\nt_time: %ld\n", pid, c_time, t_time);	
					}
					else {
						printf("Invalid PID entry\n");
					}
					break;
				case 't':
					printf("Get plog size option given\n\n");
					size = get_plog_size();
					printf("Logging table size reported as %d\n", size);
					break;
				case 'f':
					for(int i = 0; i < 5; i++) {
						pid = fork();
					}
					break;
				case 'h':
					printf("Optional Arguments:\n-s (Start Logging)\n-k (Stop Logging)\n-r (Reset Logging)\n-i (Test Get by Index)\n-p (Test Get by PID)\n-t (Get Logging Buffer Size)\n-f (Fill Table w/ Dummy PS)\n-h (Help)\n");
					break;	
			}
		}
	}

 	return 0; 
}
