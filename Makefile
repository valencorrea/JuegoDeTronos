CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = valgrind --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = reino.c juego_de_tronos.c abb.c cola.c lista.c
HFILES = reino.h abb.h cola.h lista.h
EXEC_S = ejecutable

build: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(CFILES)

run: build
	./$(EXEC_S)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC_S)

gdb: build
	gdbtui $(GDBFLAGS) ./$(EXEC_S)

