# Makefile for compiling integrate and handle_input programs

CC = gcc
CFLAGS = -Wall -Wextra
RM = rm -f

# Executable names
EXEC1 = receiver
EXEC2 = sender

# Source files
SRC1 = receiver.c
SRC2 = sender.c

# Object files
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)

.PHONY: all clean

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJ1)
	$(CC) $(CFLAGS) -o $@ $^

$(EXEC2): $(OBJ2)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(EXEC1) $(EXEC2) $(OBJ1) $(OBJ2) integral_in.fifo integral_out.fifo

