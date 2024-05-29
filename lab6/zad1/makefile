# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=gnu99

# Define the source files
SOURCES_INTEGRATE = integrate.c


# Define the executables
EXECUTABLE_INTEGRATE = integrate


all: $(EXECUTABLE_INTEGRATE)

$(EXECUTABLE_INTEGRATE): $(SOURCES_INTEGRATE)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


clean:
	rm -f $(EXECUTABLE_INTEGRATE)

.PHONY: all clean
