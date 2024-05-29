CC=gcc
CFLAGS=-Wall -g
SRC=reverse.c
OBJ=$(SRC:.c=.o)
EXEC1=reverse_buffer
EXEC2=reverse_no_buffer

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(SRC)
	$(CC) $(CFLAGS) -DBUFFER_ENABLED -o $@ $^

$(EXEC2): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(EXEC1) $(EXEC2) $(OBJ)

.PHONY: all clean
