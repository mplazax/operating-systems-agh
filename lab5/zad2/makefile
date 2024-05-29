# Compiler to use
CC = gcc

LDFLAGS = -lrt

# Compiler flags
CFLAGS = -Wall -std=gnu99

# Define the source files
SOURCES_SENDER = sender.c
SOURCES_CATCHER = catcher.c

# Define the executables
EXECUTABLE_SENDER = sender
EXECUTABLE_CATCHER = catcher

all: $(EXECUTABLE_SENDER) $(EXECUTABLE_CATCHER)

$(EXECUTABLE_SENDER): $(SOURCES_SENDER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(EXECUTABLE_CATCHER): $(SOURCES_CATCHER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE_SENDER) $(EXECUTABLE_CATCHER)

.PHONY: all clean
