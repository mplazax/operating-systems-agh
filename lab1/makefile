CC = gcc
CFLAGS = -Wall -std=c17 -g

.PHONY: clean all test

all: countdown

test: all
	./countdown

countdown: 
	$(CC) $(CFLAGS) -c countdown.c
	$(CC) $(CFLAGS) countdown.o -o countdown

clean: 
	rm -f *.o countdown

