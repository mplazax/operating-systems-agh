CC=gcc
CFLAGS=-Wall -g
TARGET=globallocal
SRC=globallocal.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
