CC=cc
CFLAGS= -g -Wall -I.

project1: project1.c
	$(CC) -o $@ project1.c $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.out core project1