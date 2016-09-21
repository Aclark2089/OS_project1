PROJECT_DIR=/mnt/projects/project1/
cd $PROJECT_DIR
patch /usr/src/include/unistd.h include/diff_unistd.txt
patch /usr/src/include/minix/callnr.h include/minix/diff_callnr.txt
patch /usr/src/lib/libc/sys-minix/Makefile.inc lib/libc/sys-minix/diff_Makefile.txt
cp lib/libc/sys-minix/get_plog_byindex.c /usr/src/lib/libc/sys-minix/
cp lib/libc/sys-minix/get_plog_byPID.c /usr/src/lib/libc/sys-minix/
cp lib/libc/sys-minix/get_plog_size.c /usr/src/lib/libc/sys-minix/
cp lib/libc/sys-minix/reset_plog.c /usr/src/lib/libc/sys-minix/
cp lib/libc/sys-minix/start_plog.c /usr/src/lib/libc/sys-minix/
cp lib/libc/sys-minix/stop_plog.c /usr/src/lib/libc/sys-minix/
patch /usr/src/servers/pm/Makefile servers/pm/diff_Makefile.txt
patch /usr/src/servers/pm/proto.h servers/pm/diff_proto.txt
patch /usr/src/servers/pm/table.c servers/pm/diff_table.txt
patch /usr/src/servers/pm/mproc.c servers/pm/diff_mproc.txt
patch /usr/src/servers/pm/forkexit.c servers/pm/diff_forkexit.txt
patch /usr/src/servers/pm/glo.h servers/pm/diff_glo.txt
cp servers/pm/do_logsysps.c /usr/src/servers/pm/
cp servers/pm/do_logsysps.h /usr/src/servers/pm/