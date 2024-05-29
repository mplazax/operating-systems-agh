# Variables to control Makefile operation
CC = gcc
CFLAGS = -Wall

# Name of the target executable
TARGET = sigusr

# Build target
all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $(TARGET).c

# Clean target
clean:
	rm -f $(TARGET) $(TARGET).o

# Phony targets
.PHONY: all clean
