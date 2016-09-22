
#define DEBUG_MODE 1				// Debug printing on
#define TABLE_CAPACITY 1024      // Globally defined sz of table

/* 
 *  Struct aggregating each process' details as element 
 *  in logging table
 */
EXTERN struct logging_node {
  int pid;                          // Process id
  long c_time;                      // Creation time of this process
  long t_time;                      // Termination time of this process
} logging_node;
