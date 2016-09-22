CC=cc
CFLAGS= -g -Wall -I.

# My test program
project1: project1.c
	$(CC) -o $@ project1.c $(CFLAGS)

# Test compilation
test: patch_copy buildsys

patch_copy:
	./scripts/patch_copy.sh

buildsys:
	cd /usr/src/releasetools && make hdboot
	cd /usr/src/include && make dependall install
	cd /usr/src/lib && make dependall install
	reboot

.PHONY: clean

clean:
	rm -f *.out core log_*.txt ./logs/*.txt project1
