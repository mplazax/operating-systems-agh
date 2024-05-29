# Makefile

# Kompilator
CC = gcc

# Flagi kompilatora
CFLAGS = -Wall -pthread

# Nazwa pliku wykonywalnego
TARGET = santa_reindeers

# Pliki źródłowe
SRCS = santa_reindeers.c

# Pliki obiektowe
OBJS = $(SRCS:.c=.o)

# Reguła domyślna
all: $(TARGET)

# Reguła budująca plik wykonywalny
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Reguła budująca pliki obiektowe
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Reguła czyszczenia
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
