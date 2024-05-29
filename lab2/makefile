CC=gcc
CFLAGS=-Wall -fPIC -O0

# Domyślny cel
all: shared dynamic

# Kompilacja biblioteki współdzielonej
shared: libcollatz.so main_shared

libcollatz.so: collatz.o
	$(CC) -shared -o $@ $^

main_shared: main.o
	$(CC) $(CFLAGS) main.o -L. -lcollatz -o $@

# Kompilacja z biblioteką ładowaną dynamicznie
dynamic: libcollatz.so main_dynamic

main_dynamic: main.c
	$(CC) $(CFLAGS) -DDYNAMIC $< -ldl -o $@

collatz.o: collatz.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

# Czyszczenie
clean:
	rm -f *.o *.a *.so main_shared main_dynamic
