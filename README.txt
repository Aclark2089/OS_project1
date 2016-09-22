R. Alex Clark
Project 1 - System Call
9/21/16
COP4600

MAKING A SYSTEM CALL

Detail of circular buffer)
	
	Name: psbuffer
	Size: 1024 (Defined by definition TABLE_CAPACITY)

Steps)

	1) Add PM Server Table Entry
		* We need to update the /usr/src/servers/pm/table.c file with a declaration of the call that will be implemented by our PM server. In this case, we added do_logsysps to slot 69 of the table

	2) Define the SYSCALL number
		* Like table.c, we need to add the LOGSYSPS definition to the /usr/src/includes/minix/callnr.h. This needs to be the SAME NUMBER as the slot that we took in table.c so we will be able to call that specific function from user space

	3) Define prototypes of functions we will be using
		* Specifically, we will need to define do_logsysps() and the helper functions for it inside of the servers/pm/proto.h header file

	4) Setup the system call implementations
		* In /usr/src/lib/libc/ we will need to setup the function calls that implement the different actions and set a different mode for each of them so that do_logsysps knows which switch branch to take.
		* We will need to add the new library .c files to the Makefile so that they will be compiled

	5) Pass messages & perform the syscalls
		* Using the message struct we set the message contents such as mode and pid / index for the do_logsysps call to receive.

	6) Return response
		* After the requested action has been taken, we save the contents of the response inside the m_reply, so that the caller in user space will be able to access them. We then return 1, 2, or 3 based on the success or failure of the call, or if it is unable to find the specified logging entry.


Challenges Encountered)

	* Understanding system landscape - it was quite difficult to understand where the necessary directories were that I would need to recompile and add to if I wanted to add new system calls. This took a lot of supplemental reading to become familiar with the fs.

	* Compile time - the process of changing and then recompiling takes quite a long time even if done selectively. I wrote scripts to selectively compile the parts that I needed.

	* Understanding how the global definitions and externally defined variables and structures are used by the system. This took quite a bit of testing and rerunning of programs to figure out where I would need to define things.

	* Understanding how the message passing works for performing the syscall - This took quite awhile because there is not a lot of easily available resources for understanding how the message members work but I had to just browse through ipc.h and see which members I would need based on type and availability

Testing)

	Tested using a custom .exe that performs different actions based on the passed flag.

	s - calls the start_plog()
	k - calls the stop_plog()
	r - calls reset_plog()
	i - calls get_plog_byindex() and passes in a set index
	p - calls get_plog_byPID() and passes in a set pid
	t - calls get_plog_size() and gets the table size

Known Bugs)
	None currently known