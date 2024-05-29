# Definicja kompilatora
CC=gcc

# Opcje kompilatora, gdzie:
# -Wall włącza wszystkie ostrzeżenia kompilatora
# -g dodaje informacje debugowania, przydatne podczas debugowania
CFLAGS=-Wall -g

# Nazwa pliku wykonywalnego
TARGET=print_system

# Lista plików źródłowych
SOURCES=print_system.c

# Lista obiektów, które są kompilowane
OBJECTS=$(SOURCES:.c=.o)

# Domyślny cel (target), który zostanie wykonany, gdy uruchomisz make bez argumentów
all: $(TARGET)

# Jak zbudować plik wykonywalny z obiektów
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Jak zbudować pliki obiektowe z plików źródłowych
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Cel czyszczący projekt ze wszystkich plików generowanych przez kompilator
clean:
	rm -f $(TARGET) $(OBJECTS)

# Cel pomocniczy, aby zapobiec problemom z nazwami plików
.PHONY: all clean
