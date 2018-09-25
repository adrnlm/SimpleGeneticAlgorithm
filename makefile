CC = gcc
DEBUG = -DDEBUG -g
CFLAGS = -ansi -pedantic -Wall
PROG = ga
OBJS = drive.o gene.o invector.o pop.o

all:
	$(CC) $(CFLAGS) *.c -o $(PROG)

debug:
	$(CC) $(DEBUG) -o $(PROG) *.c
	./ga

clean:
	rm -f *.o *.h.gch $(PROG)
