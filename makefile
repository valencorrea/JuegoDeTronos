CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = valgrind --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = reino.c juego_de_tronos.c 
HFILES = reino.h 
OFILES = cola.o lista.o abb.o
EXEC_S = ejecutable

build: $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) $(OFILES) -o $(EXEC_S) 

run: build
	./$(EXEC_S)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC_S)

gdb: build
	gdbtui $(GDBFLAGS) ./$(EXEC_S)
